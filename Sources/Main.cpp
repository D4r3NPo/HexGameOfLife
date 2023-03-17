#include "Main.hpp"
#include "Grapic.h"
#include "HexGameOfLife.hpp"

using namespace grapic;
using namespace std;
using namespace HexGameOfLife;

int main(int,char**)
{
	winInit("[Hex Game of Life]", Screen_Size, Screen_Size);
	World world = HexGameOfLife::init();
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
