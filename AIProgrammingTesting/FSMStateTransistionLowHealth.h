#pragma once
#include "FSMStateTransistionBase.h"

class FSMStateTransistionLowHealth : public FSMStateTransistionBase
{
public:
	FSMStateTransistionLowHealth();
	~FSMStateTransistionLowHealth();
	bool isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	FSMStateBase* getNextState() override;
	void onTransistion(AIBase* myAI) override;
};
