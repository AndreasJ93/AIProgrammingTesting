#pragma once
#include "AIBase.h"

/*

The "UtilityBasedAI" below is based on the AI presented in "Behavioural Mathematics for Game AI"

*/

class UtilityBasedAI :
	public AIBase
{
public:
	UtilityBasedAI(uint16_t life, float positionX, float positionY);
	~UtilityBasedAI();
	AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned int myID);
};
