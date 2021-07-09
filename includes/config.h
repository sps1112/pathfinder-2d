#ifndef CONFIG_H
#define CONFIG_H

// Grid Settings
#define NUMBER_ROWS 10
#define NUMBER_COLUMNS 10
#define GRID_ELEMENT_SIZE 80
#define GRID_BORDER_SIZE 10

// PathFinder Settings
#define DIAGONAL_DISABLED 0

// Color Settings
#define GAMMA_CORRECTION 0
#define EMPTY_COLOR Colorf(1.0f)
#define BORDER_COLOR Colorf(0.1f)
#define BLOCKED_COLOR Colorf(0.0f)
#define ORIGIN_COLOR Colorf(0.0f, 0.0f, 1.0f)
#define TARGET_COLOR Colorf(1.0f, 0.0f, 0.0f)
#define PATH_COLOR Colorf(0.0f, 1.0f, 0.0f)
#define CHECK_COLOR Colorf(1.0f, 1.0f, 0.0f)

#endif // CONFIG_H
