#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "util.c"
// #include "grid.c"
// #include "cell.h"


uint MAZE_SIZE;
uint FRONTIER_SIZE;


void remove_wall(Cell** grid, int height, int width, int row, int col);

void prims_algorithm(Cell** grid, int height, int width) {
    MAZE_SIZE = 0;
    // height = num_rows
    // width = num_cols

    GSList* frontier = NULL;

    int cell_x = genRandNum(0, height-1);
    int cell_y = genRandNum(0, width-1);    
    printf("Start Cell: %d, %d\n", cell_x, cell_y);
    mark_cell(grid, height, width, (&grid[cell_x][cell_y]), &frontier);


    int frontier_index;
    Vector2* frontier_cell;  // pointer to frontier cell chosen at random

    while (MAZE_SIZE < height*width) {
    // while (MAZE_SIZE < 10) {

        if (FRONTIER_SIZE < 2) frontier_index = 0;
        else frontier_index = genRandNum(0, FRONTIER_SIZE);
        frontier_cell = (Vector2*) g_slist_nth_data(frontier, frontier_index);
        cell_x = (int) (*frontier_cell).x;
        cell_y = (int) (*frontier_cell).y;
        // printf("Chosen frontier cell located at: %d, %d\n", cell_x, cell_y);


        mark_cell(grid, height, width, (&grid[cell_x][cell_y]), &frontier);
        remove_wall(grid, height, width, cell_x, cell_y);


        frontier = g_slist_remove(frontier,  frontier_cell);
        FRONTIER_SIZE--;
    }

    int real_count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j].timeaddedtomaze > 1) {
                real_count++;
                // printf("%d\n", grid[i][j].timeaddedtomaze);
            }
        }
    }

    printf("Expected: %d -- Actual: %d\n", height*width, real_count);
    printf("DONE\n");
    g_slist_free(frontier);
}


void mark_cell(Cell** grid, int height, int width, Cell* cell, GSList** frontier) {     //maybe change this so you pass a grid position rather than a cell???

    (*cell).timeaddedtomaze = time(NULL) + MAZE_SIZE;
    MAZE_SIZE += 1;

    int xpos = (*cell).gridposition.x;
    int ypos = (*cell).gridposition.y;

    frontier_add(grid, height, width, xpos-1, ypos, frontier);
    frontier_add(grid, height, width, xpos+1, ypos, frontier);
    frontier_add(grid, height, width, xpos, ypos-1, frontier);
    frontier_add(grid, height, width, xpos, ypos+1, frontier);
}


void frontier_add(Cell** grid, int height, int width, int row, int col, GSList** frontier) {
    if (row >= 0 && col >= 0 && row < height && col < width && (&grid[row][col])->timeaddedtomaze == 0) {
        (&grid[row][col])->timeaddedtomaze = 1;
        *frontier = g_slist_append(*frontier, &(&grid[row][col])->gridposition);
        FRONTIER_SIZE += 1;
    }
}

void remove_wall(Cell** grid, int height, int width, int row, int col) {

    //  {1, 1, 1, 1},    // { left, right, bottom, top}    
    if (col-1 >= 0 && col-1 < width && grid[row][col-1].timeaddedtomaze > 1) {
        (&grid[row][col])->sides[0] = 0; //remove left wall of current cell
        (&grid[row][col-1])->sides[1] = 0; //remove right wall of current cell
        return;
    }
    
    if (row+1 >= 0 && row+1 < height && grid[row+1][col].timeaddedtomaze > 1) {
        (&grid[row][col])->sides[2] = 0; //remove bottom wall of current cell
        (&grid[row+1][col])->sides[3] = 0; //remove top wall of current cell
        return;
    }
    if (col+1 >= 0 && col+1 < width && grid[row][col+1].timeaddedtomaze > 1) {
        (&grid[row][col])->sides[1] = 0; //remove right wall of current cell
        (&grid[row][col+1])->sides[0] = 0; //remove left wall of current cell

        return;
    }
    if (row-1 >= 0 && row-1 < height && grid[row-1][col].timeaddedtomaze > 1) {
        (&grid[row][col])->sides[3] = 0; //remove top wall of current cell
        (&grid[row-1][col])->sides[2] = 0; //remove bottom wall of current cell
        return;
    }
}





// void remove_wall(Cell** grid, int height, int width, int row, int col) {

//     //  {1, 1, 1, 1},    // { left, right, bottom, top}


//     printf("Checking cells around grid position: %d, %d\n", row, col);
//     //  {1, 1, 1, 1},    // { left, right, bottom, top}
    
//     if (col-1 >= 0 && col-1 < width && grid[row][col-1].timeaddedtomaze > 1) {
//         printf("Cell already in maze found to the left: %d, %d\n", row, col-1);
//         (&grid[row][col])->sides[0] = 0; //remove left wall of current cell
//         (&grid[row][col-1])->sides[1] = 0; //remove right wall of current cell

//         printf("Frontier cell chosen sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row][col].sides[i]);
//         printf("\n");

//         printf("Cell already in maze sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row][col-1].sides[i]);
//         printf("\n");
//         return;
//     }
    
//     if (row+1 >= 0 && row+1 < height && grid[row+1][col].timeaddedtomaze > 1) {
//         printf("Cell already in maze found below: %d, %d\n", row+1, col);
//         (&grid[row][col])->sides[2] = 0; //remove bottom wall of current cell
//         (&grid[row+1][col])->sides[3] = 0; //remove top wall of current cell

//         printf("Frontier cell chosen sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row][col].sides[i]);
//         printf("\n");

//         printf("Cell already in maze sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row+1][col].sides[i]);
//         printf("\n");
//         return;
//     }
//     if (col+1 >= 0 && col+1 < width && grid[row][col+1].timeaddedtomaze > 1) {
//         printf("Cell already in maze found to the right: %d, %d\n", row, col+1);
//         (&grid[row][col])->sides[1] = 0; //remove right wall of current cell
//         (&grid[row][col+1])->sides[0] = 0; //remove left wall of current cell

//         printf("Frontier cell chosen sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row][col].sides[i]);
//         printf("\n");

//         printf("Cell already in maze sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row][col+1].sides[i]);
//         printf("\n");
//         return;
//     }
//     if (row-1 >= 0 && row-1 < height && grid[row-1][col].timeaddedtomaze > 1) {
//         printf("Cell already in maze found above: %d, %d\n", row-1, col);
//         (&grid[row][col])->sides[3] = 0; //remove top wall of current cell
//         (&grid[row-1][col])->sides[2] = 0; //remove bottom wall of current cell

//         printf("Frontier cell chosen sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row][col].sides[i]);
//         printf("\n");

//         printf("Cell already in maze sides after wall removal: ");
//         for (int i = 0; i < 4; i++) printf("%d ", grid[row-1][col].sides[i]);
//         printf("\n");
//         return;
//     }
// }