#include "inventory.hpp"
#include <string>

inventory::inventory(SDL_Renderer *ren, camera* cam)
{
    container = {50, 50, cam->position().w - 100, cam->position().h - 100};
    sizeX = container.w / 50 - 1;
    label = new uiLabel(ren, (std::to_string(boxOfThings.size()) + "/" + std::to_string(capasity)).c_str(), 24, {60,60,100,100});
}

inventory::~inventory()
{}

void inventory::addItem(SDL_Renderer* ren, const char* name, const char* filepath)
{
    boxOfThings.push_back(new inventoryItem(ren, name, filepath));
    if(boxOfThings.size() == capasity)
    {
        label->setColor({255,0,0,255});
    }   
    else
    {
        label->setColor({255,255,255,255});
    }
    label->updateText(ren, (std::to_string(boxOfThings.size()) + "/" + std::to_string(capasity)).c_str());
}

void inventory::interactInventory()
{
    if(open)
    {
        open = false;
    }else
    {
        open = true;
    }
}

void inventory::draw(SDL_Renderer* ren)
{
    if(open)
    {
    SDL_SetRenderDrawColor(ren, 0,0,0,150);
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(ren, &container);
    int x = 0;
    int y = 0;
    for(inventoryItem* item : boxOfThings)
    {
        if(x!=0 && x%sizeX == 0)
        {
            x -= sizeX;
            y++;
        }
        item->draw(ren, x, y);
        x += 1;
    }
    label->draw(ren);
}
}