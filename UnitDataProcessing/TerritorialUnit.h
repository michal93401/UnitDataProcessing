#pragma once
#include <string>
#include "types.h"
#include "sorted_sequence_table.h"
#include "unsorted_sequence_table.h"

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
	int getPeopleCount() const;
	void saveAge(structures::Array<int>& man, structures::Array<int>& woman);
	void saveEducation(structures::UnsortedSequenceTable<Education, int>& education);
	int getAge(int age, Pohlavie pohlavie) const;
	int getEducation(Education type) const;
	std::wstring toString();
protected:
	std::wstring officialTitle_;
	std::wstring code_;
	TerritorialUnitTypes type_;
	TerritorialUnit* higherUnit_ = nullptr;
	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* Units_ = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>();
	structures::Array<int>* man_ = new structures::Array<int>(101);
	structures::Array<int>* woman_ = new structures::Array<int>(101);
	structures::UnsortedSequenceTable<Education, int>* education_ = new structures::UnsortedSequenceTable<Education, int>();
};