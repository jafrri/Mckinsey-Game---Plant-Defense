#include "pathFindWavePropagation.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

bool notContain(int row, int col, vector<Node>& discovered)
{
    for (Node& n: discovered)
    {
        if (row == n.r && col == n.c)
            return false;
    }   

    return true;
}

void getNeighbours(Node node, int rows, int cols, int**& graph, vector<Node>& discovered)
{
    if (node.c > 0)
    {
        if (graph[node.r][node.c-1] == 0 && notContain(node.r, node.c-1, discovered))
        {
            discovered.push_back({node.r, node.c-1, node.dist+1});
        }
    }   
    if (node.c < cols - 1)
    {
        if (graph[node.r][node.c+1] == 0 && notContain(node.r, node.c+1, discovered))
        {
            discovered.push_back({node.r, node.c+1, node.dist+1});
        }
    }   
    if (node.r > 0)
    {
        if (graph[node.r-1][node.c] == 0 && notContain(node.r-1, node.c, discovered))
        {
            discovered.push_back({node.r-1, node.c, node.dist+1});
        }
    }   
    if (node.r < rows - 1)
    {
        if (graph[node.r+1][node.c] == 0 && notContain(node.r+1, node.c, discovered))
        {
            discovered.push_back({node.r+1, node.c, node.dist+1});
        }
    }   
}

int** generateGraph(Entry** grid, int rows, int cols)
{
    int** graph = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        graph[i] = new int[cols]{0};
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j].obstacle)
                graph[i][j] = -1;
        }
    }

    return graph;
}

void deleteGraph(int** graph, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] graph[i];
    }

    delete[] graph;
}

vector<Node> tracePath(Node start, Node end, int** graph, int rows, int cols)
{
    Node cNode = start;

    vector<Node> path = {start};

    bool pathExists;

    while(1)
    {
        pathExists = true;

        if (cNode.c > 0 && graph[cNode.r][cNode.c-1] < cNode.dist && graph[cNode.r][cNode.c-1] > 0)
        {
            cNode = {cNode.r, cNode.c-1, graph[cNode.r][cNode.c-1]};
            path.push_back(cNode);
        }
        else if (cNode.c < cols-1 && graph[cNode.r][cNode.c+1] < cNode.dist && graph[cNode.r][cNode.c+1] > 0)
        {
            cNode = {cNode.r, cNode.c+1, graph[cNode.r][cNode.c+1]};
            path.push_back(cNode);
        }
        else if (cNode.r > 0 && graph[cNode.r-1][cNode.c] < cNode.dist && graph[cNode.r-1][cNode.c] > 0)
        {
            cNode = {cNode.r-1, cNode.c, graph[cNode.r-1][cNode.c]};
            path.push_back(cNode);
        }
        else if (cNode.r < rows-1 && graph[cNode.r+1][cNode.c] < cNode.dist && graph[cNode.r+1][cNode.c] > 0)
        {
            cNode = {cNode.r+1, cNode.c, graph[cNode.r+1][cNode.c]};
            path.push_back(cNode);
        }
        else
            pathExists = false;

        if(cNode.r == end.r && cNode.c == end.c || !pathExists)
            break;
    }

    return path;
}

vector<Node> wavePropagationPathFind(Entry** grid, int rows, int cols, int startRow, int startCol, int plantRow, int plantCol)
{
    // Generate suitable graph (still a grid) from 'Entry** grid' for path finding.
    int** graph = generateGraph(grid, rows, cols);

    Node end = {plantRow, plantCol, 1}; // The distance of the first node is 1.
    vector<Node> toVisit = {end}; // Start the path finding from the destination position.

    while (1)
    { 
        Node currentNode = toVisit[0]; // The node that we are currently visit.

        // Add the distance of the current node to the graph. This distance will then be used to trace the shortest
        // path towrds the plant from the starting node.
        graph[currentNode.r][currentNode.c] = currentNode.dist; 

        // Remove the first node from the toVisit vector, since it is visited.
        toVisit.erase(toVisit.begin());

        // Stop the algorithm after the starting position is found.
        if(currentNode.r == startRow && currentNode.c == startCol)
            break;
    
        // Add the up, down, left, right neighbours to the end of the toVisit vector.
        getNeighbours(currentNode, rows, cols, graph, toVisit);
        
        // Stop the algotrithm if all of the nodes were explored.
        if(toVisit.size() == 0)
            break;
    }

    Node start = {startRow, startCol, graph[startRow][startCol]};

    // Trace path from the graph generated by wave propagation.
    vector<Node> path = tracePath(start, end, graph, rows, cols);

    // Delete the generated graph.
    deleteGraph(graph, rows);

    return path;
}

void print_graph(int** graph, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << setw(3) << graph[i][j] << ' ';
        }
        cout << '\n';
    }
}

void print_graph(char** graph, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << setw(2) << graph[i][j] << ' ';
        }
        cout << '\n';
    }
}

void print_vect(vector<Node> vect)
{
    if (!vect.size())
        cout << "()";
    else
        for (auto i: vect)
        {
            cout <<'(' << i.r << ", " << i.c << ", " << i.dist << ')' << ' ';
        }
    cout << '\n';
}

void print_node(Node node)
{
    cout <<'(' << node.r << ", " << node.c << ", " << node.dist << ')' << '\n';
}
