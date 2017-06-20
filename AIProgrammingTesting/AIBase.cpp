#include "AIBase.h"

AIBase::AIBase(uint16_t life, float position)
{
	myEntity = new Entity(life, position);
	targetID = -1;
	lastAction = ACTION_FIRE;
};
AIBase::~AIBase()
{
	if (myEntity)
		delete myEntity;
};

AllowedActions AIBase::GetLastPerformedAction() 
{ 
	return lastAction; 
};
bool AIBase::Fire() 
{ 
	return myEntity->Fire(); 
};
void AIBase::Reload() 
{ 
	return myEntity->Reload(); 
};
void AIBase::Heal(uint16_t damageToHeal) 
{ 
	myEntity->Heal(damageToHeal); 
};
float AIBase::GetLife() 
{ 
	return myEntity->GetLife(); 
};
float AIBase::GetDamage(float distanceToTarget) 
{ 
	return myEntity->Damage(distanceToTarget); 
};
uint16_t AIBase::GetTarget() 
{ 
	return targetID; 
};
float AIBase::GetAccuracy(float distanceToTarget) 
{ 
	return myEntity->Accuracy(distanceToTarget); 
};
void AIBase::TakeDamage(uint16_t damage) 
{ 
	myEntity->TakeDamage(damage); 
};
float AIBase::GetPosition() 
{ 
	return myEntity->Position(); 
};
