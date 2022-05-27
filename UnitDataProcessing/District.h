#pragma once
#include "TerritorialUnit.h"

class District : public TerritorialUnit
{
public:
	District(std::wstring officialTitle, std::wstring code, TerritorialUnitTypes type) :
		TerritorialUnit(officialTitle, code, type) {};
private:

};