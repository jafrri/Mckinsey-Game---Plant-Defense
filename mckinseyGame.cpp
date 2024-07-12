#include "mckinseyGame.hpp"

MckinseyGame::MckinseyGame(SDL_Renderer* renderer, int sWidth, int sHeight, int nRows, int nCols) 
             : m_pRenderer(renderer), m_sWidth(sWidth), m_sHeight(sHeight), nRows(nRows), nCols(nCols)
{
    m_tileHeight = sHeight / nRows;
    m_tileWidth = sWidth / nCols + 1; // Ceil division.

    textures = new TextureManager(m_pRenderer);//Intializing the textures.
    soundManager = new SoundManager();//Intialzing the sound.
    init();   
}

void MckinseyGame::init()
{
    loadAssets();//initliazing the assets

    cursor = new Cursor(m_pRenderer, textures->textureMap["CURSOR"]);//Intializing the cursor.
    SDL_ShowCursor(SDL_DISABLE); // Hide the default cursor.
}

void MckinseyGame::loadAssets()//the textures are loaded from the assets file.
{
    textures->loadTexture("Assets/grass_texture.png", "GRASS_TEXTURE");
    textures->loadTexture("Assets/start_screen.png", "START_SCREEN");
    textures->loadTexture("Assets/game_over.png", "GAME_OVER_SCREEN");
    textures->loadTexture("Assets/plant.png","PLANT");
    textures->loadTexture("Assets/cursor.png","CURSOR");
    textures->loadTexture("Assets/obstacles.png","OBSTACLES");
    textures->loadTexture("Assets/enemies.png","ENEMIES");
    textures->loadTexture("Assets/protectors.png","PROTECTORS");
    textures->loadTexture("Assets/pause.png","PAUSE");
    textures->loadTexture("Assets/instructions.png","INSTRUCTIONS");

    soundManager->load("Assets/start.wav", "START_MUSIC", SOUND_MUSIC);
    soundManager->load("Assets/play.wav", "PLAY_MUSIC", SOUND_MUSIC);
}

void MckinseyGame::manageState()
{
    if (state != prevState)//checks whether the previous state is not equal to the current state and only then proceeds.
    {
        switch(prevState)//uses switch cases and deletes the previous state and sets it's pointer to nullptr.
        {
            case START:
                delete startState;
                startState = nullptr;
            break;

            case PLAY:
                delete playState;
                playState = nullptr;
            break;

            case OVER:
                delete overState;
                overState = nullptr;
            break; 
            case INSTRUCTIONS:
                delete instrucState;
                instrucState = nullptr;
            break;
            
        }
        prevState = state;// after this updates the previous state to current state and the code below then updates the current sta
    }
    //This initializes the corresponding state(startState,playState etc.) dynamically after checking the state variable.
    if (state == START && startState == nullptr)
        startState = new StartState(m_pRenderer, soundManager, textures->textureMap["START_SCREEN"], m_sWidth, m_sHeight, &state);

    else if (state == PLAY && playState == nullptr)
        playState = new PlayState(m_pRenderer, soundManager, m_tileWidth, m_tileHeight, nRows, nCols, textures->textureMap["GRASS_TEXTURE"], textures->textureMap["PLANT"],  textures->textureMap["ENEMIES"], textures->textureMap["PROTECTORS"], textures->textureMap["OBSTACLES"], textures->textureMap["PAUSE"],&state);

    else if (state == OVER && overState == nullptr)
        overState = new GameOverState(m_pRenderer, textures->textureMap["GAME_OVER_SCREEN"], textures->textureMap["START_SCREEN"], m_sWidth, m_sHeight, &state , m_tileWidth , m_tileHeight , nRows, nCols);

    else if (state == INSTRUCTIONS && instrucState == nullptr){
        instrucState = new Instructions(m_pRenderer, textures->textureMap["INSTRUCTIONS"], textures->textureMap["START_SCREEN"], m_sWidth, m_sHeight,&state);
    }
}

void MckinseyGame::draw()
{
    switch(state)
    {
        case START:
            startState->draw();
        break;
        case PLAY:
            playState->draw();
        break;
        case OVER:
            overState->draw();
        break;
        case INSTRUCTIONS:
            instrucState->draw();
        break;
    }  
    cursor->draw(); //Draw the cursor last, so it draws over everything else.
}

void MckinseyGame::handleEvents(SDL_Event& event)
{
    cursor->update(event);
    switch(state)
    {
        case START:
            if (startState)
                startState->handleEvents(event);
        break;
        case PLAY:
            if (playState)
                playState->handleEvents(event);
        break;
        case OVER:
            if (overState)
                overState->handleEvents(event);
        break;
        case INSTRUCTIONS:
            if(instrucState)
                instrucState->handleEvents(event);
    }
}

void MckinseyGame::freeAssets()//the textures are loaded from the assets file.
{
    SDL_DestroyTexture(textures->textureMap["GRASS_TEXTURE"]);
    SDL_DestroyTexture(textures->textureMap["START_SCREEN"]);
    SDL_DestroyTexture(textures->textureMap["GAME_OVER_SCREEN"]);
    SDL_DestroyTexture(textures->textureMap["PLANT"]);
    SDL_DestroyTexture(textures->textureMap["CURSOR"]);
    SDL_DestroyTexture(textures->textureMap["OBSTACLES"]);
    SDL_DestroyTexture(textures->textureMap["ENEMIES"]);
    SDL_DestroyTexture(textures->textureMap["PROTECTORS"]);
    SDL_DestroyTexture(textures->textureMap["INSTRUCTIONS"]);

    soundManager->deleteSound("START_MUSIC", SOUND_MUSIC);
    soundManager->deleteSound("PLAY_MUSIC", SOUND_MUSIC);
}

MckinseyGame::~MckinseyGame(){
    delete startState;
    delete playState;
    delete overState;
    delete instrucState;
    delete cursor;

    startState=nullptr;
    playState=nullptr;
    overState=nullptr;
    instrucState=nullptr;
    cursor=nullptr;

    delete textures;
    textures = nullptr;

    delete soundManager;
    soundManager = nullptr;




}
