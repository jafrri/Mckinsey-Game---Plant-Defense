#include "startState.hpp"
#include <iostream>

StartState::StartState(SDL_Renderer* renderer, SoundManager* soundManager, SDL_Texture* texture, int sWidth, int sHeight, int* state)
          : m_pRenderer(renderer), soundManager(soundManager), m_pTexture(texture), m_sWidth(sWidth), m_sHeight(sHeight), state(state)
{
    std::cout << "Initializing start state" << std::endl;
    screenSrcRect = {0, 0, 1000, 600};
    screenMovRect = {0, 0, sWidth, sHeight};

    int sbWidth = 292, sbHeight = 95;
    int x = sWidth/2 - sbWidth/2;
    int y = sHeight/2;
    startButton = new Button(renderer, texture, &mouseX, &mouseY, 1001, 1, 1001, 96, x, y, sbWidth, sbHeight);
    
    int ibWidth = 241, ibHeight = 77;
    x = sWidth/2 - ibWidth/2;
    y = sHeight/2 + sbHeight + 40;
    insButton = new Button(renderer, texture, &mouseX, &mouseY, 1001, 191, 1001, 271, x, y, ibWidth, ibHeight);

    std::cout << "Playing Sound" << std::endl;
    soundManager->playMusic("START_MUSIC", -1);
    std::cout << "Start playing playstate music" << std::endl;
}


void StartState::draw()
{
    SDL_RenderCopy(m_pRenderer, m_pTexture, &screenSrcRect, &screenMovRect);
    startButton->draw();
    insButton->draw();
}

void StartState::handleEvents(SDL_Event& event)
{
    if(event.type == SDL_MOUSEMOTION)
    {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }

    if(event.type == SDL_MOUSEBUTTONDOWN & startButton->hover())
    {
        *state = PLAY;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN & insButton->hover()){
        *state= INSTRUCTIONS;
    }
}

StartState::~StartState()
{
    std::cout << "Stopped playing music" << std::endl;
    Mix_PauseMusic();
    Mix_HaltMusic();
    delete startButton;
    delete insButton;
    startButton = nullptr;
    insButton = nullptr;
}