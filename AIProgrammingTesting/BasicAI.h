#pragma once
#include "AIBase.h"
class BasicAI :
	public AIBase
{
public:
	BasicAI(uint16_t life, float position);
	~BasicAI();
	AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID);
};
