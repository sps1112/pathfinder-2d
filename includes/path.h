#ifndef PATH_H
#define PATH_H

// Custom Headers
#include <grid.h>
#include <mathdef.h>

// Finds the distance b/w 2 Positions
int distance_element(Position *a, Position *b)
{
    int deltaX = a->x - b->x;
    int deltaY = a->y - b->y;
    int dist = deltaY * deltaY + deltaX * deltaX;
    return ((int)sqrt(dist) * 10);
}

// The GridNode Struct
struct GridNode
{
    GridElement *element;
    GridElement *next;
    int gCost;
    int hCost;
    int fCost;
};

// The Path Struct containing all the nodes
struct Path
{
    int number;      //  Number of Nodes in the Path
    GridNode *grids; // List of Nodes which make up the path
    Path() : number(0), grids(new GridNode[1]) {}
    // Sets the Path Elements on a Grid
    void set_path()
    {
        // Process the Path
        for (int i = 0; i < number; i++)
        {
            GridNode *node = &grids[i];
            node->element->state = PATH;
        }
    }
};

// Returns a Path for the Grid
Path find_path(Grid *grid)
{
    int rows = grid->rows;
    int columns = grid->columns;
    // Calculate Path

    // Setup Path
    Path p;
    /*p.number = 3;
    p.grids = new GridNode[3];
    p.grids[0].element = grid->get_element(3, 0);
    p.grids[1].element = grid->get_element(4, 0);
    p.grids[2].element = grid->get_element(4, 1);*/
    return p;
}

#endif // PATH_
