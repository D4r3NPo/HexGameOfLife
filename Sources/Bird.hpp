#ifndef Bird_hpp
#define Bird_hpp


#include "Grapic.h"
#include "Complex.hpp"
#include "Sandbox.hpp"

namespace Bird {

struct Bird {
	grapic::Image birdImg,wingL,wingR;
	Complex position;
	float wingsAngle;
	float Time,deltaTime;
	bool toggle;
};

Bird init();
void update(Bird& system);
void draw(Bird& system);
}

#endif

