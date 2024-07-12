#include "playState.hpp"
#include <iostream>

//The static variables are defined here.
int Zombie::count=-1;
int Zombie::maxZombies=2;

int Eagle::count=-1;
int Eagle::maxEagles=1;

int Snake::count=-1;
int Snake::maxSnakes=2;

int PlayState::turns=0;


PlayState::PlayState(SDL_Renderer *renderer, SoundManager* soundManager, int tileWidth, int tileHeight, int rows, int cols,
                     SDL_Texture *grassTexture, SDL_Texture *plantTexture, SDL_Texture *enemyTexture, SDL_Texture *protectorTexture, SDL_Texture *obstacleTexture, SDL_Texture *pauseTexture, int* State)

    : m_pRenderer(renderer), soundManager(soundManager), tileWidth(tileWidth), tileHeight(tileHeight), rows(rows), columns(cols),
      grassTexture(grassTexture), plantTexture(plantTexture), enemyTexture(enemyTexture), obstacleTexture(obstacleTexture), protectorTexture(protectorTexture), pauseTexture(pauseTexture), State(State)
{
    worldRows = rows - 2;//the playing rows and columns are set
    worldCols = cols - 2;//

    int plantRow = (rand() % 2 + rows / 2 - 1),//the plantrow and plantcol are assigned randomly towards the centre of the grid.
        plantCol = (rand() % 2 + columns / 2 - 1);

    SDL_Rect plantSrcRect = {0, 0, 502, 907},
             plantMovRect = {plantCol * tileWidth, plantRow * tileHeight, tileWidth, tileHeight};

    plant = new Plant(renderer, plantTexture, plantSrcRect, plantMovRect);// plant is initialized.

    pause = new GameObject(m_pRenderer, pauseTexture, SDL_Rect{65,66,376,388});
    pause->moverRect = {(columns/2 - 1) * tileWidth, 0, tileWidth, tileHeight};
    initObstacles(20); // Number of initial obstacles.

    grid = new Grid(rows, cols); //grid object is initialzed with the rows and columns.
    grid->updateGrid(&obstacles); // the grid is updated with the obstacles.
    grid->grid[plantRow][plantCol].plant = true; //the plant position is updated on the grid.

    panel = new Panel(renderer, protectorTexture, tileWidth, tileHeight);
    
    soundManager->playMusic("PLAY_MUSIC", -1);//the music is played for the playstate.

    score = new Score(m_pRenderer);//the score object is initalized which displays the turns.
}

void PlayState::draw()
{
    drawGrass(); // Draw the grass first so that it is underneath everything else.
    if(isPlaying) // Play only when the user decides to
        play();
    else
        pause->draw();

    SDL_Rect movRect={(columns/2 + 3) * tileWidth , 0 , tileWidth * 3, tileHeight};// moverrect for the display of the turns on the screen.
    score->draw(&movRect,turns);
    plant->draw();
    panel->draw();

    for (auto obs : obstacles)
    {
        obs->draw();
    }

    for (Protector *&protector : protectors)
    {
        protector->draw(grid);
    }

    if (clickedProtector != nullptr)
    {
        clickedProtector->draw();
    }

    for (auto enemy : enemies)
    {
        if (inWorld_coord(enemy->moverRect.x, enemy->moverRect.y))
            enemy->draw();
    }

    grid->clearPath(); // Clear the previous path traced by the enemies on the grid.

    // Highlight Rectangle.
    if (inWorld_index(m_xIndex, m_yIndex))
    {
        SDL_SetRenderDrawColor(m_pRenderer, 200, 50, 0, 80);
        SDL_Rect shadeRect = {m_xIndex * tileWidth, m_yIndex * tileHeight, tileWidth, tileHeight};
        SDL_RenderFillRect(m_pRenderer, &shadeRect);
    }
}

