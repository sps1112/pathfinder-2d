#ifndef DRAW_H
#define DRAW_H

// Custom Headers
#include <grid.h>

// Standard Headers
#include <iostream>
#include <cmath>

// A Color type as (r,g,b) with each from (0.0 to 1,0)
struct Colorf
{
    float r; // Red Channel
    float g; // Green Channel
    float b; // Blue Channel
    Colorf(float a) : r(a), g(a), b(a) {}
    Colorf(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}
};

// Color Data Type for the stb library
using Colori = uint32_t;

// Returns a Colori from (r,g,b) values
Colori get_color(Colorf col)
{
#if GAMMA_CORRECTION
    // Gamma correction
    float gamma = 1 / 2.2f;
    col.r = std::pow(clamp(col.r), gamma);
    col.g = std::pow(clamp(col.g), gamma);
    col.b = std::pow(clamp(col.b), gamma);
#endif
    // Convert a valid Colorf to Colori
    return (255 << 24) | ((int)std::floor(col.b * 255) << 16) | ((int)std::floor(col.g * 255) << 8) | (int)std::floor(col.r * 255);
}

// The Image data type which holds a Colori for each pixel
using Image = Colori *;

// Returns an Image from grid data
Image get_image_from_grid(Grid *grid)
{
    int rows = grid->rows;
    int columns = grid->columns;
    int size = GRID_ELEMENT_SIZE;
    int borderSize = GRID_BORDER_SIZE;
    Image img = new Colori[(rows * size) * (columns * size)];
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            NODE_STATE state = grid->get_node_from_position(x, y)->state;
            Colorf col(0.0f);
            switch (state)
            {
            case EMPTY:
                col = EMPTY_COLOR;
                break;
            case BLOCKED:
                col = BLOCKED_COLOR;
                break;
            case ORIGIN:
                col = ORIGIN_COLOR;
                break;
            case TARGET:
                col = TARGET_COLOR;
                break;
            case PATH:
                col = PATH_COLOR;
                break;
            }
            int startX = x * size;
            int startY = y * size;
            for (int newY = 0; newY < size; newY++)
            {
                for (int newX = 0; newX < size; newX++)
                {
                    int index = (startY + newY) * (columns * size) + (startX + newX);
                    if (newY < borderSize / 2 || newY >= (size - (borderSize / 2)))
                    {
                        img[index] = get_color(BORDER_COLOR);
                    }
                    else if (newX < borderSize / 2 || newX >= (size - (borderSize / 2)))
                    {
                        img[index] = get_color(BORDER_COLOR);
                    }
                    else
                    {
                        img[index] = get_color(col);
                    }
                }
            }
        }
    }
    return img;
}

#endif // DRAW_H
