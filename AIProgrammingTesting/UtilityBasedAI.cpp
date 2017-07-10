#include "UtilityBasedAI.h"
#include <algorithm>
UtilityBasedAI::UtilityBasedAI(uint16_t life, float positionX, float positionY) : AIBase(life, positionX, positionY)
{
	//Add entity creation here!
}

UtilityBasedAI::~UtilityBasedAI()
{
}

AllowedActions UtilityBasedAI::DecideAction(std::vector<AIBase*> allAIs, unsigned int myID, Map2D* map)
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
		int positionX = myEntity->PositionX();
		int positionY = myEntity->PositionY();
		for (auto &agents : allAIs)
		{
			int enemyPosX = agents->GetPositionX();
			int enemyPosY = agents->GetPositionY();
			if (myID != ID && agents->GetLife() && map->LineOfSight(positionX, positionY, enemyPosX, enemyPosY))
			{
				float distance = sqrt(pow(enemyPosX - positionX, 2) + pow(enemyPosY - positionY, 2));
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
			lastAction = ACTION_MOVE;
		}
	}
	else {
		targetID = -1;
		lastAction = ACTION_RELOAD;
	}
	return lastAction;
}