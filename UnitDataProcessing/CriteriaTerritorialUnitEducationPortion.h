#pragma once
#include "CriteriaTerritorialUnit.h"
#include "types.h"
#include <string>

class CriteriaTerritorialUnitEducationPortion : public CriteriaTerritorialUnit<double>
{
private:
	 Education education_;
public:
	CriteriaTerritorialUnitEducationPortion(Education education) : education_(education)
	{}
	double evaluate(const TerritorialUnit& unit) {
		double value = unit.getPeopleCount() == 0 ? 0 : (static_cast<double>(unit.getEducation(education_)) / static_cast<double>(unit.getPeopleCount()) * 100);
		return value;
	}
};