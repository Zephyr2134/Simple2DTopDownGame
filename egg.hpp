#pragma once
#include <SDL3/SDL.h>
#include "vector2d.hpp"
#include "camera.hpp"
#include "uiLabel.hpp"

class egg
{
    public:
        egg(SDL_Renderer* ren, const char* name, const char* filepath, float sizeX, float sizeY, int posX, int posY);
        ~egg();


        void update(int playerX, int playerY, int pickupRadius);
        bool pickup();
        void draw(SDL_Renderer* ren, camera* cam);

        const char* getName(){return name;}
        const char* getFilepath(){return filePath;}

    private:
        SDL_Texture* eggTex;
        SDL_FRect dstRect;
        vector2d* worldpos;

        uiLabel* label;

        bool inRange = false;

        const char* name;
        const char* filePath;
};