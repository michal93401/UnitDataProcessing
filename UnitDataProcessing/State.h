#pragma once
#include "TerritorialUnit.h"

class State : public TerritorialUnit
{
public:
	State();
};

inline State::State() :
	TerritorialUnit({ L"Slovakia"}, {L"SK"}, TerritorialUnitTypes::State) {
}