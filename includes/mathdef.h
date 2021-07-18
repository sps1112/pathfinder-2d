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

// Clamps the value of n from min to max
int clamp(int n, int min, int max)
{
    return ((n > max) ? max : ((n < min) ? min : n));
}

// Clamps the value of n from min to max
float clampf(float n, float min = 0.0f, float max = 1.0f)
{
    return ((n > max) ? max : ((n < min) ? min : n));
}

// Returns the absolute of n
int absolute(int n)
{
    return ((n < 0) ? -n : n);
}

// 2D Position Struct
struct Position
{
    int x; // X Coordinate
    int y; // Y Coordinate
    // Position Struct Constructor
    Position(int x_, int y_) : x(x_), y(y_) {}
};

#endif // MATHDEF_H
