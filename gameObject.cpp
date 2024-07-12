#include "gameObject.hpp"
#include<iostream>

GameObject::GameObject(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect)
      : m_pRenderer(renderer), m_pTexture(texture), srcRect(srcRect)
{}

void GameObject::draw(SDL_RendererFlip flip, double angle)
{
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &srcRect, &moverRect, angle, NULL, flip);
}

GameObject::~GameObject()
{
    m_pRenderer = nullptr;
    m_pTexture = nullptr;
    std::cout<<"Destructing objects"<<std::endl;
}