void PlayState::play()
{
    int maxEnemies = 3;
    int updateTime = 20; // in deci-second i.e. seconds/10.

    int currTime = SDL_GetTicks();

    // Take a turn only the first time that currTime/20 becomes a multiple of 20.
    turnOccured = ((currTime / 100 % updateTime) && turnOccured) ? false : turnOccured;
    if ((!(currTime / 100 % updateTime) && !turnOccured)) // update after every 2 seconds.
    {
        // std::list<Enemy*>::iterator iter = enemies.begin();
        for (int i = 0; i < enemies.size(); i++)
        {   
            Enemy *enemy = enemies[i];
            
            // enemy->takeDamage(grid);
            *(enemy) - grid;//operator - overloaded to inflict the damage on the enemy. The negative denotes that health is getting subtracted.
            enemy->move();// the enemy move is called to move the enemies on the next turn.

            int rem = enemy->gethealth();
            if (rem <= 0)// this condition checks which enemy's health has become zero or less and deletes it from the enemies vector.
            {
                enemies.erase(enemies.begin() + i);
                delete enemy;
            }
        }

        grid->updateGrid(&obstacles); //this updates the grid at each turn after giving damage to the enemy as above.
        updateEnemies(); //this updates the grid with enemies locations after the enemies has moved.

        
        if(checkGameOver()){//this checks whether the enemy has reached the plant or not. When enemy has reached
        //it sets the state to over and the state is switched and screen is changed to gameoverScreen.
            *State = OVER;
        }

        for(auto &protector : protectors)//updates the combined damage from protectors on the grid.
        {
            protector->attack(grid);
        }

        // Spawn an enemy after every 2 turns untill there are 'maxEnemies' enemies on the screen.
        if (enemies.size() < maxEnemies && !(turns % 2))
            generateEnemy();

        turns += 1;
        turnOccured = true;

        if (!(turns % 10))
            isPlaying = false;
    }
}

void PlayState::drawGrass()
{
    SDL_Rect grassRect = {0, 0, 160, 120};
    SDL_Rect grassRectFog = {160, 0, 160, 120};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            SDL_Rect movRect = {tileWidth * j, tileHeight * i, tileWidth, tileHeight};
            if (i == 0 | i == rows - 1 | j == 0 | j == columns - 1)
                SDL_RenderCopy(m_pRenderer, grassTexture, &grassRectFog, &movRect);
            else
                SDL_RenderCopy(m_pRenderer, grassTexture, &grassRect, &movRect);
        }
    }
}

void PlayState::handleEvents(SDL_Event &event)
{
    if  (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'p')//this controls the pause functionality. When the p key is pressed pause is disabled.
    {
        isPlaying = true;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && !isPlaying)// this keeps track of new protectors being generated from the side panel and is 
    //functional only when the pause is enabled.
    {
        // if mouse is hovering over the panel.
        if (m_yIndex == panel->zRow && m_xIndex == panel->zCol && (Zombie::count<Zombie::maxZombies))
            clickedProtector = generateProtectors(ZOMBIE);
        else if (m_yIndex == panel->eRow && m_xIndex == panel->eCol && (Eagle::count<Eagle::maxEagles))
            clickedProtector = generateProtectors(EAGLE);
        else if (m_yIndex == panel->sRow && m_xIndex == panel->sCol && (Snake::count<Snake::maxSnakes))
            clickedProtector = generateProtectors(SNAKE);
        else
        {
            for (int i = 0; i < protectors.size(); i++)
            {
                Protector* protector = protectors[i];
                int pRow = protector->moverRect.y / protector->moverRect.h,
                    pCol = protector->moverRect.x / protector->moverRect.w;

                if (pRow == m_yIndex && pCol == m_xIndex)
                {
                    clickedProtector = protector;
                    protectors.erase(protectors.begin() + i);
                    grid->grid[pRow][pCol].protector = false;
                }
            }  
        }
    }

    if (event.type == SDL_MOUSEMOTION)
    {
        // update mouse positions.
        m_xIndex = event.motion.x / tileWidth;
        m_yIndex = event.motion.y / tileHeight;
    }

    if ((event.motion.state == SDL_PRESSED | event.button.state == SDL_PRESSED) && clickedProtector != nullptr)
    {
        clickedProtector->moverRect.x = m_xIndex * tileWidth;
        clickedProtector->moverRect.y = m_yIndex * tileHeight;
    }
    else if (clickedProtector != nullptr)
    {
        int plantRow = plant->moverRect.y / plant->moverRect.h;
        int plantCol = plant->moverRect.x / plant->moverRect.w;

        if (!(m_yIndex < 1 | m_yIndex > worldRows | m_xIndex < 1 | m_xIndex > worldCols | grid->grid[m_yIndex][m_xIndex].protector | grid->grid[m_yIndex][m_xIndex].obstacle | (plantRow == m_yIndex && plantCol == m_xIndex)))
        {
            clickedProtector->row = m_yIndex;
            clickedProtector->col = m_xIndex;

            protectors.push_back(clickedProtector);
            clickedProtector = nullptr;
            grid->grid[m_yIndex][m_xIndex].protector = true;

        }
        else
        {
            // Check if protector position is valid, if so, then add it to protectors vector.
            if (clickedProtector->row && clickedProtector->col)
            {
                clickedProtector->moverRect.y = clickedProtector->row * tileHeight;
                clickedProtector->moverRect.x = clickedProtector->col * tileWidth;
                protectors.push_back(clickedProtector);
                grid->grid[clickedProtector->row][clickedProtector->col].protector = true;
            }
            else
            {
                std::cout << "Deleted Protector\n";
                delete clickedProtector;
            }
            clickedProtector = nullptr;
        }
    }
}

