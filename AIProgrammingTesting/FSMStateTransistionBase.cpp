#include "FSMStateTransistionBase.h"

FSMStateTransistionBase::FSMStateTransistionBase()
{
}

FSMStateTransistionBase::~FSMStateTransistionBase()
{
}

void FSMStateTransistionBase::addState(FSMStateBase* newState)
{
	states.push_back(newState);
}