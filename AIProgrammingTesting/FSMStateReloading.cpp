#include "FSMStateReloading.h"

FSMStateReloading::FSMStateReloading()
{
	/*Kept empty on purpose*/
}

FSMStateReloading::~FSMStateReloading()
{
	/*Kept empty on purpose*/
}

void FSMStateReloading::onEnter(AIBase* myAI)
{
	/*Kept empty on purpose*/
}

AllowedActions FSMStateReloading::onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	return ACTION_RELOAD;
}

void FSMStateReloading::onExit(AIBase* myAI)
{
	/*Kept empty on purpose*/
}