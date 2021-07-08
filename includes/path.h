#ifndef PATH_H
#define PATH_H

// Custom Headers
#include <grid.h>
#include <mathdef.h>

// Standard Headers
#include <vector>
#include <limits>

// Finds the distance b/w 2 Positions
int get_distance_bw_nodes(GridNode *a, GridNode *b)
{
    int deltaX = a->pos.x - b->pos.x;
    int deltaY = a->pos.y - b->pos.y;
    int dist = deltaY * deltaY + deltaX * deltaX;
    return (int)(sqrt(dist) * 10);
}

struct NodeList
{
    GridNode **list; // List of Nodes
    int count;       // Number of elements in list
    // Default Constructor for Node List
    NodeList() : count(0) {}

    void print_node_list()
    {
        std::cout << "Printing List..." << std::endl;
        for (int i = 0; i < count; i++)
        {
            std::cout << "Node is:"
                      << "(" << list[i]->pos.x << "," << list[i]->pos.y << ")" << std::endl;
        }
    }

    // Add a new Node to the List
    void add_node(GridNode *node)
    {
        GridNode **tempList;
        if (count > 0)
        {
            tempList = new GridNode *[count];
            for (int i = 0; i < count; i++)
            {
                tempList[i] = list[i];
            }
        }
        count++;
        list = new GridNode *[count];
        for (int i = 0; i < count - 1; i++)
        {
            list[i] = tempList[i];
        }
        list[count - 1] = node;
    }

    // Checks if the node is present in list
    bool has_node(GridNode *node)
    {
        for (int i = 0; i < count; i++)
        {
            if (list[i] == node)
            {
                return true;
            }
        }
        return false;
    }

    // Gets the index of node in list
    int get_node_index(GridNode *node)
    {
        if (has_node(node))
        {
            for (int i = 0; i < count; i++)
            {
                if (list[i] == node)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    // Removes the Node from the list
    void remove_node(GridNode *node)
    {
        int index = get_node_index(node);
        if (count > 1)
        {
            if (index >= 0)
            {
                GridNode **tempList;
                tempList = new GridNode *[count - 1];
                int listIndex = 0;
                for (int i = 0; i < count; i++)
                {
                    if (i != index)
                    {
                        tempList[listIndex] = list[i];
                        listIndex++;
                    }
                }
                count--;
                list = new GridNode *[count];
                for (int i = 0; i < count; i++)
                {
                    list[i] = tempList[i];
                }
            }
        }
        else
        {
            count--;
        }
    }

    void set_list_costs(GridNode *start, GridNode *target)
    {
        for (int i = 0; i < count; i++)
        {
            GridNode *node = list[i];
            node->gCost = get_distance_bw_nodes(start, node);
            node->hCost = get_distance_bw_nodes(target, node);
            node->fCost = node->gCost + node->hCost;
        }
    }

    GridNode *get_current_node()
    {
        int minIndex = 0;
        int minFCost = std::numeric_limits<int>::max();
        int minHCost = std::numeric_limits<int>::max();
        for (int i = 0; i < count; i++)
        {
            if (list[i]->fCost < minFCost)
            {
                minFCost = list[i]->fCost;
                minHCost = list[i]->hCost;
                minIndex = i;
            }
            else if (list[i]->fCost == minFCost)
            {
                if (list[i]->hCost <= minHCost)
                {
                    minFCost = list[i]->fCost;
                    minHCost = list[i]->hCost;
                    minIndex = i;
                }
            }
        }
        return list[minIndex];
    }
};

int get_fcost(GridNode *node, GridNode *start, GridNode *target)
{
    int gCost = get_distance_bw_nodes(start, node);
    int hCost = get_distance_bw_nodes(target, node);
    return gCost + hCost;
}

void set_cost(GridNode *node, GridNode *start, GridNode *target)
{
    node->gCost = get_distance_bw_nodes(start, node);
    node->hCost = get_distance_bw_nodes(target, node);
    node->fCost = node->gCost + node->hCost;
}

// The Path Struct containing all the nodes
struct Path
{
    int number;     //  Number of Nodes in the Path
    NodeList grids; // List of Nodes which make up the path
    Path() : number(0) {}
    // Sets the Path Elements on a Grid
    void set_path()
    {
        // Process the Path
        for (int i = 0; i < number; i++)
        {
            grids.list[i]->state = PATH;
        }
    }
};

// Returns a Path for the Grid
Path find_path(Grid *grid)
{
    int rows = grid->rows;
    int columns = grid->columns;
    std::cout << "Map is " << rows << " X " << columns << std::endl;
    // Calculate Path
    NodeList openList;
    NodeList closedList;
    GridNode *targetNode = grid->get_target_node();
    GridNode *startNode = grid->get_start_node();
    std::cout << "Start from:"
              << "(" << startNode->pos.x << "," << startNode->pos.y << ")" << std::endl;
    std::cout << "Target is:"
              << "(" << targetNode->pos.x << "," << targetNode->pos.y << ")" << std::endl;
    openList.add_node(startNode);
    openList.set_list_costs(startNode, targetNode);
    int n = 0;
    while (true)
    {
        std::cout << "Iteration: " << n << std::endl;
        n++;
        GridNode *currentNode = openList.get_current_node();
        std::cout << "Current Node:"
                  << "(" << currentNode->pos.x << "," << currentNode->pos.y << ")" << std::endl;
        openList.remove_node(currentNode);
        closedList.add_node(currentNode);
        std::cout << "Check for target..." << std::endl;
        if (currentNode == targetNode)
        {
            break;
        }
        std::cout << "Check for neighbours..." << std::endl;
        for (int i = 0; i < currentNode->neighbourCount; i++)
        {
            GridNode *neighbour = currentNode->neighbours[i];
            if (neighbour->is_traversable() && !closedList.has_node(neighbour))
            {
                int moveCost = currentNode->gCost + get_distance_bw_nodes(currentNode, neighbour);
                if (!openList.has_node(neighbour) || moveCost < neighbour->gCost)
                {
                    neighbour->gCost = moveCost;
                    neighbour->hCost = get_distance_bw_nodes(targetNode, neighbour);
                    neighbour->fCost = neighbour->gCost + neighbour->hCost;
                    neighbour->parent = currentNode;
                    if (!openList.has_node(neighbour))
                    {
                        openList.add_node(neighbour);
                    }
                    else
                    {
                        set_cost(neighbour, startNode, targetNode);
                    }
                }
            }
        }
    }
    std::cout << "Path Found!!!" << std::endl;

    // Setup Path
    Path p;
    GridNode *node = targetNode->parent;
    while (node != startNode)
    {
        std::cout << "Current Node:"
                  << "(" << node->pos.x << "," << node->pos.y << ")" << std::endl;
        p.grids.add_node(node);
        node = node->parent;
        p.number++;
    }
    return p;
}

#endif // PATH_
