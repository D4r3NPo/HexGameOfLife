#include "Interpolation.hpp"

float lerp(float a,float b,float t)
{
	return (a * (1-t)) + (b * t);
}

int lerp(int a,int b,float t)
{
	return (a * (1-t)) + (b * t);
}