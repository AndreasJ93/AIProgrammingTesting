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

	for (auto Agents : otherAIs)
	{
		if (map->LineOfSight(xPos, yPos, int(floor(Agents->GetPositionX())), int(floor(Agents->GetPositionY()))))
			return true;
	}
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