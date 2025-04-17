#include "camera.hpp"

camera::camera(float width, float height, float spd)
{
    rec.x = 0 - width/2;
    rec.y = 0 - height/2;
    rec.w = width;
    rec.h = height;

    speed = spd;
}

camera::~camera()
{}

void camera::follow(float x, float y, int mapWidth, int mapHeight)
{
    if(rec.x + rec.w/2 + 100 < x || rec.x + rec.w/2 - 100 > x)
    {
        followX = true;
    }
    else if(x < rec.x + rec.w/2 + 10 && x > rec.x + rec.w/2 - 10)
    {
        followX = false;
    }
    if(rec.y + rec.h/2 + 100 < y || rec.y + rec.h/2 - 100 > y)
    {
        followY = true;
    }
    else if(y < rec.y + rec.h/2 + 10 && y > rec.y + rec.h/2 - 10)
    {
        followY = false;
    }

    if(followX || followY)
    {
        if(followX)
        {
        rec.x -= ((rec.x + rec.w/2) - x)/smoothing * speed;
        if(rec.x < 0)
        {
            rec.x = 0;
        }else if(rec.x + rec.w > mapWidth)
        {
            rec.x = mapWidth - rec.w;
        }
        }
        if(followY)
        {
        rec.y -= ((rec.y + rec.h/2) - y)/smoothing * speed;
        if(rec.y < 0)
        {
            rec.y = 0;
        }
        else if(rec.y + rec.h > mapHeight)
        {
            rec.y = mapHeight - rec.h;
        }
        }
    }
}