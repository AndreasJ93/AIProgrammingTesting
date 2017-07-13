#include "FSMStateHealing.h"
#include "AIBase.h"
FSMStateHealing::FSMStateHealing()
{
	/*Empty on purpose*/
}

FSMStateHealing::~FSMStateHealing()
{
	/*Empty on purpose*/
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