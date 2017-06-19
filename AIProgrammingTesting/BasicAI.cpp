#include "BasicAI.h"
#include <algorithm>
BasicAI::BasicAI(uint16_t life) : AIBase(life)
{
}

BasicAI::~BasicAI()
{
}

AllowedActions BasicAI::DecideAction(std::vector<AIBase*> allAIs, unsigned int myID)
{
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
				float timeToKill = agents->GetLife() / (this->GetDamage()*this->myEntity->Accuracy());
				float timeToKillMe = this->GetLife() / (agents->GetDamage()*agents->GetAccuracy());
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