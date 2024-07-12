#include "textureManager.hpp"
#include <SDL_image.h>
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* renderer) : m_pRenderer(renderer)
{
    init();
}

bool TextureManager::init()
{
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == IMG_INIT_PNG | IMG_INIT_JPG)
        return true;

    std::cout << "Error! could not initialize SDL image" << std::endl;
    return false;
}

bool TextureManager::loadTexture(const char* filename, std::string ID)
{
    SDL_Surface* pTempSurface = IMG_Load(filename);

    if(pTempSurface == 0)
        return false;

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    
    if (pTexture == NULL)
        return false;

    SDL_FreeSurface(pTempSurface);
    textureMap[ID] = pTexture; // Add texture in the texture map upon successful creation.

    return true;
}