void PlayState::generateObstacle(int row, int col, SDL_Rect srcRect)// generates the obstacles on the row and col position taken as arguments
{
    if (col == (plant->moverRect.x / plant->moverRect.w) && row == (plant->moverRect.y / plant->moverRect.h))// if the position is that of plant osbtacle is not generated.
        return;
    else
    {
        for (auto obs : obstacles)//this loop checks whether the positon is not that of already existing obstacle, it this is the case the obstacle is not generated.
        {
            int obsR = obs->moverRect.y / obs->moverRect.h;
            int obsC = obs->moverRect.x / obs->moverRect.w;

            if (obsR == row && obsC == col)
                return;
        }
        //if the position is not on any plant and not of any existing obstacle, then the obstacle is generated.
        SDL_Rect mRect = {col * tileWidth, row * tileHeight, tileWidth, tileHeight};
        Obstacle *obstacle = new Obstacle(m_pRenderer, obstacleTexture, srcRect, mRect);
        obstacles.push_back(obstacle);
    }
}

void PlayState::generateEnemy()//this function generates the enemy 
{
    SDL_Rect enemySrcArray[6] =
        {
            SDL_Rect{0, 0, 350, 350},
            SDL_Rect{0, 350, 350, 350},
            SDL_Rect{0, 700, 350, 350},
            SDL_Rect{350, 0, 346, 346},
            SDL_Rect{350, 350, 346, 346},
            SDL_Rect{350, 700, 350, 350}};

    // Generate the enemy on one of the four edges of the game's grid.
    int animalPos[2] = {rand() % worldRows + 1, rand() % worldCols + 1};
    int changeIndex = rand() % 2;
    int changeValue[2][2] = {{0, 0}, {worldRows + 1, worldCols + 1}};
    animalPos[changeIndex] = changeValue[rand() % 2][changeIndex];

    SDL_Rect sRect = enemySrcArray[rand() % 6];

    SDL_Rect mRect = {animalPos[1] * tileWidth, animalPos[0] * tileHeight, tileWidth, tileHeight};

    Enemy *enemy = new Enemy(m_pRenderer, enemyTexture, sRect, mRect, grid, rows, columns, plant->moverRect.y / tileHeight, plant->moverRect.x / tileWidth, (rand()%3*2+6)*10); // health either 60, 80, or 100
    enemies.push_back(enemy);
    int row = animalPos[0];
    int col = animalPos[1];
    grid->grid[row][col].enemy = true;
}

