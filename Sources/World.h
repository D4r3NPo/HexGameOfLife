#ifndef WORLD_H
#define WORLD_H

#include "Cell.h"
#include "Grapic.h"
#include "Complex.hpp"

using namespace grapic;

//TODO Express in term of ScreenSize on Init

const int CellSize = 25;
const int VCellCount = 10;
const int HCellCount = 10;
const int CellCount = VCellCount * HCellCount;

struct World {
    float Time,deltaTime;
    Cell cells[VCellCount * HCellCount];
};

World WorldInit();
void update(World& system);
void draw(const World& system);

void update(const World& system,Cell& cell);
void draw(const World& system,const Cell& cell);

#endif //WORLD_H
