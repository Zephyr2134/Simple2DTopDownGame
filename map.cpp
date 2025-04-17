#include "map.hpp"
#include <iostream>

map::map(SDL_Renderer* ren, const char* mapFilepath, int rows, int collumns, int scale)
{

    addTile(ren, "Assets/Map/water.png");
    addTile(ren, "Assets/Map/Grass.png");

    mapRows = rows;
    mapCollumns = collumns;

    tilePlacement.w = scale;
    tilePlacement.h = scale;

    mapWidth = mapRows * scale;
    mapHeight = mapCollumns * scale;

    std::fstream mapFile;
    mapFile.open(mapFilepath);
    char character;

    for(int i = 0; i < mapCollumns; i++)
    {
        grid.push_back(new std::vector<int>);
        for(int x = 0; x < mapRows; x++)
        {
            mapFile.get(character);
            mapFile.ignore();
            grid[i]->push_back(character - '0');
        }
    }
    mapFile.close();
}

map::~map()
{}

void map::addTile(SDL_Renderer* ren, const char* filepath)
{
    SDL_Surface* tmp = IMG_Load(filepath);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmp);
    SDL_DestroySurface(tmp);
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    tiles.push_back(tex);
}

void map::draw(SDL_Renderer* ren, camera* cam)
{
    for(int y = 0;y < mapCollumns; y++)
    {
        tilePlacement.y = (y * tilePlacement.h) - cam->position().y;
        for(int x = 0;x < mapRows;x++)
        {
            tilePlacement.x = (x * tilePlacement.w) - cam->position().x;
            SDL_RenderTexture(ren, tiles[grid[y]->at(x)], NULL, &tilePlacement);
        }
    }
}