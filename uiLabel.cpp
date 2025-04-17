#include "uiLabel.hpp"
#include <iostream>

uiLabel::uiLabel(SDL_Renderer* ren, const char* text, int size, SDL_FRect trnsfrm)
{
    font = TTF_OpenFont("ARIAL.TTF", size);
    if(!font)
    {
        std::cout << "failed to load font" << std::endl;
    }
    SDL_Surface* tmpSurf = TTF_RenderText_Solid(font, text, strlen(text), textColor);
    textTex = SDL_CreateTextureFromSurface(ren, tmpSurf);
    SDL_DestroySurface(tmpSurf);
    SDL_SetTextureScaleMode(textTex, SDL_SCALEMODE_NEAREST);

    worldpos = new vector2d(trnsfrm.x,trnsfrm.y);
    transform = trnsfrm;
}

uiLabel::~uiLabel()
{}

void uiLabel::updateText(SDL_Renderer* ren, const char* newText)
{
    SDL_Surface* tmp = TTF_RenderText_Solid(font, newText, strlen(newText), textColor);
    textTex = SDL_CreateTextureFromSurface(ren, tmp);
    SDL_DestroySurface(tmp);
    SDL_SetTextureScaleMode(textTex, SDL_SCALEMODE_NEAREST);
}

void uiLabel::setColor(SDL_Color color)
{
    textColor = color;
}

void uiLabel::draw(SDL_Renderer* ren)
{
    SDL_RenderTexture(ren, textTex, NULL, &transform);
}

void uiLabel::draw(SDL_Renderer* ren, camera* cam)
{
    transform.x = worldpos->getX() - cam->position().x;
    transform.y = worldpos->getY() - cam->position().y;

    SDL_RenderTexture(ren, textTex, NULL, &transform);
}