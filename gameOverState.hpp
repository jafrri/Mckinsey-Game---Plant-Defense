#pragma once
#include <SDL.h>
#include "button.hpp"
#include "definitions.hpp"
#include "score.hpp"
#include "playState.hpp"
class GameOverState
{
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;
    SDL_Texture* m_pTexture_start;
    SDL_Rect screenSrcRect;
    SDL_Rect screenMovRect;
    Button* startButton;

    int rows, columns; // Total Rows and Columns in the grid.
    int tileWidth, tileHeight;

    int m_sWidth, m_sHeight;
    int mouseX = 0, mouseY = 0;

    int* state;

    Score* display;

    public:
        GameOverState(SDL_Renderer* renderer, SDL_Texture* screenTexture, SDL_Texture* startTexture ,int sWidth, int sHeight, int* State, int m_tileWidth, int m_tileHeight , int nRows, int nCols);
        ~GameOverState();
        void draw();
        void handleEvents(SDL_Event& event);
};