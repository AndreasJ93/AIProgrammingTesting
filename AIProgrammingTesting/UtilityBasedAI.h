#pragma once
#include "AIBase.h"
class UtilityBasedAI :
	public AIBase
{
public:
	UtilityBasedAI(uint16_t life, float positionX, float positionY);
	~UtilityBasedAI();
	AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID);
};
