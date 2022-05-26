#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitName : public CriteriaTerritorialUnit<std::wstring>
{
public:
	std::wstring evaluate(const TerritorialUnit& unit) override {
		return unit.getOfficialTitle();
	}
};