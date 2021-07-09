// Custom Headers
#include <config.h>
#include <grid.h>
#include <draw.h>
#include <stb_image_write.h>
#include <path.h>
#include <chrono>

// Standard Headers
#include <iostream>

// Grid Data
int rows = NUMBER_ROWS;                                                      // Number of Rows in the Grid
int columns = NUMBER_COLUMNS;                                                // Number of Columns in the Grid
int size = GRID_ELEMENT_SIZE;                                                // The Size of Each Elements
int gridState[NUMBER_ROWS * NUMBER_COLUMNS] = {1, 0, 0, 0, 0, 3, 1, 0, 0, 0, // The Grid State
                                               1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
                                               0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
                                               0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
                                               0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
                                               0, 1, 0, 1, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
                                               0, 0, 0, 1, 0, 0, 1, 0, 1, 0,
                                               1, 1, 1, 1, 2, 0, 1, 0, 1, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
//Empty Grid
/*int gridState[NUMBER_ROWS * NUMBER_COLUMNS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // The Grid State
                                               0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0};*/

int main()
{
    // Setup Grid
    std::cout << "Setup Grid Elements" << std::endl;
    GridNode *nodes = new GridNode[rows * columns];
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            nodes[y * columns + x] = GridNode(x, y, get_state_from_int(gridState[y * columns + x]));
        }
    }
    Grid grid(rows, columns, nodes);
    grid.setup_neighbours();

    // Get Image
    std::cout << "Setting up Image" << std::endl;
    int imgRows = rows * size;
    int imgColumns = columns * size;
    Image img = new Colori[imgRows * imgColumns];
    img = get_image_from_grid(&grid);
    stbi_write_png("1.path_to_find.png", imgColumns, imgRows, 4, (void *)img, imgColumns * sizeof(Colori));

    // Process Pathfinding
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Finding path...." << std::endl;
    Path path = find_path(&grid);
    path.set_path();
    auto stop = std::chrono::high_resolution_clock::now();
    printf("Pathfinding time is:- %.5f\n", std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());

    // Show final Result
    std::cout << "Showing Result" << std::endl;
    img = get_image_from_grid(&grid);

    stbi_write_png("2.final_path.png", imgColumns, imgRows, 4, (void *)img, imgColumns * sizeof(Colori));

    // Finish Program
    delete[] nodes;
    std::cout << "Finish!!!" << std::endl;
}