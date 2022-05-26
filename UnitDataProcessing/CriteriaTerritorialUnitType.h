#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitEducationType : public CriteriaTerritorialUnit<TerritorialUnitTypes>
{
public:
	TerritorialUnitTypes evaluate(const TerritorialUnit& unit) override {
		return unit.getType();
	}
};