#pragma once
#include "TerritorialUnit.h"
#include "unsorted_sequence_table.h"

class Town : public TerritorialUnit
{
public:
	Town(std::wstring officialTitle, std::wstring code, TerritorialUnitTypes type) :
		TerritorialUnit(officialTitle, code, type) {};
}; 
