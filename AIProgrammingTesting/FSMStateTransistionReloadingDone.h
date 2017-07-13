#pragma once
#include "FSMStateBase.h"
#include "FSMStateTransistionBase.h"

class FSMStateTransistionReloadingDone : public FSMStateTransistionBase
{
public:
	FSMStateTransistionReloadingDone();
	~FSMStateTransistionReloadingDone();

	bool isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	FSMStateBase* getNextState() override;
	void onTransistion(AIBase* myAI) override;
};
