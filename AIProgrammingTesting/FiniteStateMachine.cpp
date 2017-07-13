#include "FiniteStateMachine.h"
#include "FSMStateAttacking.h"
#include "FSMStateHealing.h"
#include "FSMStateReloading.h"
#include "FSMStateMoving.h"
#include "FSMStateTransistionHealthy.h"
#include "FSMStateTransistionLowHealth.h"
#include "FSMStateTransistionNoAmmo.h"
#include "FSMStateTransistionOnSight.h"
#include "FSMStateTransistionReloadingDone.h"
#include "FSMStateTransistionNoEnemy.h"

FiniteStateMachine::FiniteStateMachine()
{
	FSMStateAttacking* attackingState = new FSMStateAttacking;
	FSMStateMoving* movingState = new FSMStateMoving;
	FSMStateHealing* healingState = new FSMStateHealing;
	FSMStateReloading* reloadingState = new FSMStateReloading;

	/*Attacking State*/
	FSMStateTransistionLowHealth* lowHealthTransistion = new FSMStateTransistionLowHealth;
	lowHealthTransistion->addState(healingState);
	attackingState->addTransistion(lowHealthTransistion);

	FSMStateTransistionNoEnemy* noEnemyTransistion = new FSMStateTransistionNoEnemy;
	noEnemyTransistion->addState(movingState);
	attackingState->addTransistion(noEnemyTransistion);

	FSMStateTransistionNoAmmo* noAmmoTransistion = new FSMStateTransistionNoAmmo;
	noAmmoTransistion->addState(reloadingState);
	attackingState->addTransistion(noAmmoTransistion);

	/*Moving State*/
	FSMStateTransistionOnSight* enemyInSightTransistion = new FSMStateTransistionOnSight;
	enemyInSightTransistion->addState(attackingState);
	movingState->addTransistion(enemyInSightTransistion);

	/*Reloading State*/
	FSMStateTransistionReloadingDone* reloadingDoneTransistion = new FSMStateTransistionReloadingDone;
	reloadingDoneTransistion->addState(attackingState);
	reloadingState->addTransistion(reloadingDoneTransistion);

	/*Healing State*/
	FSMStateTransistionHealthy* healingDoneTransistion = new FSMStateTransistionHealthy;
	healingDoneTransistion->addState(attackingState);
	healingState->addTransistion(healingDoneTransistion);

	initialState = activeState = movingState;
}

FiniteStateMachine::~FiniteStateMachine()
{
	/*Need to be filled*/
}

AllowedActions FiniteStateMachine::update(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map)
{
	auto newState = activeState->checkTransistions(myAI, otherAIs, map);
	if (newState)
	{
		activeState->onExit(myAI);
		activeState = newState;
		activeState->onEnter(myAI);
	}
	return activeState->onUpdate(myAI, otherAIs, map);
}