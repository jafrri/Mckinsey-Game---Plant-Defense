#include "plant.hpp"
#include <iostream>

Plant::Plant(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect movRect)
      :GameObject(renderer, texture, srcRect) 
{
    std::cout << "Initializing Plant\n";
    moverRect = movRect;
}

void Plant::draw()
{   
    GameObject::draw();
}
