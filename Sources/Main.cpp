#include "Main.hpp"
#include "Grapic.h"
#include "World.h"

using namespace grapic;
using namespace std;

int main(int,char**)
{
	winInit("[Hex Game of Life]", Screen_Size, Screen_Size);
	World world = WorldInit();
	do
	{
		winClear();
		update(world);
		draw(world);
	}
	while(!winDisplay());
	winQuit();
	return 0;
}
