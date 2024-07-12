#include "game.hpp"
#include <iostream>

Game::Game(const char* title)
{
    if (init(m_pWindow, m_pRenderer, title));
}

bool Game::init(SDL_Window* &window, SDL_Renderer* &renderer, const char* title)
{
    bool success = false; // Indicates whether initialization was successful or not.

    srand(time(NULL)); //Provide starting time as the seed for random generator.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
    {
        std::cout << "SDL init success\n";
        // init the window
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);

        m_sWidth = DM.w; m_sHeight = DM.h;

        m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_sWidth, m_sHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if(m_pWindow != nullptr)
        {
            std::cout << "window creation successful\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC); // Vsync enabled.

            if(m_pRenderer != nullptr)
            {
                std::cout << "Renderer creation successful\n";
                SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
                
                success = true;
            }
            else
            {
                std::cout << "Renderer creation unsuccessful\n";
            }
        }
        else
        {
            std::cout << "Window creation unsuccessful\n";
        }
    }
    else
    {
        std::cout << "SDL initialization unsuccessful\n";
    }

    std::cout << "Initialization successful\n";
    m_bRunning = true; // Start the game loop if initialization wasa successful.

    if ( TTF_Init() < 0 ) {
        std::cout << "Error initializing SDL_ttf: \n";
        success = false;
    }

    return success;
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);
    mckinseyGame->draw(); //draw for mckinsey getting called
    SDL_RenderPresent(m_pRenderer);
}

void Game::play()
{
    SDL_Event event;

    mckinseyGame = new MckinseyGame(m_pRenderer, m_sWidth, m_sHeight, ROWS, COLUMNS);

    while (m_bRunning)
    {
        mckinseyGame->manageState();
        render();
        handleEvents(event);
    }
}

void Game::handleEvents(SDL_Event& event)
{   
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                m_bRunning = false;
            break;
        }
        mckinseyGame->handleEvents(event);
    }
}

Game::~Game()
{
    std::cout << "quitting game...\n";
    delete mckinseyGame;
    mckinseyGame = nullptr;
    SDL_DestroyWindow(m_pWindow); // Destroy the window since it was dynamically created.
    SDL_DestroyRenderer(m_pRenderer); // Destroy the renderer since it was dynamically created.
    TTF_Quit();
    SDL_Quit();
}