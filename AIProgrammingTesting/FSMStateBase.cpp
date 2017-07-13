#include "FSMStateBase.h"
#include "FSMStateTransistionBase.h"

FSMStateBase::FSMStateBase()
{
}

FSMStateBase::~FSMStateBase()
{
}

FSMStateBase* FSMStateBase::checkTransistions(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	for (auto transistion : transistions)
	{
		if (transistion->isValid(myAI, otherAIs, map))
			return transistion->getNextState();
	}
	return nullptr;
}

void FSMStateBase::addTransistion(FSMStateTransistionBase* transistionToAdd)
{
	transistions.push_back(transistionToAdd);
}