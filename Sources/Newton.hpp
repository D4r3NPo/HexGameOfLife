#ifndef Newton_hpp
#define Newton_hpp

#include "Complex.hpp"
#include "Grapic.h"
#include "Color.hpp"
#include <random>
#include <time.h>

namespace Newton {

struct Particule{
	int index;
	Complex position;
	Complex velocity;
	Color color;
};
struct System {
	const static int particulesCount = 10;
	const static int particulesSize = 10;
	Particule particules[particulesCount];
	Complex Gravity;
	float Time,deltaTime;
};

System init();
void update(const System& system,Particule& particule);
void update(System& system);
void draw(const System& system);
void draw(const System& system,const Particule& particule);

}

#endif
