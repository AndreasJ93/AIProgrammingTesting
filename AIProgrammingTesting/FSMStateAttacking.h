#pragma once
#include "FSMStateBase.h"

class FSMStateAttacking : public FSMStateBase
{
public:
	FSMStateAttacking();
	~FSMStateAttacking();

	void onEnter(AIBase* myAI) override;
	AllowedActions onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) override;
	void onExit(AIBase* myAI) override;

private:
	uint16_t findTarget(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) const;
};
