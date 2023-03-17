#include "Newton.hpp"
using namespace grapic;
namespace Newton{

float Remap(float value,float inMin,float inMax,float outMin,float outMax)
{
	return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}
Complex RandomComplex(float min, float max)
{
	int range = abs(max - min);
	return{Remap((float)(rand()%range), 0, range, min, max), Remap((float)(rand()%range), 0, range, min, max)};
}


System init()
{
	srand(time(NULL));
	
	System system;
	system.Time = 0;
	system.deltaTime = 0;
	system.Gravity = {0 ,-98.1 * 2};
	for (int i = 0; i < system.particulesCount; i++) {
		system.particules[i].color = {255,0,0,255};
		system.particules[i].position = mkComplex(Screen_Size/2 + i,Screen_Size/2);
		system.particules[i].velocity = RandomComplex(-100, 100);
		system.particules[i].index = i;
	}
	return system;
}




void update(System& system, Particule& p)
{
	p.velocity = p.velocity + system.Gravity * system.deltaTime;
	p.position = p.position + p.velocity * system.deltaTime;
	
	for (int i = 0; i < system.particulesCount; i++) {
		if(p.index == system.particules[i].index) continue;
		float distance =
		sqrt(
			 pow(p.position.re - system.particules[i].position.re,2)
			 +
			 pow(p.position.im - system.particules[i].position.im,2));
		if(distance < system.particulesSize)
		{
			p.velocity = mkComplex(0,0) - p.velocity;
			system.particules[i].velocity = (mkComplex(0, 0) - system.particules[i].velocity) * 0.9f;
			p.position = p.position + normalize(p.velocity)  * system.particulesSize;
			system.particules[i].position = system.particules[i].position + normalize(system.particules[i].velocity) * system.particulesSize;
			
		}
	}
	
	if(p.position.re <= 0)
	{
		p.position.re = -p.position.re;
		p.velocity = mkComplex(-p.velocity.re, p.velocity.im);
	}
	if(p.position.re >= Screen_Size)
	{
		p.position.re = 2 * Screen_Size-p.position.re;
		p.velocity = mkComplex(-p.velocity.re, p.velocity.im);
	}
	if(p.position.im <= 0)
	{
		p.position.im = -p.position.im;
		p.velocity = mkComplex(p.velocity.re, -p.velocity.im);
	}
	if(p.position.im >= Screen_Size)
	{
		p.position.im = 2 * Screen_Size -p.position.im;
		p.velocity = mkComplex(p.velocity.re, -p.velocity.im);
	}
}
void update(System& system)
{
	system.deltaTime = elapsedTime() - system.Time;
	system.Time = elapsedTime();
	for (int i = 0; i < system.particulesCount; i++) {
		update(system,system.particules[i]);
	}
}

void draw(const System& system)
{
	for (int i = 0; i < system.particulesCount; i++) {
		draw(system,system.particules[i]);
	}
}
void draw(const System& system,const Particule& p)
{
	color(p.index*3678678+35%256,p.index*200987+973%256,p.index*9876678+6735%256,255);
	circleFill(p.position.re, p.position.im,system.particulesSize);
}
}
