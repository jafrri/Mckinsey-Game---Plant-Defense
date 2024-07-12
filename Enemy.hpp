#pragma once
#include "Animal.hpp"
#include"gameObject.hpp"
#include "pathFindWavePropagation.hpp"
#include "grid.hpp"
#include "score.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include<string>
#include<cstring>

class Enemy: public Animal
{
    std::vector<Node> path;
    Grid* grid;// A pointer to the map grid for interaction with other objects and path finding.

    SDL_RendererFlip flip = SDL_FLIP_NONE; // Determines the direction that the plant-eating enemy should face.
    int rows, cols, plantRow, plantCol;
    int health;// this variable is the health of the enemy and is initialized in the constructor.


    Score* display;//this is a pointer to Score class object which we have used to display text on the screen.


    public:
        Enemy(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect movRect, Grid* grid, int rows, int cols, int plantRow, int plantCol,int health);
        ~Enemy();

        void updatePath();
        void move();
        void draw();
        // void takeDamage(Grid* &grid);
        int gethealth();
        void highlightPath();
        void operator -(Grid*& grid);
        friend std::vector<Node> wavePropagationPathFind(Entry** grid, int rows, int cols, int startRow, int startCol, int plantRow, int plantCol);
};