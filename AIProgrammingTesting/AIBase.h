#pragma once
#include <vector>

#include "Entity.h"
#include "Map.h"

//SHOULD THE AI HOLD IN THE ENTITY, OR THE OTHER WAY AROUND?

enum AllowedActions
{
	ACTION_FIRE,
	ACTION_RELOAD,
	ACTION_HEAL,
	ACTION_MOVE
};

class AIBase
{
public:
	AIBase(uint16_t life, float positionX, float positionY);
	virtual ~AIBase();
	virtual AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID, Map2D* map) = 0;
	AllowedActions GetLastPerformedAction() const;
	bool Fire() const;
	void Reload() const;
	void Heal(uint16_t damageToHeal) const;
	float GetLife() const;
	float GetDamage(float distanceToTarget) const;
	uint16_t GetTarget() const;
	void SetTarget(uint16_t target);
	float GetAccuracy(float distanceToTarget) const;
	void TakeDamage(float damage) const;
	float GetPositionX() const;
	float GetPositionY() const;
	void SetPositionX(float position) const;
	void SetPositionY(float position) const;
	Entity* GetEntity() const;
protected:
	Entity* myEntity;
	AllowedActions lastAction;
	uint16_t targetID;
};
