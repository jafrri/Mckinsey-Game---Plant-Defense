#include "Obstacle.hpp"
#include <iostream>

Obstacle::Obstacle(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect movRect)
      :GameObject(renderer, texture, srcRect) 
{
    moverRect = movRect;//moverRect for the obstacle.
}

void Obstacle::draw()
{   
    GameObject::draw();
}

