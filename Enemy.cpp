#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect movRect, Grid* grid, int rows, int cols, int plantRow, int plantCol, int health)
      : Animal(renderer, texture, srcRect, movRect), grid(grid), rows(rows), cols(cols), plantRow(plantRow), plantCol(plantCol), health(health)
{
    updatePath();

    display=new Score(renderer);
    
}

void Enemy::updatePath()//this function updates the path of the enemy that it will take to reach the plant.
{
    path = wavePropagationPathFind(grid->getGrid(), rows, cols, moverRect.y/moverRect.h, moverRect.x/moverRect.w, plantRow, plantCol);
}

void Enemy::move()//this function moves the enemy by changing its moverrect by reading the postion from the path vector,
//which stores the path in form of rows and cols.
{
    if (path.size()) // Move only if path exists.
    {
        moverRect.y = path[0].r * moverRect.h;
        moverRect.x = path[0].c * moverRect.w;
        path.erase(path.begin()); // pop the front element of the path vector.
    }
}

void Enemy::draw()//this function draws the enemies on the screen.
{    
    if (path.size() && path[0].c - moverRect.x/moverRect.w < 0)//if the path is opposite to the current position of the 
    //enemy that is the path if opposite to the direction in which enemy is facing, then the enemy is flipped to give proper moving animation.
        flip = SDL_FLIP_HORIZONTAL;
    else if (path.size() && path[0].c - moverRect.x/moverRect.w > 0)// but if the direction of facing and next position from path is same then enemy is not flipped.
        flip = SDL_FLIP_NONE;
    highlightPath();//this function highlights the path that the enemy is taking so that player is aware and can 
    //change stategy accordingly.
    
    Animal::draw(flip);//the draw of parent class Animal is called with the flip argument for rendereing on screen.


    SDL_Rect display_rect={moverRect.x,moverRect.y,(moverRect.w/3),(moverRect.h/3)};//this is the moverrect for the display of the 
    //health of enemy at its top left
    display->draw(&display_rect,health,0);// this renders the health of enemy at it's top left.
}

// void Enemy::takeDamage(Grid* &grid)
// {
    
// }

void Enemy:: operator -(Grid* &grid){//this operator overloading takes the grid pointer to read the damage data from it 
//and accordingly subtract the health from the enemy.
    int r=moverRect.y/moverRect.h;
    int c=moverRect.x/moverRect.w;
    
    health=health-grid->grid[r][c].damage;    
}

int Enemy::gethealth()//this returns the current health.
{
    return health;
}


void Enemy::highlightPath()//this function highlights the enemy path to the plant.
{
    SDL_Rect shadeRect = moverRect;
    SDL_SetRenderDrawColor(m_pRenderer, 78, 7, 162, 80);
    for (Node &node: path)
    {
        if ((grid->grid[node.r][node.c].path == false) && (grid->grid[node.r][node.c].plant == false))
        {
            grid->grid[node.r][node.c].path = true;

            shadeRect.x = node.c * moverRect.w;
            shadeRect.y = node.r * moverRect.h;
            SDL_RenderFillRect(m_pRenderer, &shadeRect);
        }
    }
}

Enemy::~Enemy()
{
    delete display;
    display=nullptr;
    // GameObject::~GameObject();
}