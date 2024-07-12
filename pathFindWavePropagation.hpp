#pragma once
#include <vector>
#include "grid.hpp"

struct Node
{
    int r, c, dist;
};

void print_graph(int** graph, int rows, int cols);
void print_graph(char** graph, int rows, int cols);
void print_vect(std::vector<Node> vect);
void print_node(Node node);

std::vector<Node> wavePropagationPathFind(Entry** grid, int rows, int cols, int startRow, int startCol, int plantRow, int plantCol);