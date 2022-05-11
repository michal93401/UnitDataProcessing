#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitEducationCount : public CriteriaTerritorialUnit<int>
{
private:
	std::string education_;
public:
	CriteriaTerritorialUnitEducationCount(std::string education);
	int evaluate(const TerritorialUnit& unit);
};