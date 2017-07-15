#include "FSMStateAttacking.h"
#include "FSMStateTransistionBase.h"

FSMStateAttacking::FSMStateAttacking()
{
	/*Empty on purpose*/
}

FSMStateAttacking::~FSMStateAttacking()
{
}

void FSMStateAttacking::onEnter(AIBase* myAI)
{
	/*Empty on purpose*/
}

AllowedActions FSMStateAttacking::onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	if (myAI->GetTarget() == -1 || !otherAIs[myAI->GetTarget()]->GetLife())
	{
		findTarget(myAI, otherAIs, map);
	}
	return ACTION_FIRE;
}

void FSMStateAttacking::onExit(AIBase* myAI)
{
	/*Empty on purpose*/
}

uint16_t FSMStateAttacking::findTarget(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) const
{
	int xPos = int(floor(myAI->GetPositionX()));
	int yPos = int(floor(myAI->GetPositionY()));
	uint16_t ID = -1;
	for (auto Agents : otherAIs)
	{
		++ID;
		if (Agents != myAI && Agents->GetLife() && map->LineOfSight(xPos, yPos, int(floor(Agents->GetPositionX())), int(floor(Agents->GetPositionY()))))
		{
			break;
		}
	}
	return ID;
}