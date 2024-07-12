#pragma once
#include <SDL.h>
#include "button.hpp"
#include "definitions.hpp"

class Instructions
{
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;
    SDL_Texture* m_pTexture_start;
    SDL_Rect screenSrcRect;
    SDL_Rect screenMovRect;
    Button* startButton;

    int m_sWidth, m_sHeight;
    int mouseX = 0, mouseY = 0;

    int* state;

    public:
        Instructions(SDL_Renderer* renderer, SDL_Texture* screenTexture, SDL_Texture* startTexture ,int sWidth, int sHeight, int* State);
        ~Instructions();
        void draw();
        void handleEvents(SDL_Event& event);
};