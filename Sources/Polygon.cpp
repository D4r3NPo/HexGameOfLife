#include "Polygon.hpp"
/*using namespace Polygon;

void operator+=(Polygon& polygon,Complex vertex)
{
	if(polygon.vertexCount < MAX_VERTEX)
	{
		polygon.vertex[polygon.vertexCount] = vertex;
		polygon.vertexCount++;
	}
}
void draw(const Complex& a,const Complex& b)
{
	line(a.re, a.im, b.re, b.im);
}
void draw(const Polygon& polygon)
{
	for (int i =0; i < polygon.vertexCount; i++) {
		draw(polygon[i], polygon[(i+1)%polygon.vertexCount])
	}
}
Polygon lerp(const Polygon& a,const Polygon& b)
{
	if(a.vertexCount != b.vertexCount)
	{
		cout << "Error: Both Polygon need to have same vertex count !" << endl;
		return;
	}
	Polygon lerp;
	lerp.vertexCount = a.vertexCount;
	for (int i = 0; i <a.vertexCount-1; i++) {
		lerp.vertex[i] = Lerp(a.vertex[i],b.vertex[i]);
	}
}
Complex center(const Polygon& polygon)
{
	Complex c = mkComplex(0, 0);
	for (int i = 0; i < polygon.vertexCount-1; i++) {
		c += polygon[i];
	}
	return c * (1.0 / polygon.vertexCount);
}

*/
