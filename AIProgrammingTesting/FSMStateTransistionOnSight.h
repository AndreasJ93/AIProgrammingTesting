#pragma once
#include "FSMStateTransistionBase.h"

class FSMStateTransistionOnSight : public FSMStateTransistionBase
{
public:
	FSMStateTransistionOnSight();
	~FSMStateTransistionOnSight();
	bool isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	FSMStateBase* getNextState() override;
	void onTransistion(AIBase* myAI) override;
};
