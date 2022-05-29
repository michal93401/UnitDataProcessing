#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitType : public CriteriaTerritorialUnit<TerritorialUnitTypes>
{
public:
	TerritorialUnitTypes evaluate(const TerritorialUnit& unit) override {
		return unit.getType();
	}
};