#include "FSMStateTransistionReloadingDone.h"
#include <functional>

FSMStateTransistionReloadingDone::FSMStateTransistionReloadingDone()
{
	/*Kept empty on purpose*/
}

FSMStateTransistionReloadingDone::~FSMStateTransistionReloadingDone()
{
	/*Kept empty on purpose*/
}

bool FSMStateTransistionReloadingDone::isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	if (myAI->GetEntity()->EquipedWeapon()->CurrentAmmo())
		return true;

	return false;
}

FSMStateBase* FSMStateTransistionReloadingDone::getNextState()
{
	return states.front();
}

void FSMStateTransistionReloadingDone::onTransistion(AIBase* myAI)
{
	myAI->SetTarget(-1);
}