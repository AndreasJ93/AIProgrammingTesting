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

	if (myAI->GetTarget() != -1 && otherAIs[myAI->GetTarget()]->GetLife())
	{
		for (auto Agents : otherAIs)
		{
			if (Agents != myAI && Agents->GetLife() && map->LineOfSight(xPos, yPos, int(floor(Agents->GetPositionX())), int(floor(Agents->GetPositionY()))))
			{
				return false;
			}
		}
	}
	myAI->SetTarget(-1);
	return true;
}

FSMStateBase* FSMStateTransistionNoEnemy::getNextState()
{
	return states.front();
}

void FSMStateTransistionNoEnemy::onTransistion(AIBase* myAI)
{
	myAI->SetTarget(-1);
}