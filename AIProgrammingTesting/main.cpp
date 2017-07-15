#include <Windows.h>
#include <windowsx.h>
#include "D2DClass.h"
#include "AISimulation.h"
#define _USE_MATH_DEFINES
#include <time.h>
// the WindowProc function prototype

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	auto seed = time(nullptr);
	srand(unsigned int(seed));

	AISimulation simulation(hInstance, nCmdShow, 35, 20);
	simulation.RunSimulation(20000);

	return 0;
}