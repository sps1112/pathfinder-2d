#ifndef HEAP_H
#define HEAP_h

// Custom Headers
#include <config.h>
#include <mathdef.h>
#include <grid.h>

// Grid Heap Struct
struct Heap
{
    GridNode **list; // List of Grid nodes
    int count;       // Current Count of Nodes
    int maxCount;    // Max capacity of the list
    // Heap Constructor
    Heap(int maxSize = NUMBER_ROWS * NUMBER_COLUMNS)
    {
        maxCount = maxSize;
        list = new GridNode *[maxSize];
        count = 0;
    }

    // Adds Item to the Heap
    void add_to_heap(GridNode *item)
    {
        item->index = count;
        list[count] = item;
        sort_up(item);
        count++;
    }

    // Sorts the Heap upwards from item
    void sort_up(GridNode *item)
    {
        int parentIndex = clamp((item->index - 1) / 2, 0, maxCount - 1);
        while (true)
        {
            GridNode *parent = list[parentIndex];
            if (item->compare_item(parent) > 0)
            {
                swap_items(item, parent);
            }
            else
            {
                break;
            }
            parentIndex = clamp((item->index - 1) / 2, 0, maxCount - 1);
        }
    }

    // Swaps Item a and Item b
    void swap_items(GridNode *a, GridNode *b)
    {
        // Swap values
        list[a->index] = b;
        list[b->index] = a;
        // Swap Item
        a->index = a->index + b->index;
        b->index = a->index - b->index;
        a->index = a->index - b->index;
    }

    // Removes the first item in the Heap
    GridNode *remove_first()
    {
        GridNode *firstItem = list[0];
        count--;
        list[0] = list[count];
        list[0]->index = 0;
        sort_down(list[0]);
        return firstItem;
    }

    // Sorts the list downwards from item
    void sort_down(GridNode *item)
    {
        while (true)
        {
            int childIndex1 = item->index * 2 + 1;
            int childIndex2 = item->index * 2 + 2;
            int newIndex = 0;
            if (childIndex1 < count)
            {
                newIndex = childIndex1;
                if (childIndex2 < count)
                {
                    if (list[childIndex1]->compare_item(list[childIndex2]) < 0)
                    {
                        newIndex = childIndex2;
                    }
                }
                if (item->compare_item(list[newIndex]) < 0)
                {
                    swap_items(list[newIndex], item);
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }

    // Checks if item is at the defined index
    bool has_node(GridNode *item)
    {
        if (count > 0)
        {
            return (list[item->index] == item);
        }
        return false;
    }

    // Updates the said item in the Heap
    void update_item(GridNode *item)
    {
        sort_up(item);
    }
};

#endif // HEAP_H
