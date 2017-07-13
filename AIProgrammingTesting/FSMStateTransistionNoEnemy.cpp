#include "FSMStateTransistionNoEnemy.h"
#include "AIBase.h"

FSMStateTransistionNoEnemy::FSMStateTransistionNoEnemy()
{
	/*Kept empty on purpose*/
}

FSMStateTransistionNoEnemy::~FSMStateTransistionNoEnemy()
{
	/*Kept empty on purpose*/
}

bool FSMStateTransistionNoEnemy::isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	int xPos = int(floor(myAI->GetPositionX()));
	int yPos = int(floor(myAI->GetPositionY()));

	for (auto Agents : otherAIs)
	{
		if (map->LineOfSight(xPos, yPos, int(floor(Agents->GetPositionX())), int(floor(Agents->GetPositionY()))))
			return false;
	}
	return true;
}

FSMStateBase* FSMStateTransistionNoEnemy::getNextState()
{
	return states.front();
}

void FSMStateTransistionNoEnemy::onTransistion(AIBase* myAI)
{
	/*Kept empty on purpose*/
}