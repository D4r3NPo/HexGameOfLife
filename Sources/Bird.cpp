#include "Bird.hpp"
using namespace grapic;

namespace Bird{
Bird init()
{
	return {image("Images/bird.png"),image("Images/wingL.png"),image("Images/wingR.png"),mkComplex(Screen_Size/2,Screen_Size/2),0,0,0,false};
}
void update(Bird& bird)
{
	if(elapsedTime() - bird.Time < 0.016) return;
	
	bird.deltaTime = elapsedTime() - bird.Time;
	bird.Time = elapsedTime();
	
	if(isKeyPressed(SDLK_SPACE)) bird.toggle = !bird.toggle;
	
	bird.wingsAngle = sin(bird.Time * 10) * 20;
	if(bird.toggle)
	{
		bird.position = mkComplex(Screen_Size/2, Screen_Size/2)+ mkComplex(cos(bird.Time), sin(bird.Time))* 100;
	}
	else
	{
		bird.position = mkComplex(Screen_Size/2, Screen_Size/2)+ mkComplex(sin(bird.Time), cos(bird.Time))* 100;
	}

}
void draw(Bird& bird)
{
	for (int x = 0; x < Screen_Size; x+=10) {
		for (int y = 0; y < 360; y+= 10) {
			Complex a = mkComplex(Screen_Size/2, Screen_Size/2)+ mkComplexExp(x, y);
			a = rotate(a, a, sin(elapsedTime())*360);
			point(a.re, a.im);
		}
	}
	
	image_draw(bird.wingR, bird.position.re -64 + 50, bird.position.im-70, 128,128,bird.wingsAngle);
	image_draw(bird.wingL, bird.position.re -64 - 50, bird.position.im-70, 128,128,-bird.wingsAngle);
	image_draw(bird.birdImg, bird.position.re-64, bird.position.im-64, 128,128);
}

}
