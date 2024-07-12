#pragma once
#include <SDL.h>

class GameObject
{
    //This is the main class from which all the objects such as protectors , obstacles and plant have been inherited. 
    SDL_Texture* m_pTexture;
    SDL_Rect srcRect;

    public:
        SDL_Rect moverRect;
        GameObject(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect);
        virtual ~GameObject();
        
        virtual void draw(SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0);

    protected:
        SDL_Renderer* m_pRenderer;
};