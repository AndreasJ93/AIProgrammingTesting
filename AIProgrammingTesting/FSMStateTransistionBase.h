#pragma once
#include <list>
#include <vector>

class FSMStateBase;
class AIBase;
class Map2D;

class FSMStateTransistionBase
{
public:
	FSMStateTransistionBase();
	virtual ~FSMStateTransistionBase();
	virtual bool isValid(AIBase* myAI, std::vector<AIBase*> otherAIs, Map2D* map) = 0;
	virtual FSMStateBase* getNextState() = 0;
	virtual void onTransistion(AIBase* myAI) = 0;
	void addState(FSMStateBase* newState);

protected:
	std::list<FSMStateBase*> states;
};
