#include "FSMStateHealing.h"
#include "FSMStateTransistionBase.h"
FSMStateHealing::FSMStateHealing()
{
	/*Empty on purpose*/
}

FSMStateHealing::~FSMStateHealing()
{
}

void FSMStateHealing::onEnter(AIBase* /*myAI*/)
{
	/*Empty on purpose*/
}

AllowedActions FSMStateHealing::onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	return ACTION_HEAL;
}

void FSMStateHealing::onExit(AIBase* /*myAI*/)
{
	/*Empty on purpose*/
}