#include "HexGameOfLife.hpp"

using namespace grapic;

namespace HexGameOfLife {

    World init()
    {
        World world = {0,0};
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
        std::cout << system.deltaTime << std::endl;
    }

    void draw(const World &system, const Cell &cell)
    {

    }
}