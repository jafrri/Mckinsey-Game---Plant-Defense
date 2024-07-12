#pragma once
#include <SDL.h>
#include "gameObject.hpp"

class Plant : public GameObject
{
    public:
        Plant(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect,  SDL_Rect movRect);
        void draw();
};
