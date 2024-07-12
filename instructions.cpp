#include "instructions.hpp"
#include <iostream>

Instructions::Instructions(SDL_Renderer* renderer, SDL_Texture* screenTexture, SDL_Texture* startTexture, int sWidth, int sHeight, int* State)
          : m_pRenderer(renderer), m_pTexture(screenTexture),m_pTexture_start(startTexture), m_sWidth(sWidth), m_sHeight(sHeight), state(State)
{
    std::cout << "Initializing start state" << std::endl;
    screenSrcRect = {0, 0, 1000, 600};
    screenMovRect = {0, 0, sWidth, sHeight};

    int sbWidth = 292, sbHeight = 95;
    int x = sWidth/2 - sbWidth/2;
    int y = 5*(sHeight/6);
    
    startButton = new Button(renderer, startTexture, &mouseX, &mouseY, 1001, 1, 1001, 96, x, y, sbWidth, sbHeight);
    


}

void Instructions::draw()
{
    SDL_RenderCopy(m_pRenderer,m_pTexture,&screenMovRect,&screenMovRect);
    // SDL_RenderCopy(m_pRenderer, m_pTexture_start, &screenSrcRect, &screenMovRect);
    startButton->draw();
}

void Instructions::handleEvents(SDL_Event& event)
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


Instructions::~Instructions() 
{
    m_pRenderer = nullptr;
    m_pTexture = nullptr;
    m_pTexture_start=nullptr;

    delete startButton;
    startButton=nullptr;
}