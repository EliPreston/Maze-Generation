
// eval cc main.c $(pkg-config --libs --cflags raylib glib-2.0) -o out

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glib.h>     // https://docs.gtk.org/glib/data-structures.html
#include "raylib.h"   // https://www.raylib.com/cheatsheet/cheatsheet.html
#include "cell.h"




Cell** init_grid(int height, int width, int node_distance) {

    // Allocate memory for the grid of pointers
    Cell** grid = (Cell**) malloc(height * sizeof(Cell*));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Allocate memory for each row
    for (int i = 0; i < height; ++i) {
        grid[i] = (Cell*) malloc(width * sizeof(Cell));

        if (grid[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");

            // Free the already allocated memory before returning
            for (int j = 0; j < i; ++j) free(grid[j]);
            free(grid);
            return NULL;
        }
    }
    
    Vector2 topleft = {0, 0};     // (Vector2) { x_pos, y_pos }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            Cell c = {
                (Vector2) { i, j },
                (Rectangle) {topleft.x, topleft.y, node_distance, node_distance},     // Rectangle (float x, float y, float width, float height)
                // NULL,
                0,                          // time(NULL) gives current time
                {1, 1, 1, 1},    // { left, right, bottom, top}
            };

            grid[i][j] = c;
            topleft.x += node_distance;

        }
        topleft.x = 0;
        topleft.y += node_distance;
    }

    return grid;
}


// Function to free the 2D grid
void free_grid(Cell** grid, int height) {
    for (int i = 0; i < height; ++i) free(grid[i]);
    free(grid);
}

void draw_grid(Cell** grid, int cell_size, int height, int width) {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            draw_cell_sides(&(grid[i][j]), cell_size);
        }
    }   
}