#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <ctime> // for time()
#include <cstdlib> // for srand()
#include "mckinseyGame.hpp"

class Game
{
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Event event; // Event Handler
    int m_sWidth, m_sHeight;
    bool m_bRunning;

    MckinseyGame* mckinseyGame;

    public:
        Game(const char* title);
        ~Game();

        bool init(SDL_Window* &window, SDL_Renderer* &renderer, const char* title);
        void play();
        void render();
        void handleEvents(SDL_Event& event);
};