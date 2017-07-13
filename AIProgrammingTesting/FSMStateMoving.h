#pragma once
#include "FSMStateBase.h"

class FSMStateMoving : public FSMStateBase
{
public:
	FSMStateMoving();
	~FSMStateMoving();

	void onEnter(AIBase* myAI) override;
	AllowedActions onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	void onExit(AIBase* myAI) override;
};
