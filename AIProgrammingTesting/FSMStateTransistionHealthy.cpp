#include "FSMStateTransistionHealthy.h"
#include "AIBase.h"

FSMStateTransistionHealthy::FSMStateTransistionHealthy()
{
	/*Kept empty on purpose*/
}

FSMStateTransistionHealthy::~FSMStateTransistionHealthy()
{
	/*Kept empty on purpose*/
}

bool FSMStateTransistionHealthy::isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	if (myAI->GetLife() >= 15)
		return true;
	return false;
}

FSMStateBase* FSMStateTransistionHealthy::getNextState()
{
	return states.front();
}

void FSMStateTransistionHealthy::onTransistion(AIBase* myAI)
{
	myAI->SetTarget(-1);
}