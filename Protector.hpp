#pragma once
#include <SDL.h>
#include "gameObject.hpp"
#include "grid.hpp"
#include "definitions.hpp"

class Protector : public GameObject
{
    public:
        int row = 0, col = 0;
        Protector(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect,  SDL_Rect movRect);
        virtual void draw();
        virtual void draw(Grid* &grid);
        virtual void attack(Grid* &grid)=0;
        bool is_ingrid(int shift_x, int shift_y);
        virtual ~Protector();
};
