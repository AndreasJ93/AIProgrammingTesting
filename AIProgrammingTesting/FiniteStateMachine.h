#pragma once
#include "FSMStateBase.h"
#include <vector>

class FiniteStateMachine
{
public:
	FiniteStateMachine();
	~FiniteStateMachine();
	AllowedActions update(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map);

private:
	std::list<FSMStateBase*> states;
	FSMStateBase* initialState;
	FSMStateBase* activeState;
};
