#include "Sandbox.hpp"
#include "SolarSystem.hpp"
#include "Grapic.h"

using namespace grapic;

namespace SolarSystem {


PlanetInfo Sun,Earth,Mercury,Moon;

SolarSystem init()
{
	backgroundColor(0,0,0,0);
	SolarSystem system{};
	Complex worldCenter = mkComplex(Screen_Size/2,Screen_Size/2);
	system.Sun = worldCenter;
	system.Earth = worldCenter + mkComplex(Screen_Size/4, 0);
	system.Moon = system.Earth + mkComplex(Screen_Size/8, 0);
	system.Mercury = worldCenter+ mkComplex(Screen_Size/6, 0);
	
	Sun = {grapic::image("Images/sun.png"),Screen_Size/16};
	Earth = {grapic::image("Images/earth.png"),Screen_Size/32};
	Mercury = {grapic::image("Images/mercury.png"),Screen_Size/64};
	Moon = {grapic::image("Images/moon.png"),Screen_Size/64};
	
	return system;
}
void update(SolarSystem& system)
{
	system.deltaTime = elapsedTime() - system.Time;
	system.Time = elapsedTime();
	
	system.Mercury = rotate(system.Mercury, system.Sun, system.deltaTime * 180);
	system.Earth = rotate(system.Earth, system.Sun, system.deltaTime * 60);
	system.Moon = rotate(system.Moon, system.Sun, system.deltaTime * 60);
	system.Moon = rotate(system.Moon, system.Earth, system.deltaTime * 360);
}

void draw(const SolarSystem& system)
{
	draw(Sun,system.Sun);
	draw(Moon,system.Moon);
	draw(Earth,system.Earth);
	draw(Mercury,system.Mercury);
}

void draw(PlanetInfo info,Complex position)
{
	image_draw(info.image, position.re-info.size,position.im-info.size,info.size*2,info.size*2);
}

}
