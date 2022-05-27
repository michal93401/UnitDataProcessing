#pragma once
#include "TerritorialUnit.h"
#include "ParametricCriteria.h"

template<typename ResultType, typename ParameterType>
class ParametricCriteriaTerritorialUnit : public ParametricCriteria<TerritorialUnit, ResultType, ParameterType>
{
public:
	virtual ResultType evaluate(const TerritorialUnit& unit, const ParameterType& parameter) = 0;
};