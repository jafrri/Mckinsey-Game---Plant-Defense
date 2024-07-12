#pragma once
// #include "Protector.hpp"
// #include "button.hpp"
#include "zombie.hpp"
#include "snake.hpp"
#include "eagle.hpp"
// this class is used to display the side panel of the protectors.
class Panel
{
    SDL_Renderer* m_pRenderer;
    //pointers to the zombie, snake and eagle class object.
    Zombie* zombie;
    Snake* snake;
    Eagle* eagle;

    //row and columns for zombie,eagle and snake.
    public:
        int zRow, zCol,
            eRow, eCol,
            sRow, sCol;
        
        Panel(SDL_Renderer* pRenderer, SDL_Texture* pTexture, int tileWidth, int tileHeight);
        ~Panel();
        void draw();
};