Protector* PlayState::generateProtectors(PROTECTOR_TYPE type)//this function generates the protector.
{
    std::cout << "Generating Protector\n";
    SDL_Rect movRect = {tileWidth * m_xIndex, tileHeight * m_yIndex, tileWidth, tileHeight};
    Protector *object;

    switch(type)//this depending on the case it generates correspondong protector
    {
        case ZOMBIE:
            object = new Zombie(m_pRenderer, protectorTexture, movRect);
        break;
        case EAGLE:
            object = new Eagle(m_pRenderer, protectorTexture, movRect);
        break;
        case SNAKE:
            object = new Snake(m_pRenderer, protectorTexture, movRect);
        break;
    }

    return object;
}

void PlayState::initObstacles(int nObstacles)
{
    SDL_Rect obsSrcArray[5] =
        {
            SDL_Rect{350, 0, 346, 346},
            SDL_Rect{0, 350, 350, 350},
            SDL_Rect{349, 352, 346, 346},
            SDL_Rect{700, 0, 350, 350},
            SDL_Rect{700, 350, 350, 350}
        };
    while (obstacles.size() < nObstacles)
    {
        SDL_Rect sRect = obsSrcArray[rand() % 5];
        generateObstacle(rand() % worldRows + 1, rand() % worldCols + 1, sRect);
    }
}

// Check whether an object is in the playable area or not.
bool PlayState::inWorld_coord(int x, int y)
{
    bool inWorld = false;
    int colX = x / tileWidth, rowY = y / tileHeight;
    if (colX > 0 && colX < worldCols + 1 && rowY > 0 && rowY < worldRows + 1)
        inWorld = true;
    return inWorld;
}

bool PlayState::inWorld_index(int xIndex, int yIndex)
{
    bool inWorld = false;
    if (xIndex > 0 && xIndex < worldCols + 1 && yIndex > 0 && yIndex < worldRows + 1)
        inWorld = true;
    return inWorld;
}

void PlayState::updateEnemies()//this function iterates over the enemies vector and updates their location on the grid.
{
    for (Enemy *&enemy: enemies)
    {
        int r = enemy->moverRect.y / enemy->moverRect.h;
        int c = enemy->moverRect.x / enemy->moverRect.w;
        
        grid->grid[r][c].enemy = true;
    }
}

void PlayState::updateProtectors()//this function iterates over the protectos vector and updates their location on the grid.
{
    for (Protector *&protector: protectors)
    {
        int r = protector->moverRect.y / protector->moverRect.h;
        int c = protector->moverRect.x / protector->moverRect.w;
        
        grid->grid[r][c].protector = true;
    }
}

bool PlayState::checkGameOver()//this function checks whether any enemy has reahced the plant or not and returns true when it has.
{
    int r = plant->moverRect.y / plant->moverRect.h;
    int c = plant->moverRect.x / plant->moverRect.w;

    if(grid->grid[r][c].enemy==true){
        return(true);
    }
}

PlayState::~PlayState()
{
    Mix_PauseMusic();
    Mix_HaltMusic();
    
    //all the pointers are set to null;
    m_pRenderer = nullptr;
    grassTexture = nullptr;
    plantTexture = nullptr;
    enemyTexture = nullptr;
    obstacleTexture = nullptr;
    protectorTexture = nullptr;

    // the dynamic memory is released.
    delete plant;
    delete grid;
    delete panel;
    delete pause;
    delete score;

    //pointers are set to null.
    plant = nullptr;
    grid = nullptr;
    panel = nullptr;
    pause = nullptr;
    score = nullptr;
    // dynamically created objects are deleted and their pointers set to null.
    for (int i = 0; i < enemies.size(); i++)
    {
        delete enemies.back();
        enemies.back() = nullptr;
        enemies.pop_back();
    }

    for (int i = 0; i < protectors.size(); i++)
    {
        delete protectors.back();
        protectors.back() = nullptr;
        protectors.pop_back();
    }
    for (int i = 0; i < obstacles.size(); i++)
    {
        delete obstacles.back();
        obstacles.back() = nullptr;
        obstacles.pop_back();
    }

    Zombie::set_count(-1);
    Eagle::set_count(-1);
    Snake::set_count(-1);
}

