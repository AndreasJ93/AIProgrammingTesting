#pragma once

#include "D2DClass.h"
#include "Map.h"
#include "AIBase.h"

class AISimulation
{
private:
	void InitializeAIs(int nrOfAgents);

	bool Turn(); //Returns false when the "simulation" is done
	void PresentResults() const; //Print out the curves to the screen

	void UpdateAIs();
	void AddPointsOnCurves(); //Add the points (turn, life) for each AI's curve
	void AddSymbolsOnCurves(); //Add symbols for "special" events (such as reloading)
	bool Done(); //Check for victory!
private:
	struct AIInformation
	{
		AIBase* agent;
		UINT symbolID;
		UINT curveID;
		std::deque<Map2D::Direction> path;
		D2DClass::BrushColour* colour;
	};

	D2DClass* d2d;
	Map2D* map;
	std::vector<AIInformation> Agents;
	UINT symbolVectorID;
	unsigned int numberOfTurnsDone;
	UINT nrOfAgentsAlive = 0;

	int sizeX;
	int sizeY;
	float sizeScale;
	float offsetX;
	float offsetY;
	float scaleX;
	float scaleY;
public:
	AISimulation(HINSTANCE hInstance, int nCmdShow, int mazeWidth, int mazeHeight, int height = WINDOW_HEIGHT, int width = WINDOW_WIDTH);
	~AISimulation();
	void RunSimulation(int nrOfAgents);
};
