#include "cursor.hpp"

Cursor::Cursor(SDL_Renderer* renderer, SDL_Texture* texture)
: GameObject::GameObject(renderer, texture, {0, 0, 64, 64})
{
    moverRect = {0, 0, 40, 40};//initial moverrect of the cursor.
}

void Cursor::draw()
{
    GameObject::draw();
}

void Cursor::update(SDL_Event& event)//the cursor poistion is updateed with the mousemotion
{
    if (event.type == SDL_MOUSEMOTION)
    {
        moverRect.x = event.motion.x;
        moverRect.y = event.motion.y;
    }
}