#include "World.h"

World WorldInit()
{
    World world = {};
    world.Time = 0;
    world.deltaTime = 0;
    for (int x = 0; x < HCellCount; ++x) {
        for (int y = 0; y < VCellCount; ++y)
            world.cells[x + y * HCellCount] = {mkHexPosition(x,y), CellState::Alive};
    }
    return world;
}

void update(const World &system, Cell &cell)
{

}

void update(World &system)
{
    system.deltaTime = elapsedTime() - system.Time;
    system.Time = elapsedTime();
}

void draw(const World &system)
{
    for (auto cell : system.cells) draw(system, cell);
}

void draw(const World &system, const Cell &cell)
{
    Complex position = PositionFromHexPosition(cell.hexPosition);
    circle(position.re * CellSize * 2,position.im * CellSize * 2,CellSize);
}
