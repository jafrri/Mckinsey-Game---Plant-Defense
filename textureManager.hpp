#pragma once
#include <SDL.h>
#include <map>
#include <string>

class TextureManager
{
    SDL_Renderer* m_pRenderer;
    public:
        std::map<std::string, SDL_Texture*> textureMap;
        TextureManager(SDL_Renderer* renderer);
        bool init();
        bool loadTexture(const char* filename, std::string ID);
};