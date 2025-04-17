#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "camera.hpp"
#include "uiLabel.hpp"

struct inventoryItem
{
    inventoryItem(SDL_Renderer* ren, const char* name, const char* texturePath)
    {
        itemName = name;
        SDL_Surface* tmp = IMG_Load(texturePath);
        itemTex = SDL_CreateTextureFromSurface(ren, tmp);
        SDL_SetTextureScaleMode(itemTex, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }
    ~inventoryItem()
    {}
    
    void draw(SDL_Renderer* ren, int xPos, int yPos)
    {
        dstRect.x = xPos * dstRect.w + 60;
        dstRect.y = yPos * dstRect.h + 150;

        SDL_RenderTexture(ren, itemTex, NULL, &dstRect);
    }

    SDL_Texture* itemTex;
    const char* itemName;
    SDL_FRect dstRect = {0,0,50,50};
};

class inventory
{

    public:
    inventory(SDL_Renderer* ren, camera* cam);
    ~inventory();

    void interactInventory();

    void addItem(SDL_Renderer* ren, const char* name, const char* filepath);

    bool hasSpace(){return capasity - boxOfThings.size() > 0;}

    void draw(SDL_Renderer* ren);
    
    private:
    std::vector<inventoryItem*> boxOfThings;
    SDL_FRect container;
    bool open = false;
    int sizeX;
    int capasity = 100;
    uiLabel* label;
};