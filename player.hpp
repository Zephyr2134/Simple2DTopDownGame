#pragma once
#include "vector2d.hpp"
#include "camera.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class player
{
public:
    player(SDL_Renderer* renderer, const char* textureFilepath, float xpos, float ypos);
    ~player();

    void handleEvents(SDL_Event event);
    void move();
    void render(SDL_Renderer* renderer, camera* cam);

    float middleX(){return worldPos->getX() + dstRect.w/2;}
    float middleY(){return worldPos->getY() + dstRect.h/2;}
    float getSpeed(){return baseSpeed;}

    int pickupRad(){return pickupRadius;}

private:
    vector2d* worldPos;
    SDL_FRect dstRect = {0,0,100,100};

    float speed = 6.0f;
    float baseSpeed = 6.0f;
    float angledSpeed = 6/1.414f;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    SDL_FRect camPos;

    SDL_Texture* playerTex;

    int pickupRadius = 150;
};