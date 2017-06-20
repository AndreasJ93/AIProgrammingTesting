#pragma once
#include <vector>

#include "Entity.h"

//SHOULD THE AI HOLD IN THE ENTITY, OR THE OTHER WAY AROUND?

enum AllowedActions {
	ACTION_FIRE,
	ACTION_RELOAD,
	ACTION_HEAL
};

class AIBase
{
public:
	AIBase(uint16_t life, float position);
	virtual ~AIBase();
	virtual AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID) = 0;
	AllowedActions GetLastPerformedAction();
	bool Fire();
	void Reload();
	void Heal(uint16_t damageToHeal);
	float GetLife();
	float GetDamage(float distanceToTarget);
	uint16_t GetTarget();
	float GetAccuracy(float distanceToTarget);
	void TakeDamage(uint16_t damage);
	float GetPosition();
protected:
	Entity* myEntity;
	AllowedActions lastAction;
	uint16_t targetID;
private:
};