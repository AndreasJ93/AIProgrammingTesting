#pragma once
#include "AIBase.h"

class AIFSM : public AIBase/*Side 48 in Game AI Pro*/
{
public:
	AIFSM(uint16_t life, float positionX, float positionY);

	AllowedActions DecideAction(std::vector<AIBase*> allAIs, unsigned myID, Map2D* map) override;
	~AIFSM() override;

private:
	std::vector<int> temp;
};
