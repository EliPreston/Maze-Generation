#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"


void draw_cell_sides(Cell* cell, int cell_size) {

    if (cell->timeaddedtomaze > 1) DrawRectangleRec(cell->shape, WHITE);
    else if (cell->timeaddedtomaze == 1) DrawRectangleRec(cell->shape, YELLOW);
    else DrawRectangleRec(cell->shape, RED);
    
    // {1, 1, 1, 1},    // { left, right, bottom, top}
    if (cell->sides[0] == 1) draw_West_Wall(cell, cell_size);
    if (cell->sides[1] == 1) draw_East_Wall(cell, cell_size);
    if (cell->sides[2] == 1) draw_South_Wall(cell, cell_size);
    if (cell->sides[3] == 1) draw_North_Wall(cell, cell_size);

}


void draw_North_Wall(Cell* cell, int cell_size) {
    Vector2 topleft = { (*cell).shape.x, (*cell).shape.y };
    Vector2 top_right = (Vector2) { topleft.x + cell_size, topleft.y };
    DrawLineV(topleft, top_right, BLACK);
}

void draw_West_Wall(Cell* cell, int cell_size) {
    Vector2 topleft = { (*cell).shape.x, (*cell).shape.y };
    Vector2 bottom_left = (Vector2) { topleft.x, topleft.y + cell_size };
    DrawLineV(topleft, bottom_left, BLACK);
}

void draw_South_Wall(Cell* cell, int cell_size) {
    Vector2 topleft = { (*cell).shape.x, (*cell).shape.y };
    Vector2 bottom_left = (Vector2) { topleft.x, topleft.y + cell_size };
    Vector2 bottom_right = (Vector2) { topleft.x + cell_size, topleft.y + cell_size };
    DrawLineV(bottom_left, bottom_right, BLACK);
}

void draw_East_Wall(Cell* cell, int cell_size) {
    Vector2 topleft = { (*cell).shape.x, (*cell).shape.y };
    Vector2 top_right = (Vector2) { topleft.x + cell_size, topleft.y };
    Vector2 bottom_right = (Vector2) { topleft.x + cell_size, topleft.y + cell_size };
    DrawLineV(top_right, bottom_right, BLACK);
}

