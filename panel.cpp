#include "panel.hpp"
#include <iostream>

Panel::Panel(SDL_Renderer* pRenderer, SDL_Texture* pTexture, int tileWidth, int tileHeight)
: m_pRenderer(pRenderer)
{
    //the position of the panel objects are set.
    zRow = 5, zCol = 0;
    eRow = 7, eCol = 0;
    sRow = 9, sCol = 0;
    //moverrect for different panel objects.
    SDL_Rect zombieLoc = {0, zRow * tileHeight, tileWidth, tileHeight};
    SDL_Rect eagleLoc = {0, eRow * tileHeight, tileWidth, tileHeight};
    SDL_Rect snakeLoc = {0, sRow * tileHeight, tileWidth, tileHeight};

    zombie = new Zombie(pRenderer, pTexture, zombieLoc);
    eagle = new Eagle(pRenderer, pTexture, eagleLoc);
    snake = new Snake(pRenderer, pTexture, snakeLoc);
}

void Panel::draw()//this function draws the panel on the screen.
{
    SDL_SetRenderDrawColor(m_pRenderer, 220, 220, 220, 100);
    SDL_RenderFillRect(m_pRenderer, &zombie->moverRect);
    SDL_RenderFillRect(m_pRenderer, &eagle->moverRect);
    SDL_RenderFillRect(m_pRenderer, &snake->moverRect);
    zombie->draw();
    eagle->draw();
    snake->draw();
}
Panel::~Panel(){
    delete zombie;
    delete eagle;
    delete snake;

    zombie=nullptr;
    eagle=nullptr;
    snake=nullptr;
}