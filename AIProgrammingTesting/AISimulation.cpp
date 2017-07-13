#include "AISimulation.h"
#include "UtilityBasedAI.h"
#include "AIFSM.h"
#include <string>

void AISimulation::InitializeAIs(int nrOfAgents)
{
	for (int i = 0; i < nrOfAgents; i++)
	{
		//TO DO; place out the AIs in a non-random way. Read from file? (JSON?)
		std::pair<int, int> startPoint = map->GetRandomPointInMaze();
		std::pair<int, int> goal = map->GetRandomPointInMaze();
		AIInformation agent;
		agent.curveID = d2d->AddDataVector();
		auto temp = d2d->RandomBrushColour(0, 100, 0, 100, 25, 100);
		D2DClass::BrushColour* brush = new D2DClass::BrushColour(temp);

		d2d->SetBrushColour(agent.curveID, temp);
		//agent.agent = new UtilityBasedAI(rand() % 100 + 250, 1.0f*startPoint.first, 1.0f*startPoint.second);
		agent.agent = new AIFSM(rand() % 100 + 250, 1.0f*startPoint.first, 1.0f*startPoint.second);
		agent.path = map->GetPathBetweenPoints(startPoint.first, startPoint.second, goal.first, goal.second);
		agent.symbolID = map->AddSymbol(Map2D::Map2DSymbolData::CIRCLE, startPoint.first, startPoint.second, 0.25f * scaleX, 0.25f * scaleY);
		agent.colour = brush;
		Agents.push_back(agent);
	}
}

bool AISimulation::Turn()
{
	UpdateAIs();
	AddPointsOnCurves();
	AddSymbolsOnCurves();
	numberOfTurnsDone++;
	return Done();
}

void AISimulation::PresentResults() const
{
	d2d->UpdateAll();
	d2d->Draw();
}

void AISimulation::UpdateAIs()
{
	unsigned int ID = 0;
	std::vector<AIBase*> allAgents;
	for (auto& it : Agents)
		allAgents.push_back(it.agent);
	for (auto& AI : Agents)
	{
		auto circle = map->GetSymbol(AI.symbolID);
		if (AI.agent->GetLife())
		{
			switch (AI.agent->DecideAction(allAgents, ID, map))
			{
			case ACTION_FIRE:
			{
				//Get target, get damage, deal damage to the target ("perform action" call?)
				uint16_t targetID = AI.agent->GetTarget();
				if (targetID != uint16_t(-1) && AI.agent->Fire())
				{
					float distance = sqrt(pow(AI.agent->GetPositionX() - Agents[targetID].agent->GetPositionX(), 2) + pow(AI.agent->GetPositionY() - Agents[targetID].agent->GetPositionY(), 2));
					if (rand() % 10000 / 100.0f / 100.0f <= AI.agent->GetAccuracy(distance))
						Agents[targetID].agent->TakeDamage(AI.agent->GetDamage(distance));
				}
				break;
			}
			case ACTION_RELOAD:
			{
				//Perform the reload
				AI.agent->Reload();
				break;
			}
			case ACTION_HEAL:
			{
				//Perform the healing action
				AI.agent->Heal(rand() % 50);
				break;
			}
			case ACTION_MOVE:
				if (!AI.path.empty())
				{
					map->MoveSymbol(AI.symbolID, AI.path.front(), true);
					circle = map->GetSymbol(AI.symbolID);
					AI.agent->SetPositionX(floor(circle.positionX));
					AI.agent->SetPositionY(floor(circle.positionY));
					AI.path.pop_front();
				}
				else
				{
					auto newPoint = map->GetRandomPointInMaze();
					AI.path = map->GetPathBetweenPoints(int(floor(circle.positionX)), int(floor(circle.positionY)), newPoint.first, newPoint.second);
				}
				break;
			}
			d2d->AddEllipse(symbolVectorID, circle.positionX * scaleX + offsetX, circle.positionY * scaleY + offsetY, circle.sizeX, circle.sizeY, true, AI.colour);
		}

		ID++;
	}
}

void AISimulation::AddPointsOnCurves()
{
	for (auto& AI : Agents)
	{
		d2d->AddPoint(AI.curveID, float(numberOfTurnsDone), AI.agent->GetLife());
	}
}

