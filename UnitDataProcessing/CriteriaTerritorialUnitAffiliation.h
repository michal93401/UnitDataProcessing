#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitAffiliation : public CriteriaTerritorialUnit<bool>
{
private:
	TerritorialUnit* unit_;
public:
	CriteriaTerritorialUnitAffiliation(const TerritorialUnit& unit);
	bool evaluate(const TerritorialUnit& unit);
};