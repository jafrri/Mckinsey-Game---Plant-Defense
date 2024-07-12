#include "Eagle.hpp"

Eagle::Eagle(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect movRect):
Protector(renderer, texture, SDL_Rect({386,369,326,309}), movRect) {
    count++;//count is incremented as eagle object is constructed to keep count of number of eagle objects created.
    display=new Score(renderer);
}


void Eagle::draw(){
    Protector::draw();

    SDL_Rect display_rect={moverRect.x,moverRect.y-(moverRect.h/3),(moverRect.w/3),(moverRect.h/3)};// moverrect for display of number of eagles left available
    display->draw(&display_rect,Eagle::maxEagles-Eagle::count,0);//this displays the quantity of the eagle at top left of eagle.

}
void Eagle::draw(Grid* &grid){
    highlight(grid);
    Protector::draw();   
}

void Eagle::attack(Grid* &grid)//the attack implementation of eagle in diagonal direction is implemented here.
{
    int r=moverRect.y/moverRect.h;
    int c=moverRect.x/moverRect.w;

    if (grid->grid[r][c].enemy){
        grid->grid[r][c].damage+=damage;
    }


    // std::cout<<"Top Left Damage " << (r-1>0 && c-1>0 && (grid->grid[r-1][c-1].enemy)) <<std::endl;
    if(r-1>0 && c-1>0 && (grid->grid[r-1][c-1].enemy))
    {
        grid->grid[r-1][c-1].damage+=damage;
    }
    // std::cout<<"Top Right Damage"<< (r-1>0 && c+1<COLUMNS && (grid->grid[r-1][c+1].enemy)) << std::endl;
    if(r-1>0 && c+1 < COLUMNS && (grid->grid[r-1][c+1].enemy))
    {
        grid->grid[r-1][c+1].damage+=damage;
    }
    // std::cout<<"Bottom Left Damage"<< (r+1<ROWS && c-1>0 && (grid->grid[r+1][c-1].enemy)) << std::endl;
    if(r+1<ROWS && c-1>0 && (grid->grid[r+1][c-1].enemy))
    {
        grid->grid[r+1][c-1].damage+=damage;
    }
    // std::cout<<"Bottom Right Damage"<< (r+1<ROWS && c+1<COLUMNS && (grid->grid[r+1][c+1].enemy)) << std::endl;
    if(r+1<ROWS && c+1<COLUMNS && (grid->grid[r+1][c+1].enemy))
    {
        grid->grid[r+1][c+1].damage+=damage;
    }
}

void Eagle::highlight(Grid* &grid){//this function highlights the attack region of the eagle.
    shadeRect = {col * moverRect.w , row * moverRect.h, moverRect.w , moverRect.h};
    SDL_SetRenderDrawColor(m_pRenderer, 200, 50, 0, 90);

    if(is_ingrid(0,0))
    {
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(1,1) && grid->grid[row+1][col+1].obstacle==false && grid->grid[row+1][col+1].plant==false)
    {
        shadeRect.x = (col+1) * moverRect.w; 
        shadeRect.y = (row+1) * moverRect.h;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(1,-1) && grid->grid[row+1][col-1].obstacle==false && grid->grid[row+1][col-1].plant==false){
        shadeRect.x = (col-1) * moverRect.w;
        shadeRect.y = (row+1) * moverRect.h;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(-1,-1) && grid->grid[row-1][col-1].obstacle==false && grid->grid[row-1][col-1].plant==false){
        shadeRect.x = (col-1) * moverRect.w;
        shadeRect.y = (row-1) * moverRect.h;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
    if(is_ingrid(-1,1) && grid->grid[row-1][col+1].obstacle==false && grid->grid[row-1][col+1].plant==false){
        shadeRect.x = (col+1) * moverRect.w;
        shadeRect.y = (row-1) * moverRect.h;
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
}

void Eagle::set_count(int num){//static function definition to set the count to argument value num.
    count=num;
}

Eagle::~Eagle(){
    count--;

    delete display;
    display=nullptr;
};