#include "Grapic.h"
#include "Complex.hpp"

using namespace grapic;

const int ScreenSize = 512;

struct World {
  int number;
};

World init() {
  return {10};
}

void update(World &world) {
    world.number = int((1.f + cos(elapsedTime())) * 10.f);
}

void draw(const World &world) {
    for (int i = 0; i < world.number; i++) {
        color(20 * i, 255 - 20 * i, 128);
        rectangle(ScreenSize / 2 - 10 * i, ScreenSize / 2 - 10 * i,
                  ScreenSize / 2 + 10 * i, ScreenSize / 2 + 10 * i);
    }
}

int main(int, char **) {

    Complex A = mkComplex(0,0);
    Complex B = mkComplex(1,2);
    Complex C = A + B;
    std::cout << C.re;

    winInit("Program", ScreenSize, ScreenSize);
    World world = init();
    do {
        winClear();
        update(world);
        draw(world);
    } while (!winDisplay());
    winQuit();
    return 0;
}
