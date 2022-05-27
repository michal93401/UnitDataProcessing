#pragma once
#include "CriteriaTerritorialUnit.h"
#include "types.h"
#include <string>

class CriteriaTerritorialUnitEducationCount : public CriteriaTerritorialUnit<int>
{
private:
	Education education_;
public:
	CriteriaTerritorialUnitEducationCount(Education education) : education_(education)
	{}
	int evaluate(const TerritorialUnit& unit) {
		return unit.;
	};
};