#pragma once
#include "CriteriaTerritorialUnit.h"
#include "types.h"
#include <string>

class CriteriaTerritorialUnitEducationPortion : public CriteriaTerritorialUnit<double>
{
private:
	 Education education_;
public:
	CriteriaTerritorialUnitEducationPortion(Education education);
	double evaluate(const TerritorialUnit& unit);
};