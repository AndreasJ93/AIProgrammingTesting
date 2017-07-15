#include "FSMStateTransistionLowHealth.h"
#include "AIBase.h"

FSMStateTransistionLowHealth::FSMStateTransistionLowHealth()
{
	/*Empty on purpose*/
}

FSMStateTransistionLowHealth::~FSMStateTransistionLowHealth()
{
	/*Empty on purpose*/
}

bool FSMStateTransistionLowHealth::isValid(AIBase* myAI, std::vector<AIBase*> /*otherAIs*/, Map2D* /*map*/)
{
	if (myAI->GetLife() < 15)
		return true;

	return false;
}

FSMStateBase* FSMStateTransistionLowHealth::getNextState()
{
	return states.front();
}

void FSMStateTransistionLowHealth::onTransistion(AIBase* myAI)
{
	myAI->SetTarget(-1);
}