#include "zombie.hpp"


Zombie::Zombie(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect movRect):
Protector(renderer, texture, SDL_Rect({6, 385, 327, 276}), movRect){
    // this->maxZombies=maxZombies;
    count++;
    display=new Score(renderer);
}


void Zombie::draw()
{
    Protector::draw();
SDL_Rect display_rect={moverRect.x,moverRect.y-(moverRect.h/3),(moverRect.w/3),(moverRect.h/3)};
    display->draw(&display_rect,Zombie::maxZombies-Zombie::count,0);
}
void Zombie::draw(Grid* &grid){
    highlight(grid);
    Protector::draw();   
}

void Zombie::attack(Grid* &grid)
{
    int r=moverRect.y/moverRect.h;
    int c=moverRect.x/moverRect.w;

    if (grid->grid[r][c].enemy){
        grid->grid[r][c].damage+=damage;
    }

    if(r-1>0 && (grid->grid[r-1][c].enemy))
    {
        grid->grid[r-1][c].damage+=damage;
    }
    if(r+1<ROWS && (grid->grid[r+1][c].enemy))
    {
        grid->grid[r+1][c].damage+=damage;
    }
    if(c-1>0 && (grid->grid[r][c-1].enemy))
    {
        grid->grid[r][c-1].damage+=damage;
    }
    if(c+1<COLUMNS && (grid->grid[r][c+1].enemy))
    {
        grid->grid[r][c+1].damage+=damage;
    }
}
void Zombie::highlight(Grid* &grid){
    shadeRect = {col * moverRect.w , row * moverRect.h, moverRect.w , moverRect.h};
    if(is_ingrid(0,0)){
        SDL_SetRenderDrawColor(m_pRenderer, 200, 50, 0, 90);

        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    
    if(is_ingrid(0, 1) && grid->grid[row][col+1].obstacle==false && grid->grid[row][col+1].plant==false)
    {
        shadeRect.x = (col+1) * moverRect.w;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(0, -1) && grid->grid[row][col-1].obstacle==false && grid->grid[row][col-1].plant==false)
    {
        shadeRect.x = (col-1) * moverRect.w;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(-1, 0) && grid->grid[row-1][col].obstacle==false && grid->grid[row-1][col].plant==false)
    {
        shadeRect.x = col * moverRect.w;
        shadeRect.y = (row-1) * moverRect.h;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(1, 0) && grid->grid[row+1][col].obstacle==false && grid->grid[row+1][col].plant==false)
    {
        shadeRect.x = col * moverRect.w;
        shadeRect.y = (row+1) * moverRect.h;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
}
void Zombie::set_count(int num){
    count=num;
}

Zombie::~Zombie(){
    count--;
    
    delete display;
    display=nullptr;
};