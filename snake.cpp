#include "snake.hpp"

Snake::Snake(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect movRect):
Protector(renderer, texture, SDL_Rect({0, 3, 241, 340}), movRect){
    count++;
    display= new Score(renderer);
}


void Snake::draw()
{
    Protector::draw();

    SDL_Rect display_rect={moverRect.x,moverRect.y-(moverRect.h/3),(moverRect.w/3),(moverRect.h/3)};// moverrect for display of number of snakes left available
    display->draw(&display_rect,Snake::maxSnakes-Snake::count,0); //this displays the quantity of the snake at top left of eagle.
}
void Snake::draw(Grid* &grid){
    highlight(grid);
    Protector::draw();   
}

void Snake::attack(Grid* &grid)
{
    int r=moverRect.y/moverRect.h;
    int c=moverRect.x/moverRect.w;

    if (grid->grid[r][c].enemy)
        grid->grid[r][c].damage+=damage;
    if(c+1 < COLUMNS && (grid->grid[r][c+1].enemy))
        grid->grid[r][c+1].damage+=damage;
    if(c-1 > 0 && (grid->grid[r][c-1].enemy))
        grid->grid[r][c-1].damage+=damage;
}

void Snake::highlight(Grid* &grid)//the attack implementation of snake in horizontal direction is implemented here.
{
    shadeRect = {col * moverRect.w , row * moverRect.h, moverRect.w , moverRect.h};

        SDL_SetRenderDrawColor(m_pRenderer, 200, 50, 0, 90);
    if(is_ingrid(0,0))
    {
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(0,1) && grid->grid[row][col+1].obstacle==false && grid->grid[row][col+1].plant==false)
    {
        shadeRect.x = (col+1) * moverRect.w;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(0,-1) && grid->grid[row][col-1].obstacle==false && grid->grid[row][col-1].plant==false)
    {
        shadeRect.x = (col-1) * moverRect.w;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
}

void Snake::set_count(int num){//static function definition to set the count to argument value num.
    count=num;
}

Snake::~Snake(){
    count--;

    delete display;
    display=nullptr;
};