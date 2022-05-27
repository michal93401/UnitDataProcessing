#pragma once
#include "TerritorialUnit.h"

class Region : public TerritorialUnit
{
public:
	Region(std::wstring officialTitle, std::wstring code, TerritorialUnitTypes type) :
		TerritorialUnit(officialTitle, code, type) {};
private:

};