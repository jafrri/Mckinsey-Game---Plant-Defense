#pragma once
#include <SDL.h>
#include "button.hpp"
#include "definitions.hpp"
#include "soundManager.hpp"

class StartState
{
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;
    SDL_Rect screenSrcRect;
    SDL_Rect screenMovRect;
    Button* startButton;
    Button* insButton;

    SoundManager* soundManager;

    int m_sWidth, m_sHeight;
    int mouseX = 0, mouseY = 0;

    int* state;

    public:
        StartState(SDL_Renderer* renderer, SoundManager* soundManager, SDL_Texture* screenTexture, int sWidth, int sHeight, int* state);
        ~StartState();
        void draw();
        void handleEvents(SDL_Event& event);
};