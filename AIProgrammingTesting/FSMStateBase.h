#pragma once

#include <list>
#include <vector>
#include "AIBase.h"

class FSMStateTransistionBase;

class FSMStateBase
{
public:
	FSMStateBase();
	virtual ~FSMStateBase();
	virtual void onEnter(AIBase* myAI) = 0;
	virtual AllowedActions onUpdate(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) = 0;
	virtual void onExit(AIBase* myAI) = 0;
	FSMStateBase* checkTransistions(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map);
	void	addTransistion(FSMStateTransistionBase* transistionToAdd);

protected:
	std::list<FSMStateTransistionBase*> transistions;
};