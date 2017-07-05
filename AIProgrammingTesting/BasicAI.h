#pragma once
#include "AIBase.h"
class BasicAI :
	public AIBase
{
public:
	BasicAI(uint16_t life, float positionX, float positionY);
	~BasicAI();
	AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID);
};
