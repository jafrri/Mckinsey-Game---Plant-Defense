#pragma once
#include <SDL.h>
#include <vector>
#include "Obstacle.hpp"
// this is the Entry structure which has different bool variables to keep track of the obstacles, protectors,
//enemies and damage.
struct Entry
{
    bool obstacle = false;
    bool protector= false;
    bool enemy= false;
    bool plant = false;
    bool path = false;
    int damage = 0;
};
// this is Grid class which has a double array of the struct Entry.
class Grid
{
    public:
    Entry** grid;

    int nRows, nCols;

    Grid(int nRows, int nCols);
    ~Grid();
    Entry** getGrid(){return grid;};
    void updateGrid(std::vector<Obstacle*>* obstacles);
    void clearPath();
};