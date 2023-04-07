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

Cell mkCell(int col,int row)
{
    Cell cell{};
    cell.col = col;
    cell.row = row;
    cell.state = CellState::None;
    cell.nextState = CellState::None;
    for (int &neighbor: cell.neighbors) neighbor = -1;
    return cell;
}

#endif //CELL_H
