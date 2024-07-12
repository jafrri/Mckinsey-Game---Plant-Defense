#include "grid.hpp"
#include <iostream>
//the double array of the Entry struct is initialized.
Grid::Grid(int nRows, int nCols)
: nRows(nRows), nCols(nCols)
{
    // Make empty grid.
    grid = new Entry*[nRows];

    for (int i = 0; i < nRows; i++)
    {
        grid[i] = new Entry[nCols];
    }
}
//the grid is updated when this function is called.
void Grid::updateGrid(std::vector<Obstacle*>* obstacles)
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            grid[i][j].damage = 0;
            grid[i][j].enemy = false;
            grid[i][j].obstacle = false;
        }
    }

    for (auto &obs : *obstacles)
    {
        int row = obs->moverRect.y / obs->moverRect.h;
        int col = obs->moverRect.x / obs->moverRect.w;

        grid[row][col].obstacle  = true;
    }
}

//this function clears the path from the grid that is set the path vriable false for every block in the grid.
void Grid::clearPath()
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            grid[i][j].path = false;
        }
    }
}
//the destructor releases the dynamic memory and delete the double array grid.
Grid::~Grid(){
    for (int i = 0; i < nRows; i++)
    {
        delete grid[i];
        grid[i]=nullptr;
    }
    delete[] grid;
    grid=nullptr;

}
