#include "AISimulation.h"
#include "UtilityBasedAI.h"
#include <string>
void AISimulation::InitializeAIs(int nrOfAgents)
{
	for (int i = 0; i < nrOfAgents; i++)
	{
		d2d->AddDataVector();

		d2d->SetBrushColour(i, d2d->RandomBrushColour(0, 100, 0, 100, 25, 100));
		//TO DO; place out the AIs in a non-random way. Read from file? (JSON?)
		float dirtyFix = 0.001f;
		float posX = i*rand() % 50 * rand() % 2 - 1 + (250 * rand() % 10) * rand() % 3 - 2;
		float posY = i*rand() % 50 * rand() % 2 - 1 + (250 * rand() % 10) * rand() % 3 - 2;
		Agents.push_back(new UtilityBasedAI(rand() % 100 + 250, posX, posY));
	}
}

bool AISimulation::Turn()
{
	unsigned int ID = 0;
	UpdateAIs();
	AddPointsOnCurves();
	AddSymbolsOnCurves();
	numberOfTurnsDone++;
	return Done();
}

void AISimulation::PresentResults()
{
	d2d->UpdateAll();
	d2d->Draw();
}

void AISimulation::UpdateAIs()
{
	unsigned int ID = 0;
	for (auto &AI : Agents)
	{
		if (AI->GetLife())
		{
			switch (AI->DecideAction(Agents, ID))
			{
			case AllowedActions::ACTION_FIRE:
			{
				//Get target, get damage, deal damage to the target ("perform action" call?)
				uint16_t targetID = AI->GetTarget();
				if (targetID != uint16_t(-1) && AI->Fire())
				{
					float distance = sqrt(pow(AI->GetPositionX() - Agents[targetID]->GetPositionX(), 2) + pow(AI->GetPositionY() - Agents[targetID]->GetPositionY(), 2));
					if (((rand() % 10000) / 100.0f) / 100.0f <= AI->GetAccuracy(distance))
						Agents[targetID]->TakeDamage(AI->GetDamage(distance));
				}
				break;
			}
			case AllowedActions::ACTION_RELOAD:
			{
				//Perform the reload
				AI->Reload();
				break;
			}
			case AllowedActions::ACTION_HEAL:
			{
				//Perform the healing action
				AI->Heal(rand() % 50);
				break;
			}
			}
		}
		ID++;
	}
}

void AISimulation::AddPointsOnCurves()
{
	unsigned int ID = 0;
	for (auto &AI : Agents)
	{
		d2d->AddPoint(ID, numberOfTurnsDone, AI->GetLife());
		ID++;
	}
}

void AISimulation::AddSymbolsOnCurves()
{
	unsigned int ID = 0;
	for (auto &AI : Agents)
	{
		if (AI->GetLife())
		{
			switch (AI->GetLastPerformedAction())
			{
			case AllowedActions::ACTION_FIRE:
			{
				//"If nothing is put out, it's a fire"
				break;
			}
			case AllowedActions::ACTION_RELOAD:
			{
				d2d->AddCircle(ID, numberOfTurnsDone, AI->GetLife(), .5f);
				break;
			}
			case AllowedActions::ACTION_HEAL:
			{
				d2d->AddRect(ID, float(numberOfTurnsDone),
					float(AI->GetLife()),
					.5f,
					.5f);
				break;
			}
			}
		}
		ID++;
	}
}

bool AISimulation::Done()
{
	nrOfAgentsAlive = 0;
	for (auto &AI : Agents)
	{
		if (AI->GetLife())
		{
			nrOfAgentsAlive++;
		}
	}
	return nrOfAgentsAlive > 1 ? true : false;
}

AISimulation::AISimulation(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int height, int width)
{
	d2d = new D2DClass(hInstance, hPrevInstance, lpCmdLine, nCmdShow, height, width);
	numberOfTurnsDone = 0;
}

AISimulation::~AISimulation()
{
}

void AISimulation::RunSimulation(int nrOfAgents)
{
	UINT numberOfTurnsID = d2d->AddText(std::string("Number of turns: " + std::to_string(numberOfTurnsDone)), 0.0f, 0.0f);
	UINT agentsAliveID = d2d->AddText(std::string("Agents Alive: " + std::to_string(nrOfAgents)), 250.0f, 0.0f);
	InitializeAIs(nrOfAgents);
	while (Turn())
	{
		d2d->DrawTextOnly();
		d2d->UpdateText(numberOfTurnsID, std::string("Number of turns: " + std::to_string(numberOfTurnsDone)));
		d2d->UpdateText(agentsAliveID, std::string("Agents Alive: " + std::to_string(nrOfAgentsAlive)));
	}
	d2d->UpdateText(numberOfTurnsID, std::string("Number of turns: " + std::to_string(numberOfTurnsDone)));
	d2d->UpdateText(agentsAliveID, std::string("Agents Alive: " + std::to_string(nrOfAgentsAlive)));
	d2d->UpdateAll();
	d2d->Draw();
	while (d2d->run())
	{
	}
}