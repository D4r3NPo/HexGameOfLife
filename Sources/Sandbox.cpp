#include "Sandbox.hpp"
#include "Grapic.h"
#include "SolarSystem.hpp"

using namespace grapic;
using namespace std;

int main(int,char**)
{
	winInit("[Sandbox]", Screen_Size, Screen_Size);
	auto data = SolarSystem::init();
	do
	{
		winClear();
		update(data);
		draw(data);
	}
	while(!winDisplay());
	winQuit();
	return 0;
}
