#pragma once
#include <SDL.h>


class Button
{   
    SDL_Texture* pButtonTexture;
    SDL_Renderer* pRenderer;
    SDL_Rect srcRect1;
    SDL_Rect srcRect2;
    SDL_Rect movRect;

    int *pMouseX, *pMouseY;
    bool pointed = false;
    
    void check();

    public:
        Button(SDL_Renderer* renderer, SDL_Texture* texture, int* pMouseX, int* pMouseY, int s1x, int s1y, int s2x, int s2y, int posx, int posy, int width, int height);
        
        void draw();
        bool hover();
};