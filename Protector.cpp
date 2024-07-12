#include "Protector.hpp"

Protector::Protector(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect movRect)
      :GameObject(renderer, texture, srcRect) 
{
    moverRect = movRect;
}

void Protector::draw()
{   
    GameObject::draw();
}

void Protector::draw(Grid* &grid)//overloaded draw function to implement the highlight function in its child classes. highlight function requires grid to read data from it.
{
    GameObject::draw();
}

bool Protector::is_ingrid(int shiftRow, int shiftCol){//checks whether the protector attack region is in playable region or not.
    if(row && col && (row+shiftRow>0 && row+shiftRow<ROWS-1) && (col+shiftCol>0 && col+shiftCol<COLUMNS-1)){
        return(true);
    }
    else{
        return(false);
    }
}
Protector::~Protector(){};