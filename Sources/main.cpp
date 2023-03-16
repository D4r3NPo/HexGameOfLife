#include "Grapic.h"

using namespace grapic;

const int ScreenSize = 500;

struct World {
  int number;
};

World init() {
  World world;
  world.number = 10;
  return world;
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

  bool stop = false;

  winInit("Program", ScreenSize, ScreenSize);
  winSetPosition(ScreenSize, -1, 0, -1, false);
  backgroundColor(100, 50, 200);

  World world = init();

  do {
    winClear();
    update(world);
    draw(world);
  } while (!winDisplay());

  winQuit();

  return 0;
}