void AISimulation::AddSymbolsOnCurves()
{
	for (auto& AI : Agents)
	{
		if (AI.agent->GetLife())
		{
			switch (AI.agent->GetLastPerformedAction())
			{
			case ACTION_FIRE:
			{
				//"If nothing is put out, it's a fire"
				break;
			}
			case ACTION_RELOAD:
			{
				d2d->AddCircle(AI.curveID, float(numberOfTurnsDone), AI.agent->GetLife(), .5f);
				break;
			}
			case ACTION_HEAL:
			{
				d2d->AddRect(AI.curveID, float(numberOfTurnsDone),
					float(AI.agent->GetLife()),
					.5f,
					.5f);
				break;
			}
			case ACTION_MOVE:

				break;
			}
		}
	}
}

bool AISimulation::Done()
{
	nrOfAgentsAlive = 0;
	for (auto& AI : Agents)
	{
		if (AI.agent->GetLife())
		{
			nrOfAgentsAlive++;
		}
	}
	return nrOfAgentsAlive > 1 ? true : false;
}

AISimulation::AISimulation(HINSTANCE hInstance, int nCmdShow, int mazeWidth, int mazeHeight, int height, int width)
{
	d2d = new D2DClass(hInstance, nCmdShow, height, width);
	map = new Map2D();
	map->GenerateMaze(mazeHeight, mazeWidth);

	sizeX = mazeWidth;
	sizeY = mazeHeight;
	sizeScale = float(sizeX) / float(sizeY);
	offsetX = 10.0f;
	offsetY = offsetX * sizeScale * d2d->GetWindowScale();

	if (sizeY > sizeX)
	{
		offsetX /= sizeScale;
		offsetX /= d2d->GetWindowScale();
		offsetY /= sizeScale;
	}
	scaleX = (WINDOW_WIDTH - 4 * offsetX) / float(sizeX);
	scaleY = (WINDOW_HEIGHT - 4 * offsetY) / float(sizeY);

	symbolVectorID = d2d->AddDataVector();
	d2d->SetBrushColour(symbolVectorID, d2d->RandomBrushColour(0, 100, 0, 100, 25, 100));
	numberOfTurnsDone = 0;
}

AISimulation::~AISimulation()
{
	for (auto it : Agents)
	{
		delete it.colour;
		delete it.agent;
	}
	delete map;
	delete d2d;
}

void AISimulation::RunSimulation(int nrOfAgents)
{
	UINT numberOfTurnsID = d2d->AddText(std::string("Number of turns: " + std::to_string(numberOfTurnsDone)), 0.0f, 0.0f);
	UINT agentsAliveID = d2d->AddText(std::string("Agents Alive: " + std::to_string(nrOfAgents)), 250.0f, 0.0f);
	InitializeAIs(nrOfAgents);
	std::vector<Map2D::Map2DWallData> points = map->GetMazePoints();
	while (Turn())
	{
		d2d->BeginDrawing();
		d2d->DrawTextOnly();
		d2d->UpdateText(numberOfTurnsID, std::string("Number of turns: " + std::to_string(numberOfTurnsDone)));
		d2d->UpdateText(agentsAliveID, std::string("Agents Alive: " + std::to_string(nrOfAgentsAlive)));

		for (auto point : points)
		{
			d2d->AddMapPoint(point.xStart, point.yStart, point.xEnd, point.yEnd, scaleX, scaleY, offsetX, offsetY);
		}
		d2d->DrawMap(symbolVectorID);
		d2d->EndDrawing();
		Sleep(75);
		d2d->ClearDataVector(symbolVectorID);
		d2d->ClearMap();
	}
	d2d->UpdateText(numberOfTurnsID, std::string("Number of turns: " + std::to_string(numberOfTurnsDone)));
	d2d->UpdateText(agentsAliveID, std::string("Agents Alive: " + std::to_string(nrOfAgentsAlive)));
	d2d->BeginDrawing();
	for (auto AI : Agents)
	{
		d2d->Update(AI.curveID);
		d2d->Draw(AI.curveID);
	}
	d2d->EndDrawing();
	while (d2d->run())
	{
	}
}