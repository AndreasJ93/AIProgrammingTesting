#pragma once

#include "D2DClass.h"
#include "AIBase.h"

class AISimulation
{
private:
	void InitializeAIs(int nrOfAgents);

	bool Turn(); //Returns false when the "simulation" is done
	void PresentResults(); //Print out the curves to the screen

	void UpdateAIs();
	void AddPointsOnCurves(); //Add the points (turn, life) for each AI's curve
	void AddSymbolsOnCurves(); //Add symbols for "special" events (such as reloading)
	bool Done(); //Check for victory!
private:
	D2DClass *d2d;
	std::vector<AIBase*> Agents;
	unsigned int numberOfTurnsDone;
	UINT nrOfAgentsAlive = 0;
public:
	AISimulation(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int height = WINDOW_HEIGHT, int width = WINDOW_WIDTH);
	~AISimulation();
	void RunSimulation(int nrOfAgents);
};