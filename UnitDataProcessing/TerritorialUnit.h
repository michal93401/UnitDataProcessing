#pragma once
#include <string>
#include "types.h"
#include "sorted_sequence_table.h"

class TerritorialUnit {
public:
	TerritorialUnit(std::wstring officialTitle, std::wstring code, TerritorialUnitTypes type);
	~TerritorialUnit();
	const std::wstring& getOfficialTitle() const;
	const std::wstring& getCode() const;
	TerritorialUnitTypes getType() const;
	void setHigherUnit(TerritorialUnit* newHigherUnit);
	TerritorialUnit* getHigherUnit() const;
	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* getUnits() const;
	void setUnits(structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* newUnits);
	std::wstring toString();
protected:
	std::wstring officialTitle_;
	std::wstring code_;
	TerritorialUnitTypes type_;
	TerritorialUnit* higherUnit_ = nullptr;
	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* Units_ = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>();
};