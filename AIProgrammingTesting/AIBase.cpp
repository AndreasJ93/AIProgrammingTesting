#include "AIBase.h"

AIBase::AIBase(uint16_t life, float positionX, float positionY)
{
	myEntity = new Entity(life, positionX, positionY);
	targetID = -1;
	lastAction = ACTION_FIRE;
};

AIBase::~AIBase()
{
	if (myEntity)
		delete myEntity;
};

AllowedActions AIBase::GetLastPerformedAction() const
{
	return lastAction;
};

bool AIBase::Fire() const
{
	return myEntity->Fire();
};

void AIBase::Reload() const
{
	return myEntity->Reload();
};

void AIBase::Heal(uint16_t damageToHeal) const
{
	myEntity->Heal(damageToHeal);
};

float AIBase::GetLife() const
{
	return myEntity->GetLife();
};

float AIBase::GetDamage(float distanceToTarget) const
{
	return myEntity->Damage(distanceToTarget);
};

uint16_t AIBase::GetTarget() const
{
	return targetID;
}

void AIBase::SetTarget(uint16_t target)
{
	targetID = target;
};

float AIBase::GetAccuracy(float distanceToTarget) const
{
	return myEntity->Accuracy(distanceToTarget);
};

void AIBase::TakeDamage(float damage) const
{
	myEntity->TakeDamage(uint16_t(floor(damage)));
};

float AIBase::GetPositionX() const
{
	return float(myEntity->PositionX());
};

float AIBase::GetPositionY() const
{
	return float(myEntity->PositionY());
};

void AIBase::SetPositionX(float position) const
{
	myEntity->SetPositionX(int(floor(position)));
};

void AIBase::SetPositionY(float position) const
{
	myEntity->SetPositionY(int(floor(position)));
}

Entity* AIBase::GetEntity() const
{
	return myEntity;
};