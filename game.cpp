#include "game.hpp"
#include <SDL3_ttf/SDL_ttf.h>

game::game(const char* title, int width, int height, bool fullscreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_EVENTS) && TTF_Init())
    {
        SDL_Log("Subsystems initilized");
    }

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(title, width, height, flags);

    if(window)
    {
        SDL_Log("Window created");
    }

    SDL_GetWindowSize(window, &winWidth, &winHeight);

    renderer = SDL_CreateRenderer(window, NULL);

    if(renderer)
    {
        SDL_Log("Renderer created");
    }

    gameMap = new map(renderer,"Maps/sample.txt",10,10, 200);
    cam = new camera(winWidth, winHeight, 10);
    character = new player(renderer, "Assets/Map/character.png", 650,1000);
    characterInventory = new inventory(renderer, cam);

    for(int i = 0; i < 100; i++)
    {
        eggs.push_back(new egg(renderer, "BasicEgg", "Assets/Map/egg.png", 50, 50, 100, 100));
    }
}

game::~game()
{}

void game::handleEvents()
{
    SDL_PollEvent(&event);
    if(event.type == SDL_EVENT_QUIT)
    {
        isRunning = false;
    }
    if(event.type == SDL_EVENT_KEY_DOWN)
    {
        if(event.key.key == SDLK_E)
        {
            int eggCount = 0;
            for(egg* e : eggs)
            {
                if(characterInventory->hasSpace())
                {
                    if(e->pickup())
                    {
                        SDL_Log("Pick up");
                        characterInventory->addItem(renderer, e->getName(), e->getFilepath());
                        eggs.erase(eggs.begin() + eggCount);
                        break;
                    }
                    eggCount++;
                }
            }
        }
        if(event.key.key == SDLK_TAB)
        {
            characterInventory->interactInventory();
        }
    }
    character->handleEvents(event);
}

void game::update()
{
    character->move();
    cam->follow(character->middleX(), character->middleY(),gameMap->width(), gameMap->height());

    for(egg* e : eggs)
    {
        e->update(character->middleX(), character->middleY(), character->pickupRad());
    }
}

void game::render()
{   
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    gameMap->draw(renderer, cam);
    for(egg* e : eggs)
    {
        e->draw(renderer, cam);
    }
    character->render(renderer, cam);
    characterInventory->draw(renderer);
    SDL_RenderPresent(renderer);
}

void game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    SDL_Log("Finished");
}