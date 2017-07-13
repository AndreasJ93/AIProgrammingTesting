#include "FSMStateAttacking.h"

FSMStateAttacking::FSMStateAttacking()
{
	/*Empty on purpose*/
}

FSMStateAttacking::~FSMStateAttacking()
{
	/*Empty on purpose*/
}

void FSMStateAttacking::onEnter(AIBase* myAI)
{
	/*Empty on purpose*/
}

AllowedActions FSMStateAttacking::onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	return ACTION_FIRE;
}

void FSMStateAttacking::onExit(AIBase* myAI)
{
	/*Empty on purpose*/
}