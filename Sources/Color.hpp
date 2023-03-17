#ifndef Color_hpp
#define Color_hpp

#include "Interpolation.hpp"

struct Color {
	int r,g,b,a;
};
Color lerp(Color a,Color b,float t);

#endif
