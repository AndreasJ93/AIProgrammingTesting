#pragma once
#include "FSMStateTransistionBase.h"

class FSMStateTransistionNoAmmo : public FSMStateTransistionBase
{
public:
	FSMStateTransistionNoAmmo();
	~FSMStateTransistionNoAmmo();

	bool isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	FSMStateBase* getNextState() override;
	void onTransistion(AIBase* myAI) override;
};
