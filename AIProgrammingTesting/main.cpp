#include <Windows.h>
#include <windowsx.h>
#include "D2DClass.h"
#include "AISimulation.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include <time.h>
// the WindowProc function prototype

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	srand(time(0));

	D2DClass d2d(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	while (d2d.run())
	{
	}

	//AISimulation simulation(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	//simulation.RunSimulation(2000);

	return 0;
}