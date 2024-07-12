#pragma once
#include <SDL.h>
#include <list>
#include <vector>
#include <iostream>
#include "gameObject.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include "plant.hpp"
#include "Protector.hpp"
#include "zombie.hpp"
#include "eagle.hpp"
#include "snake.hpp"
#include "grid.hpp"
#include "panel.hpp"
#include "definitions.hpp"
#include "soundManager.hpp"
#include "score.hpp"


class PlayState
{
    SDL_Renderer* m_pRenderer;
    
   //These are the textures for the grass, plant,enemies, obstacles, protector, and pause symbol.
    SDL_Texture* grassTexture;
    SDL_Texture* plantTexture;
    SDL_Texture* enemyTexture;
    SDL_Texture* obstacleTexture;
    SDL_Texture* protectorTexture;
    SDL_Texture* pauseTexture;

    SoundManager* soundManager;// this a pointer to SoundManager class object which handles the sound management.

    Plant* plant; // a pointer to the Plant class object.
    GameObject* pause;

    Score* score; // a pointer to the Score class object. This is used to diplay the turns on the screen.
        
    Grid* grid;// a pointer to the Grid class object grid. This grid is used to keep track of the obstacles,
    //protectors, enemies, their damage and their path.
    
    Panel* panel;

    std::vector<Obstacle*> obstacles;//vector to store the obstacles.
    std::vector<Enemy*> enemies;//vector to store the enemies.
    std::vector<Protector*> protectors;//vector to store the protectors.

    int rows, columns; // Total Rows and Columns in the grid.
    int worldRows, worldCols; // Number of playable rows and columns
    int tileWidth, tileHeight; // tileWidth and tileHeight are 
    int m_xIndex = 0, m_yIndex = 0; // Mouse positions.

    // int turns = 0;
    bool turnOccured = false;


    Protector* clickedProtector = nullptr;
    bool isPlaying = false;
    
    int* State;

    public:
        static int turns;
        PlayState(SDL_Renderer* renderer, SoundManager* soundManager, int tileWidth, int tileHeight, int rows, int cols, SDL_Texture* grassTexture, SDL_Texture* planttexture , SDL_Texture* enemyTexture, SDL_Texture* protectorTexture, SDL_Texture* obstacleTexture, SDL_Texture *pauseTexture, int* State);
        ~PlayState();
        void draw();
        void drawGrass();
        void handleEvents(SDL_Event& event);
        void generateObstacle(int row, int col, SDL_Rect srcRect);
        Protector* generateProtectors(PROTECTOR_TYPE type);
        void generateEnemy();
        void initObstacles(int nObstacles);
        bool inWorld_coord(int x, int y);
        bool inWorld_index(int xIndex, int yIndex);
        void play();
        void updateEnemies();
        void updateProtectors();
        bool checkGameOver();
};