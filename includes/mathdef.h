#ifndef MATHDEF_H
#define MATHDEF_H

#include <cmath>

// Returns the minimum of a and b
int min(int a, int b)
{
    return ((a < b) ? a : b);
}

// Returns the maximum of a and b
int max(int a, int b)
{
    return ((a > b) ? a : b);
}

// 2D Position Struct
struct Position
{
    int x; // X Coordinate
    int y; // Y Coordinate
    // Position Struct Constructor
    Position(int x_, int y_) : x(x_), y(y_) {}
    inline float sqlen()
    {
        return ((x * x) + (y * y));
    }

    inline float len()
    {
        return std::sqrt(sqlen());
    }

    inline Position operator+(const Position &b)
    {
        return Position(x + b.x, y + b.y);
    }
    inline Position operator-(const Position &b)
    {
        return Position(x - b.x, y - b.y);
    }
};

#endif // MATHDEF_H
