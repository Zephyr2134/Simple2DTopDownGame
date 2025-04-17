#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "camera.hpp"
#include "vector2d.hpp"
#include "map.hpp"
#include "player.hpp"
#include "egg.hpp"
#include "inventory.hpp"

class game
{
public:

    game(const char* title, int width, int height, bool fullscreen);
    ~game();

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running(){return isRunning;}

private:

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int flags = 0;

    map* gameMap;

    int winWidth;
    int winHeight;
    camera* cam;

    bool isRunning = true;

    player* character;
    inventory* characterInventory;

    std::vector<egg*> eggs;
};