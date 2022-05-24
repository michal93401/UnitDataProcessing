#pragma once
#include "TerritorialUnit.h"
#include "sorted_sequence_table.h"

class Town : public TerritorialUnit
{
public:
	void saveThings(structures::Array<int>& man, structures::Array<int>& woman);
	void saveThings2(structures::SortedSequenceTable<std::wstring, int>& education);
private:
	structures::Array<int>* man_ = new structures::Array<int>(101);
	structures::Array<int>* woman_ = new structures::Array<int>(101);
	structures::SortedSequenceTable<std::wstring, int>* education_ = new structures::SortedSequenceTable<std::wstring, int>();
}; 

inline void Town::saveThings(structures::Array<int>& man, structures::Array<int>& woman) {
	man_ = &man;
	woman_ = &woman;
}

inline void Town::saveThings2(structures::SortedSequenceTable<std::wstring, int>& education) {
	education_ = &education;
}