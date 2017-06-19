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
	/*D2DClass d2d(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	UINT ID = d2d.AddDataVector();
	d2d.SetBrushColour(ID, 1.0f, 0.0f, 0.0f, 1.0f);
	float arr[2000] = { 0 };
	float highestValue = 0.0f;
	for (int i = -1000; i < 1000; i++)
	{
		arr[i + 1000] = sinf((i) * 25.0f* 3.14159265358979323846 / 500)*pow(abs(i*1.0f), 3.0f / 10.0f);
		if (abs(arr[i + 1000]) > highestValue)
		{
			highestValue = abs(arr[i + 1000]);
		}
		d2d.AddPoint(ID, i + 1000, arr[i + 1000]);
	}
	d2d.UpdateAll();
	d2d.Draw();
	while (d2d.run())
	{
	}*/
	AISimulation simulation(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	simulation.RunSimulation(1000);

	return 0;
}