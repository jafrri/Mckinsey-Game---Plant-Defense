#include "Animal.hpp"

Animal::Animal(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect movRect)
      :GameObject(renderer, texture, srcRect)
{
    moverRect = movRect;
}

void Animal::draw(SDL_RendererFlip flip, double angle)
{   
    GameObject::draw(flip, angle);
}
// Animal::~Animal(){
//     GameObject::~GameObject();
// }