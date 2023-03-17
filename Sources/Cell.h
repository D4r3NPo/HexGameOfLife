#ifndef CELL_H
#define CELL_H

#include "Hex.h"

enum CellState { Alive , Dead};

struct Cell{
    HexPosition hexPosition;
    CellState state;
};


#endif //CELL_H
