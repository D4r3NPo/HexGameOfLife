#include "Sandbox.hpp"
#include "Grapic.h"
#include "Newton.hpp"

using namespace grapic;
using namespace std;

int main(int,char**)
{
	winInit("[Sandbox]", Screen_Size, Screen_Size);
	auto data = Newton::init();
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
