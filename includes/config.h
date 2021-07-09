#ifndef CONFIG_H
#define CONFIG_H

// Grid Settings
#define NUMBER_ROWS 15
#define NUMBER_COLUMNS 15
#define GRID_ELEMENT_SIZE 60
#define GRID_BORDER_SIZE 4

// PathFinder Settings
#define DIAGONAL_DISABLED 0
#define USE_ACCURATE_DIST 0
#define USE_HEAPS 1

// Color Settings
#define GAMMA_CORRECTION 0
#define EMPTY_COLOR Colorf(1.0f)
#define BORDER_COLOR Colorf(0.15f)
#define BLOCKED_COLOR Colorf(0.0f)
#define ORIGIN_COLOR Colorf(0.0f, 0.0f, 0.8f)
#define TARGET_COLOR Colorf(0.8f, 0.0f, 0.0f)
#define PATH_COLOR Colorf(0.0f, 0.8f, 0.0f)
#define CHECK_COLOR Colorf(0.9f, 0.9f, 0.1f)

#endif // CONFIG_H
