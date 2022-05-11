#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitEducationType : public CriteriaTerritorialUnit<TerritorialUnit>
{
public:
	TerritorialUnit evaluate(const TerritorialUnit& unit);