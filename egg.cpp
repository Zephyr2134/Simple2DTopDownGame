#include "egg.hpp"
#include <SDL3_image/SDL_image.h>
#include <cmath>

egg::egg(SDL_Renderer* ren, const char* Name, const char* filepath, float sizeX, float sizeY, int posX, int posY) : name(Name), filePath(filepath) 
{
    SDL_Surface* tmp = IMG_Load(filepath);
    eggTex = SDL_CreateTextureFromSurface(ren, tmp);
    SDL_SetTextureScaleMode(eggTex, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(tmp);

    dstRect = {0,0,sizeX,sizeY};
    worldpos = new vector2d(posX, posY);

    label = new uiLabel(ren, "'E'", 24, {posX + sizeX/2.0f - 30, posY - 40.0f, 60,60});
}

egg::~egg()
{}

void egg::update(int playerX, int playerY, int pickupRadius)
{
    if(sqrt(pow(playerX - worldpos->getX() + (dstRect.w/2),2) + pow(playerY - worldpos->getY() + (dstRect.h/2), 2)) < pickupRadius)
    {
        inRange = true;
    }
    else
    {
    inRange = false;
    }
}

bool egg::pickup()
{
    if(inRange)
    {
        return true;
    }
    return false;
}

void egg::draw(SDL_Renderer* ren, camera* cam)
{
    dstRect.x = worldpos->getX() - cam->position().x;
    dstRect.y = worldpos->getY() - cam->position().y;
    SDL_RenderTexture(ren, eggTex, NULL, &dstRect);

    if(inRange)
    {
    label->draw(ren, cam);
    }
}