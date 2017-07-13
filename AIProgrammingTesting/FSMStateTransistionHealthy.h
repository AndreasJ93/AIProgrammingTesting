#pragma once
#include "FSMStateTransistionBase.h"

class FSMStateTransistionHealthy : public FSMStateTransistionBase
{
public:
	FSMStateTransistionHealthy();
	~FSMStateTransistionHealthy() override;

	bool isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	FSMStateBase* getNextState() override;
	void onTransistion(AIBase* myAI) override;
};
