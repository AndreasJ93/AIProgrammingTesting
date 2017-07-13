#include "FSMStateTransistionNoAmmo.h"
#include "AIBase.h"

FSMStateTransistionNoAmmo::FSMStateTransistionNoAmmo()
{
	/*Kept empty on purpose*/
}

FSMStateTransistionNoAmmo::~FSMStateTransistionNoAmmo()
{
	/*Kept empty on purpose*/
}

bool FSMStateTransistionNoAmmo::isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	if (myAI->GetEntity()->EquipedWeapon()->CurrentAmmo())
		return false;

	return true;
}

FSMStateBase* FSMStateTransistionNoAmmo::getNextState()
{
	return states.front();
}

void FSMStateTransistionNoAmmo::onTransistion(AIBase* myAI)
{
	/*Kept empty on purpose*/
}