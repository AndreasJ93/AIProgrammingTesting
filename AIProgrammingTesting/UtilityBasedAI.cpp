#include "UtilityBasedAI.h"
#include <algorithm>
UtilityBasedAI::UtilityBasedAI(uint16_t life, float positionX, float positionY) : AIBase(life, positionX, positionY)
{
	//Add entity creation here!
}

UtilityBasedAI::~UtilityBasedAI()
{
}

AllowedActions UtilityBasedAI::DecideAction(std::vector<AIBase*> allAIs, unsigned int myID)
{
	//COMMENT THIS AI IN DETAIL!
	if (myEntity->GetLife() < 15)
	{
		if ((rand() % 5) == 0)
		{
			targetID = -1;
			lastAction = ACTION_HEAL;
			return ACTION_HEAL;
		}
	}

	if (myEntity->EquipedWeapon()->CurrentAmmo() && myEntity->EquipedWeapon()->ReloadingDone())
	{
		unsigned int ID = 0;
		float maximumAccuracy = 0.0f;
		struct threatFloat
		{
			threatFloat(unsigned int id, float threatRatios) { this->id = id; this->threatRatios = threatRatios; };
			unsigned int id;
			float threatRatios;
			bool operator<(threatFloat &rhs) { return this->threatRatios < rhs.threatRatios ? true : false; }
		};
		std::vector<threatFloat> threatRatios;
		for (auto &agents : allAIs)
		{
			if (myID != ID && agents->GetLife())
			{
				float distance = sqrt(pow(agents->GetPositionX() - myEntity->PositionX(), 2) + pow(agents->GetPositionY() - myEntity->PositionY(), 2));
				float accuracy = this->GetAccuracy(distance);
				if (accuracy > maximumAccuracy)
					maximumAccuracy = accuracy;

				if (accuracy > 0.5f) //Only attack "far away" targets
				{
					float timeToKill = agents->GetLife() / (this->GetDamage(distance)*this->myEntity->Accuracy(distance));
					float timeToKillMe = this->GetLife() / (agents->GetDamage(distance)*agents->GetAccuracy(distance));
					float threat = (timeToKillMe + (3 * timeToKill)) / 4;
					threatRatios.push_back(threatFloat(ID, threat));
				}
			}
			ID++;
		}
		if (maximumAccuracy > 0.5f) //We have a "close" target
		{
			std::sort(threatRatios.begin(), threatRatios.end());
			targetID = threatRatios[0].id;
			lastAction = ACTION_FIRE;
		}
		else
		{
			ID = 0;
			unsigned int closestAgent = -1;
			float closestDistance = 1000.0f;
			enum Direction
			{
				LEFT,
				UP,
				RIGHT,
				DOWN
			};

			Direction directionToClosest;

			for (auto &agents : allAIs)
			{
				if (myID != ID && agents->GetLife())
				{
					float distance = sqrt(pow(agents->GetPositionX() - myEntity->PositionX(), 2) + pow(agents->GetPositionY() - myEntity->PositionY(), 2));
					if (distance < closestDistance)
					{
						closestDistance = distance;
						closestAgent = ID;
						float xDistance = agents->GetPositionX() - myEntity->PositionX();
						float yDistance = agents->GetPositionY() - myEntity->PositionY();
						if (abs(xDistance) < abs(yDistance))
						{
							if (xDistance < 0.0f)
								directionToClosest = LEFT;
							else
								directionToClosest = RIGHT;
						}
						else
						{
							if (yDistance < 0.0f)
								directionToClosest = DOWN;
							else
								directionToClosest = UP;
						}
					}
				}
				ID++;
			}
			switch (directionToClosest)
			{
			case LEFT:
				myEntity->MovePositionX((allAIs[closestAgent]->GetPositionX() - myEntity->PositionX()) / 2);
				break;
			case RIGHT:
				myEntity->MovePositionX((allAIs[closestAgent]->GetPositionX() - myEntity->PositionX()) / 2);
				break;
			case UP:
				myEntity->MovePositionY((allAIs[closestAgent]->GetPositionY() - myEntity->PositionY()) / 2);
				break;
			case DOWN:
				myEntity->MovePositionY((allAIs[closestAgent]->GetPositionY() - myEntity->PositionY()) / 2);
				break;
			}
			lastAction = ACTION_MOVE;
		}
	}
	else {
		targetID = -1;
		lastAction = ACTION_RELOAD;
	}
	return lastAction;
}