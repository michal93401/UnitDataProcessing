#pragma once
#include "TerritorialUnit.h"
#include "unsorted_sequence_table.h"

class Town : public TerritorialUnit
{
public:
	Town(std::wstring officialTitle, std::wstring code, TerritorialUnitTypes type) :
		TerritorialUnit(officialTitle, code, type) {};
	void saveThings(structures::Array<int>& man, structures::Array<int>& woman);
	void saveThings2(structures::UnsortedSequenceTable<std::wstring, int>& education);
private:
	structures::Array<int>* man_ = new structures::Array<int>(101);
	structures::Array<int>* woman_ = new structures::Array<int>(101);
	structures::UnsortedSequenceTable<std::wstring, int>* education_ = new structures::UnsortedSequenceTable<std::wstring, int>();
}; 

inline void Town::saveThings(structures::Array<int>& man, structures::Array<int>& woman) {
	man_ = &man;
	woman_ = &woman;
}

inline void Town::saveThings2(structures::UnsortedSequenceTable<std::wstring, int>& education) {
	education_ = &education;
}