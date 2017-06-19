#pragma once
#include <vector>

#include "Entity.h"

enum AllowedActions {
	ACTION_FIRE,
	ACTION_RELOAD,
	ACTION_HEAL
};

class AIBase
{
public:
	AIBase(uint16_t life, float position) { myEntity = new Entity(life, position); targetID = -1; lastAction = ACTION_FIRE; };
	virtual ~AIBase() { delete myEntity; };
	virtual AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID) = 0;
	AllowedActions GetLastPerformedAction() { return lastAction; };
	bool Fire() { return myEntity->Fire(); };
	void Reload() { return myEntity->Reload(); };
	void Heal(uint16_t damageToHeal) { myEntity->Heal(damageToHeal); };
	float GetLife() { return myEntity->GetLife(); };
	float GetDamage(float distanceToTarget) { return myEntity->Damage(distanceToTarget); };
	uint16_t GetTarget() { return targetID; };
	float GetAccuracy(float distanceToTarget) { return myEntity->Accuracy(distanceToTarget); };
	void TakeDamage(uint16_t damage) { myEntity->TakeDamage(damage); };
	float GetPosition() { return myEntity->Position(); };
protected:
	Entity* myEntity;
	AllowedActions lastAction;
	uint16_t targetID;
private:
};