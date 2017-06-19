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
	AIBase(uint16_t life) { myEntity = new Entity(life); targetID = -1; lastAction = ACTION_FIRE; };
	virtual ~AIBase() { delete myEntity; };
	virtual AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID) = 0;
	AllowedActions GetLastPerformedAction() { return lastAction; };
	bool Fire() { return myEntity->Fire(); };
	void Reload() { return myEntity->Reload(); };
	void Heal(uint16_t damageToHeal) { myEntity->Heal(damageToHeal); };
	uint16_t GetLife() { return myEntity->GetLife(); };
	uint16_t GetDamage() { return myEntity->EquipedWeapon()->Damage(); };
	uint16_t GetTarget() { return targetID; };
	float GetAccuracy() { return myEntity->Accuracy(); };
	void TakeDamage(uint16_t damage) { myEntity->TakeDamage(damage); };
protected:
	Entity* myEntity;
	AllowedActions lastAction;
	uint16_t targetID;
private:
};