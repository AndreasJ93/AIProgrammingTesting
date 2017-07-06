#include <Windows.h>
#include <windowsx.h>
#include "D2DClass.h"
#include "AISimulation.h"
#include "Map.h"
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

	D2DClass d2d(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	Map2D map2D;
	const int sizeX = 5;
	const int sizeY = 5;
	const float sizeScale = float(sizeX) / float(sizeY);
	const float windowScale = float(WINDOW_WIDTH) / float(WINDOW_HEIGHT);
	float offsetX = 10.0f;
	float offsetY = 10.0f*sizeScale*windowScale;
	if (sizeY > sizeX)
	{
		offsetX /= sizeScale;
		offsetX /= windowScale;
		offsetY /= sizeScale;
	}
	const float scaleX = (WINDOW_WIDTH - 4 * offsetX) / (float(sizeX));
	const float scaleY = (WINDOW_HEIGHT - 4 * offsetY) / (float(sizeY));

	auto points = map2D.GenerateMaze(sizeY, sizeX);

	for (auto point : points)
	{
		d2d.AddMapPoint(point.xStart, point.yStart, point.xEnd, point.yEnd, scaleX, scaleY, offsetX, offsetY);
	}

	while (d2d.run())
	{
		d2d.DrawMap();
	}

	/*
	AISimulation simulation(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	simulation.RunSimulation(2500);
	*/

	return 0;
}