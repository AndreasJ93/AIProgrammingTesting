#pragma once
#include "FSMStateBase.h"

class FSMStateHealing : public FSMStateBase
{
public:
	FSMStateHealing();
	~FSMStateHealing();

	void onEnter(AIBase* myAI) override;
	AllowedActions onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	void onExit(AIBase* myAI) override;
};
