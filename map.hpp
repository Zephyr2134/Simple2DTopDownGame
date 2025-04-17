#pragma once
#include "camera.hpp"
#include "vector2d.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <fstream>

class map
{
public:
    map(SDL_Renderer* ren, const char* mapFilepath, int rows, int collumns, int scale);
    ~map();

    void addTile(SDL_Renderer* ren, const char* filepath);

    void draw(SDL_Renderer* ren, camera* cam);

    int width(){return mapWidth;}
    int height(){return mapHeight;}

private:
    std::vector<std::vector<int>*> grid;
    int mapRows;
    int mapCollumns;

    int mapWidth;
    int mapHeight;
    vector2d* worldPos;

    SDL_Texture* grass;
    SDL_FRect tilePlacement = {0,0,50,50};
    std::vector<SDL_Texture*> tiles;
};