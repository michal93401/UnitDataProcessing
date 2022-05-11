#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitEducationPortion : public CriteriaTerritorialUnit<double>
{
private:
	std::string education_;
public:
	CriteriaTerritorialUnitEducationPortion(std::string education);
	double evaluate(const TerritorialUnit& unit);
};