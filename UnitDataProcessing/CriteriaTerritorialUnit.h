#pragma once
#include "Criteria.h"
#include "TerritorialUnit.h"

template<typename ResultType>
class CriteriaTerritorialUnit : public Criteria<TerritorialUnit, ResultType>
{
public:
	virtual ResultType evaluate(const TerritorialUnit& unit) = 0;
};