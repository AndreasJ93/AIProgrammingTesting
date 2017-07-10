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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	auto seed = time(0);
	srand(seed);

	//D2DClass d2d(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	/*Map2D map2D;
	const float windowScale = float(WINDOW_WIDTH) / float(WINDOW_HEIGHT);
	const int sizeX = 38;
	const int sizeY = 22;
	const float sizeScale = float(sizeX) / float(sizeY);
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
	int counter = 0;
	auto points = map2D.GenerateMaze(sizeY, sizeX);
	auto circleID = map2D.AddSymbol(Map2D::Map2DSymbolData::CIRCLE, 0, 0, 0.25f*scaleX, 0.25f*scaleY);
	auto symbolID = d2d.AddDataVector();
	d2d.SetBrushColour(symbolID, d2d.RandomBrushColour(0, 100, 0, 100, 25, 100));
	auto path = map2D.GetPathBetweenPoints(0, 0, sizeX - 1, sizeY - 1);
	while (d2d.run())
	{
		auto circle = map2D.GetSymbol(circleID);
		if (!path.empty())
		{
			map2D.MoveSymbol(circleID, path.front(), true);
			path.pop_front();
		}
		else
		{
			auto newPoint = map2D.GetRandomPointInMaze();
			path = map2D.GetPathBetweenPoints(floor(circle.positionX), floor(circle.positionY), newPoint.first, newPoint.second);
			d2d.SetBrushColour(symbolID, d2d.RandomBrushColour(0, 100, 0, 100, 25, 100));
		}
		d2d.ClearDataVector(symbolID);
		d2d.AddEllipse(symbolID, circle.positionX*scaleX + offsetX, circle.positionY*scaleY + offsetY, circle.sizeX, circle.sizeY);
		d2d.ClearMap();
		for (auto point : points)
		{
			d2d.AddMapPoint(point.xStart, point.yStart, point.xEnd, point.yEnd, scaleX, scaleY, offsetX, offsetY);
		}
		d2d.DrawMap(symbolID);
		Sleep(100);
	}*/

	AISimulation simulation(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 20, 12);
	simulation.RunSimulation(50);

	return 0;
}