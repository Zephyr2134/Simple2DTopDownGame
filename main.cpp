#include "game.hpp"

game* mainGame = nullptr;

int main()
{

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    mainGame = new game("DinoGame", 800, 800, false);

    while(mainGame->running())
    {

        frameStart = SDL_GetTicks();

        mainGame->handleEvents();
        mainGame->update();
        mainGame->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    mainGame->clean();
    return 0;
}