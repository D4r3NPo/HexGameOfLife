#include "Interpolation.hpp"
using namespace grapic;

namespace Interpolation{

Interpolation init()
{
	return {};
}
void update(Interpolation& interpolation)
{
	//if(elapsedTime() - interpolation.Time < 0.016) return;
	
	interpolation.deltaTime = elapsedTime() - interpolation.Time;
	interpolation.Time = elapsedTime();
}
void draw(Interpolation& interpolation)
{
	//if(elapsedTime() - interpolation.Time < 0.016) return;

	Color colorA = {255,0,0,255};
	Color colorB = {0,0,255,255};
	for (float i = 0; i<1; i+=0.01) {
		float x = lerp(100,400,i);
		Color col = lerp(colorA,colorB,i);
		color(col.r,col.g,col.b,col.a);
		Rect(mkComplex(x,Screen_Size/2 + sin(interpolation.Time + x / 50) * 100),5);
		col = lerp(colorB,colorA,i);
		color(col.r,col.g,col.b,col.a);
		Rect(mkComplex(x,Screen_Size/2 + cos(interpolation.Time + x / 50) * 100),5);
	}
}
void Rect(Complex center,int size)
{
	rectangleFill(center.re - size,center.im -size, center.re + size,center.im +size);
}
float lerp(float a,float b,float t)
{
	return (a * (1-t)) + (b * t);
}
int lerp(int a,int b,float t)
{
	return (a * (1-t)) + (b * t);
}


}
