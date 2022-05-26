#include "TerritorialUnit.h"

TerritorialUnit::TerritorialUnit(std::wstring officialTitle, std::wstring code, TerritorialUnitTypes type) :
	officialTitle_(officialTitle), code_(code), type_(type)
{
}

TerritorialUnit::~TerritorialUnit()
{
	delete Units_;
	delete higherUnit_;
}

const std::wstring& TerritorialUnit::getOfficialTitle() const
{
	return officialTitle_;
}

const std::wstring& TerritorialUnit::getCode() const
{
	return code_;
}

TerritorialUnitTypes TerritorialUnit::getType() const
{
	return TerritorialUnitTypes();
}

void TerritorialUnit::setHigherUnit(TerritorialUnit* newHigherUnit)
{
	higherUnit_ = newHigherUnit;
}

TerritorialUnit* TerritorialUnit::getHigherUnit() const
{
	return higherUnit_;
}

structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* TerritorialUnit::getUnits() const
{
	return Units_;
}

void TerritorialUnit::setUnits(structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* newUnits)
{
	Units_ = newUnits;
}

std::wstring TerritorialUnit::toString()
{
	return officialTitle_;
}
