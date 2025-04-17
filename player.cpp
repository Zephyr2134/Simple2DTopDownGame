#include "player.hpp"

player::player(SDL_Renderer* ren, const char* textureFilepath, float xpos, float ypos)
{
    worldPos = new vector2d(xpos, ypos);

    SDL_Surface* tmpSurf = IMG_Load(textureFilepath);
    playerTex = SDL_CreateTextureFromSurface(ren, tmpSurf);
    SDL_DestroySurface(tmpSurf);
    SDL_SetTextureScaleMode(playerTex, SDL_SCALEMODE_NEAREST);
}

player::~player()
{}

void player::handleEvents(SDL_Event event)
{
    if(event.type == SDL_EVENT_KEY_DOWN)
    {
        switch(event.key.key)
        {
        case SDLK_W:
            up = true;
            break;
        case SDLK_S:
            down = true;
            break;
        case SDLK_D:
            right = true;
            break;
        case SDLK_A:
            left = true;
            break;
        }
    }
    if(event.type == SDL_EVENT_KEY_UP)
    {
        switch(event.key.key)
        {
        case SDLK_W:
            up = false;
            break;
        case SDLK_S:
            down = false;
            break;
        case SDLK_D:
            right = false;
            break;
        case SDLK_A:
            left = false;
            break;
        }
    }
}

void player::move()
{
    if(up && right || right && down || down && left || left && up)
    {
        speed = angledSpeed;
    }else
    {
        speed = baseSpeed;
    }
    if(up)
    {
        worldPos->changeY(-speed);
    }
    if(down)
    {
        worldPos->changeY(speed);
    }
    if(right)
    {
        worldPos->changeX(speed);
    }
    if(left)
    {
        worldPos->changeX(-speed);
    }
}

void player::render(SDL_Renderer* renderer, camera* cam)
{
    camPos = cam->position();

    if(worldPos->getX() < camPos.x)
    {
        worldPos->setX(camPos.x);
    } else if(worldPos->getX() + dstRect.w > camPos.x + camPos.w)
    {
        worldPos->setX(camPos.x + camPos.w - dstRect.w);
    }
    if(worldPos->getY() < camPos.y)
    {
        worldPos->setY(camPos.y);
    }else if(worldPos->getY() + dstRect.h > camPos.y + camPos.h)
    {
        worldPos->setY(camPos.y + camPos.h - dstRect.h);
    }

    dstRect.x = worldPos->getX() - camPos.x;
    dstRect.y = worldPos->getY() - camPos.y;

    SDL_RenderTexture(renderer, playerTex, NULL, &dstRect);
}