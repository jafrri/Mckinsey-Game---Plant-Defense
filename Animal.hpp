#pragma once
#include <SDL.h>
#include "gameObject.hpp"

class Animal : public GameObject
{
    public:
        Animal(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect,  SDL_Rect movRect);
        // ~Animal();

        virtual void draw(SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0);
};
