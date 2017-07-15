#include "FSMStateTransistionOnSight.h"
#include "AIBase.h"
#include "Map.h"

FSMStateTransistionOnSight::FSMStateTransistionOnSight()
{
	/*Empty on purpose*/
}

FSMStateTransistionOnSight::~FSMStateTransistionOnSight()
{
	/*Empty on purpose*/
}

bool FSMStateTransistionOnSight::isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	int xPos = int(floor(myAI->GetPositionX()));
	int yPos = int(floor(myAI->GetPositionY()));
	uint16_t ID = -1;
	for (auto Agents : otherAIs)
	{
		++ID;
		if (Agents != myAI && Agents->GetLife() && map->LineOfSight(xPos, yPos, int(floor(Agents->GetPositionX())), int(floor(Agents->GetPositionY()))))
		{
			myAI->SetTarget(ID);
			return true;
		}
	}
	myAI->SetTarget(-1);
	return false;
}

FSMStateBase* FSMStateTransistionOnSight::getNextState()
{
	return states.front();
}

void FSMStateTransistionOnSight::onTransistion(AIBase*)
{
	/*Empty*/
}