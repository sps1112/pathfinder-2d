#ifndef GRID_H
#define GRID_H

// Custom Headers
#include <mathdef.h>
#include <vector>
#include <config.h>

// State of a Grid Node
enum NODE_STATE
{
    EMPTY,
    BLOCKED,
    ORIGIN,
    TARGET,
    PATH,
    CHECKED,
    NEIGHBOUR,
};

// Returns state from int value
NODE_STATE get_state_from_int(int n)
{
    return static_cast<NODE_STATE>(n);
}

// The Grid Node Struct
struct GridNode
{
    Position pos;                       // Position of node
    NODE_STATE state;                   // State of Grid Node
    std::vector<GridNode *> neighbours; // List of Neighbour Nodes
    int neighbourCount;                 // Neighbour Count
    GridNode *parent;                   // The node which comes before this node
    int gCost;                          // Distance from start Node
    int hCost;                          // Distance from target Node
    int index;                          // Index in the heap
    // Position Node Constuctor
    GridNode(Position pos_, NODE_STATE state_ = EMPTY) : pos(pos_), state(state_), neighbourCount(0), index(0) {}
    // Node Constuctor
    GridNode(int x_ = 0, int y_ = 0, NODE_STATE state_ = EMPTY) : pos(Position(x_, y_)), state(state_), neighbourCount(0), index(0) {}
    // Checks if Node is Traversable or not
    bool is_traversable()
    {
        return (state != BLOCKED);
    }

    // Returns the sum of gCost and hCost for the node
    int get_fcost()
    {
        return gCost + hCost;
    }

    // Compare Node with Item i.e. (Item - Node)
    int compare_item(GridNode *item)
    {
        int deltaF = (item->get_fcost() - get_fcost());
        return ((deltaF == 0) ? (item->hCost - hCost) : deltaF);
    }
};

// The Grid Struct
struct Grid
{
    int rows;        // Number of rows
    int columns;     // Number of Columns
    GridNode *nodes; // Element List
    // Grid Constructor
    Grid(int rows_, int columns_, GridNode *nodes_) : rows(rows_), columns(columns_), nodes(nodes_) {}
    // Returns the element positioned at (x,y)
    GridNode *get_node_from_position(int x, int y)
    {
        return &(nodes[y * columns + x]);
    }

    // Returns the Starting Node in the Grid
    GridNode *get_start_node()
    {
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < columns; x++)
            {
                if (get_node_from_position(x, y)->state == ORIGIN)
                {
                    return get_node_from_position(x, y);
                }
            }
        }
        return get_node_from_position(0, 0);
    }

    // Returns the Target Node in the Grid
    GridNode *get_target_node()
    {
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < columns; x++)
            {
                if (get_node_from_position(x, y)->state == TARGET)
                {
                    return get_node_from_position(x, y);
                }
            }
        }
        return get_node_from_position(0, 0);
    }

    // Sets up the neighbour nodes for each node
    void setup_neighbours()
    {
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < columns; x++)
            {
                GridNode *node = get_node_from_position(x, y);
                int startX = clamp(x - 1, 0, columns - 1);
                int endX = clamp(x + 1, 0, columns - 1);
                int startY = clamp(y - 1, 0, rows - 1);
                int endY = clamp(y + 1, 0, rows - 1);
                for (int newY = startY; newY <= endY; newY++)
                {
                    for (int newX = startX; newX <= endX; newX++)
                    {

                        if (newX != x || newY != y)
                        {
#if DIAGONAL_DISABLED
                            if (newX == x || newY == y)
                            {
                                node->neighbours.push_back(get_node_from_position(newX, newY));
                                node->neighbourCount++;
                            }
#else
                            node->neighbours.push_back(get_node_from_position(newX, newY));
                            node->neighbourCount++;
#endif
                        }
                    }
                }
            }
        }
    }
};

#endif // GRID_H
