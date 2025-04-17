#pragma once
#include <SDL3/SDL.h>
#include "vector2d.hpp"
#include <cmath>

class camera
{
public:
    camera(float width, float height, float spd);
    ~camera();

    SDL_FRect position(){return rec;}

    void follow(float x, float y, int mapWidth, int mapHeight);

private:
    SDL_FRect rec;
    bool followX = false;
    bool followY = false;
    int smoothing = 200;
    float speed = 0;
};