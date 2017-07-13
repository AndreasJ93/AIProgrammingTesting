#pragma once
#include "FSMStateTransistionBase.h"

class FSMStateTransistionNoEnemy : public FSMStateTransistionBase
{
public:
	FSMStateTransistionNoEnemy();
	~FSMStateTransistionNoEnemy();

	bool isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	FSMStateBase* getNextState() override;
	void onTransistion(AIBase* myAI) override;
};
