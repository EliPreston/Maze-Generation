// eval cc main.c $(pkg-config --libs --cflags raylib glib-2.0) -o 1.0.0-prim.out 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"


// ORDER MATTERS IM NOT SURE WHY --> LOOK UP HOW INCLUDE STATEMENTS WORK TO GET A BETTER UNDERSTANDING PAST SURFACE LEVEL
#include "grid.c"
#include "prim.c"
#include "cell.c"


// https://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm

// Program Entry
int main(int argc, char *argv[]) {

    // Window size
    const int pxheight = 800;
    const int pxwidth = 1200;

    // Set up grid
    int cellsize = 20;
    int height = (pxheight / cellsize);
    int width = (pxwidth / cellsize);
    Cell** cells = NULL;
    cells = init_grid(height, width, cellsize);

    InitWindow(pxwidth, pxheight, "Maze Generation - Prim's Algorithm");
    SetTargetFPS(60);
   

    // prims_algorithm(cells, height, width);
    // Controls
    int show_controls = 1;


    // Main loop
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) {
            free_grid(cells, height);
            cells = init_grid(height, width, cellsize);
            prims_algorithm(cells, height, width);
        }

        if (IsKeyPressed(KEY_C)) {
            
        }


        // Drawing objects/entities
        BeginDrawing();

            // Draw background + draw grid
            ClearBackground(RAYWHITE);
           
            draw_grid(cells, cellsize, height, width);
            DrawFPS(20, 20);
            DrawRectangle(20, 40, 75, 200, BLUE);


        EndDrawing();
    }

    CloseWindow();
    free_grid(cells, height);
    return 0;
}





    // Vector2 mouseposition;

        // mouseposition = GetMousePosition();

            // DrawCircleV(mouseposition, 20, BLACK);
