#ifndef SolarSystem_hpp
#define SolarSystem_hpp

#include "Complex.hpp"
#include "Grapic.h"

namespace SolarSystem {

struct SolarSystem {
	Complex Sun,Earth,Mercury,Moon;
	float Time,deltaTime;
};
struct Color {int r,g,b,a;};

struct PlanetInfo{
	grapic::Image image;
	int size;
};
SolarSystem init();
void update(SolarSystem& system);
void draw(const SolarSystem& system);
void draw(PlanetInfo info,Complex position);

}

#endif
