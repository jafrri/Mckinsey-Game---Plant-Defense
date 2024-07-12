#include "gameOverState.hpp"
#include <iostream>

GameOverState::GameOverState(SDL_Renderer* renderer, SDL_Texture* screenTexture, SDL_Texture* startTexture, int sWidth, int sHeight, int* State, int m_tileWidth, int m_tileHeight, int  nRows , int  nCols)
          : m_pRenderer(renderer), m_pTexture(screenTexture),m_pTexture_start(startTexture), m_sWidth(sWidth), m_sHeight(sHeight), state(State), tileWidth(m_tileWidth), tileHeight(m_tileHeight), rows(nRows), columns(nCols)
{
    std::cout << "Initializing start state" << std::endl;
    screenSrcRect = {0, 0, 1000, 600};
    screenMovRect = {0, 0, sWidth, sHeight};

    int sbWidth = 292, sbHeight = 95;
    int x = sWidth/2 - sbWidth/2;
    int y = 3*(sHeight/4);
    startButton = new Button(renderer, startTexture, &mouseX, &mouseY, 1001, 1, 1001, 96, x, y, sbWidth, sbHeight);
    
    display = new Score(renderer); 


}

void GameOverState::draw()
{
    SDL_RenderCopy(m_pRenderer,m_pTexture,&screenMovRect,&screenMovRect);
    // SDL_RenderCopy(m_pRenderer, m_pTexture_start, &screenSrcRect, &screenMovRect);
    startButton->draw();
    SDL_Rect movRect={((columns/2)-1.5) * tileWidth , 2*tileHeight , tileWidth * 3, tileHeight};
    display->draw(&movRect,PlayState::turns);
}

void GameOverState::handleEvents(SDL_Event& event)
{
    if(event.type == SDL_MOUSEMOTION)
    {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }

    if(event.type == SDL_MOUSEBUTTONDOWN & startButton->hover())
    {
        *state = START;
    }
}


GameOverState::~GameOverState() 
{
    m_pRenderer = nullptr;
    m_pTexture = nullptr;
    m_pTexture_start=nullptr;

    delete startButton;
    startButton=nullptr;

    delete display;
    display = nullptr;
    
    PlayState::turns=0;
}