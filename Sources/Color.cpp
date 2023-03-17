#include "Color.hpp"

Color lerp(Color a,Color b,float t)
{
	return {
		lerp(a.r,b.r,t),
		lerp(a.g,b.g,t),
		lerp(a.b,b.b,t),
		lerp(a.a,b.a,t)
	};
}
