#include <Windows.h>
#include <windowsx.h>
#include "D2DClass.h"
#include "AISimulation.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include <time.h>
#include <string>
// the WindowProc function prototype

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	srand(time(0));

	/*D2DClass d2d(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	int counter = 0;
	UINT textID = d2d.AddText(std::string("Counter: " + std::to_string(counter)), 0.0f, 0.0f);
	while (d2d.run())
	{
		d2d.Draw();
		Sleep(10);
		counter++;
		d2d.UpdateText(textID, std::string("Counter: " + std::to_string(counter)));
	}*/

	AISimulation simulation(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	simulation.RunSimulation(250);

	return 0;
}