#ifndef CELL_H
#define CELL_H

#include "Hex.h"

enum CellState { None, Alive , Dead};

struct Cell{
    HexPosition hexPosition;
    int col,row;
    int neighbors[6];
    CellState state;
    CellState nextState;
};

#endif //CELL_H
