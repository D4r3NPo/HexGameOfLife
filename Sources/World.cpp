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
            world.cells[col + row * HCellCount] = mkCell(col,row);
    }
    return world;
}

void DetermineNextState(World& world,Cell& cell)
{
    int aliveNeighbors = 0;
    for(int & neighbor : cell.neighbors)
    {
        if(neighbor != -1 && world.cells[neighbor].state == CellState::Alive) aliveNeighbors++;
    }

    // Test Rules
    if(cell.state == CellState::Alive) cell.state = CellState::Dead;
    else if(cell.state == CellState::Dead) cell.state = CellState::Alive;

    // True Rules
    //if(aliveNeighbors > 3) cell.nextState = CellState::Dead;
    //if(aliveNeighbors == 2 && cell.state == CellState::Dead) cell.nextState = CellState::Alive;
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
    for (auto cell : system.cells) DetermineNextState(system,cell);
    for (auto cell : system.cells) ApplyNextState(cell);
}

void draw(const World &system)
{
    for (auto cell : system.cells) draw(system, cell);
}

void draw(const World &system, const Cell &cell)
{
    Complex position = PositionFromHexPosition(cell.hexPosition);
    circle(position.re * CellSize,position.im * CellSize,CellSize);
    //polygonFill(GetHexVertex(hexPosition, CellSize).Vertex, 6);
}

