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
				float timeToKill = agents->GetLife() / (this->GetDamage(distance)*this->myEntity->Accuracy(distance));
				float timeToKillMe = this->GetLife() / (agents->GetDamage(distance)*agents->GetAccuracy(distance));
				float threat = (timeToKillMe + (3 * timeToKill)) / 4;
				threatRatios.push_back(threatFloat(ID, threat));
			}
			ID++;
		}
		std::sort(threatRatios.begin(), threatRatios.end());
		targetID = threatRatios[0].id;
		lastAction = ACTION_FIRE;
		return ACTION_FIRE;
	}
	targetID = -1;
	lastAction = ACTION_RELOAD;
	return ACTION_RELOAD;
}