#include "AIFSM.h"

AIFSM::AIFSM(uint16_t life, float positionX, float positionY) : AIBase(life, positionX, positionY)
{
}

AllowedActions AIFSM::DecideAction(std::vector<AIBase*> allAIs, unsigned myID, Map2D* map)
{
}

AIFSM::~AIFSM()
{
}