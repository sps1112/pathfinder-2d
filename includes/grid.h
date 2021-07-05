#ifndef GRID_H
#define GRID_H

// State of a Grid Element
enum ELEMENT_STATE
{
    EMPTY,
    BLOCKED,
    ORIGIN,
    TARGET,
    PATH,
};

// Returns state from int value
ELEMENT_STATE get_state_from_int(int n)
{
    return static_cast<ELEMENT_STATE>(n);
}

// The Grid Element Struct
struct GridElement
{
    int x;               // X coordinate
    int y;               // Y coordinate
    ELEMENT_STATE state; // State of Grid
    // Default Element Constuctor
    GridElement(int x_ = 0, int y_ = 0, ELEMENT_STATE state_ = EMPTY) : x(x_), y(y_), state(state_) {}
};

// The Grid Struct
struct Grid
{
    int rows;              // Number of rows
    int columns;           // Number of Columns
    GridElement *elements; // Element List
    // Grid Constructor
    Grid(int rows_, int columns_, GridElement *elements_) : rows(rows_), columns(columns_), elements(elements_) {}
    // Returns the element positioned at (x,y)
    GridElement *get_element(int x, int y)
    {
        return &(elements[y * columns + x]);
    }
};

#endif // GRID_H
