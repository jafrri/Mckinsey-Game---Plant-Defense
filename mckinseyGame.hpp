#pragma once
#include <SDL.h>
#include "textureManager.hpp"
#include "soundManager.hpp"
#include "startState.hpp"
#include "playState.hpp"
#include "instructions.hpp"
#include "gameOverState.hpp"
#include "cursor.hpp"

class MckinseyGame
{
    SDL_Renderer* m_pRenderer;
    TextureManager* textures;
    SoundManager* soundManager;

    StartState* startState;
    PlayState* playState;
    GameOverState* overState;
    Instructions* instrucState;

    Cursor* cursor;

    int state = START;
    int prevState = START;

    int m_sWidth, m_sHeight;
    int m_tileWidth, m_tileHeight;
    int nRows, nCols;

    public:
        MckinseyGame(SDL_Renderer* renderer, int sWidth, int sHeight, int nRows, int nCols);
        ~MckinseyGame();
        void init();
        void manageState();
        void loadAssets();
        void freeAssets();
        void draw();
        void handleEvents(SDL_Event& event);

};