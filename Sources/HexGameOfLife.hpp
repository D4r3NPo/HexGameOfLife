#ifndef HexGameOfLife_H
#define HexGameOfLife_H

#include "Grapic.h"

namespace HexGameOfLife {

    //TODO Express in term of ScreenSize on Init
    const int VCellCount = 10;
    const int HCellCount = 10;

    struct Cell{
    };

    struct World {
        float Time,deltaTime;

    };

    World init();
    void update(const World& system,Cell& cell);
    void update(World& system);
    void draw(const World& system);
    void draw(const World& system,const Cell& cell);

}
#endif //HexGameOfLife_H
