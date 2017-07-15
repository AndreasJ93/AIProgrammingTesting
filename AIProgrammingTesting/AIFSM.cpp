#include "AIFSM.h"

AIFSM::AIFSM(uint16_t life, float positionX, float positionY) : AIBase(life, positionX, positionY)
{
	myEntity = new Entity(life, positionX, positionY);
	targetID = -1;
	lastAction = ACTION_FIRE;
}

AllowedActions AIFSM::DecideAction(std::vector<AIBase*> allAIs, unsigned myID, Map2D* map)
{
	return stateMachine.update(this, allAIs, map);
}

AIFSM::~AIFSM()
{
}