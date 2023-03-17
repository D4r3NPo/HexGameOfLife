#include "World.h"

World WorldInit()
{
    std::cout << "HCellCount" << HCellCount << std::endl;
    std::cout << "VCellCount" << VCellCount << std::endl;
    World world = {};
    world.Time = 0;
    world.deltaTime = 0;
    for (int col = 0; col < HCellCount; ++col) {
        for (int row = 0; row < VCellCount; ++row)
            world.cells[col + row * HCellCount] = {mkHexPosition(col, row), CellState::Alive , CellState::Alive};
    }
    return world;
}

void DetermineNextState(Cell& cell)
{

}
void ApplyNextState(Cell& cell)
{
    cell.state = cell.nextState;
    cell.nextState = CellState::None;
}

void update(World &system)
{
    system.deltaTime = elapsedTime() - system.Time;
    system.Time = elapsedTime();
    for (auto cell : system.cells) DetermineNextState(cell);
    for (auto cell : system.cells) ApplyNextState(cell);
}

void draw(const World &system)
{
    for (auto cell : system.cells) draw(system, cell);
}

void draw(const World &system, const Cell &cell)
{
    drawHexagon(cell.hexPosition);
}
void drawHexagon(HexPosition hexPosition)
{
    Complex position = PositionFromHexPosition(hexPosition);
    circle(position.re * CellSize,position.im * CellSize,CellSize);
}
