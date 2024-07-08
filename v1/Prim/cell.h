#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"


// typedef struct {
//     Vector2* coordinates;
//     size_t size;
// } CellNeighbours;

typedef struct {
    Vector2 gridposition;  // gridposition.x is the row number, gridposition.y is the column number
    Rectangle shape; // Rectangle (float x, float y, float width, float height)
    uint timeaddedtomaze;
    int sides[4];
    // CellNeighbours* neighbours;
} Cell;

// CellNeighbours getneighbours(int x, int y, int** grid, int gridHeight, int gridWidth);
void draw_cell_sides(Cell *cell, int cell_size);

void draw_North_Wall(Cell *cell, int cell_size);
void draw_East_Wall(Cell *cell, int cell_size);
void draw_South_Wall(Cell *cell, int cell_size);
void draw_West_Wall(Cell *cell, int cell_size);
void mark_cell(Cell** grid, int height, int width, Cell* cell, GSList** frontier);
void frontier_add(Cell** grid, int height, int width, int row, int col, GSList** frontier);
