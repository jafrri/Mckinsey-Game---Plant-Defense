#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "definitions.hpp"

class Score
{    
    SDL_Renderer* m_pRenderer;
    
    SDL_Texture* m_pTextTexture;
    SDL_Rect fontRect;
    TTF_Font* font;
    // int* turns;

    public:
        Score(SDL_Renderer* renderer);
        ~Score();
        void draw(SDL_Rect* movRect, int number);
        void draw(SDL_Rect* movRect, int number,int dummy);
};