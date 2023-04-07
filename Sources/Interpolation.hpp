#ifndef Interpolation_hpp
#define Interpolation_hpp

<<<<<<< Updated upstream
#include "Grapic.h"
#include "Complex.hpp"
#include "Sandbox.hpp"
#include "Color.hpp"

namespace Interpolation {

struct Interpolation {
	float Time,deltaTime;
};

Interpolation init();
void update(Interpolation& system);
void draw(Interpolation& system);
=======
#include "Complex.hpp"

>>>>>>> Stashed changes
float lerp(float a,float b,float t);
int lerp(int a,int b,float t);
void Rect(Complex center,int size);

}

#endif
