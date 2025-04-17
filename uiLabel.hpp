#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include "vector2d.hpp"
#include "camera.hpp"

class uiLabel
{
    public:

        uiLabel(SDL_Renderer* ren, const char* text, int size, SDL_FRect trnsfrm);
        ~uiLabel();

        void updateText(SDL_Renderer* ren, const char* text);
        void setColor(SDL_Color color);
        void draw(SDL_Renderer* ren, camera* cam);
        void draw(SDL_Renderer* ren);
    private:
        SDL_Texture* textTex;
        TTF_Font* font;
        vector2d* worldpos;
        SDL_FRect transform;
        SDL_Color textColor = {255,255,255,255};
};