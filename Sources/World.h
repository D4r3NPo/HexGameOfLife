#ifndef WORLD_H
#define WORLD_H

#include "Main.hpp"
#include "Cell.h"
#include "Grapic.h"
#include "Complex.hpp"

using namespace grapic;

//TODO Express in term of ScreenSize on Init

const int CellSize = 25;
const int VCellCount = (int)Screen_Size/CellSize;
const int HCellCount = (int)Screen_Size/CellSize;
const int CellCount = VCellCount * HCellCount;

struct World {
    float Time,deltaTime;
    Cell cells[VCellCount * HCellCount];
};

World WorldInit();
void update(World& system);
void draw(const World& system);
void DetermineNextState(Cell& cell);
void ApplyNextState(Cell& cell);
void update(const World& system,Cell& cell);
void draw(const World& system,const Cell& cell);
void drawHexagon(HexPosition position);

#endif //WORLD_H
