#pragma once
#include "ParametricCriteriaTerritorialUnit.h"
#include "types.h"

class ParametricCriteriaTerritorialUnitEducationCount : public ParametricCriteriaTerritorialUnit<int, Education>
{
public:
	int evaluate(const TerritorialUnit& unit, const Education& parameter) = 0;
};