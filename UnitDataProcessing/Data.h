#pragma once
#include "sorted_sequence_table.h"
#include "TerritorialUnit.h"
#include <string>
#include <fstream>
#include <codecvt>

class Data {
public:
	//Data();
	~Data();
	void loadData();
private:
	void loadRegions();
	void loadDistricts();
	void loadTowns();
	void loadAgeGroups();
	void loadEducation();
private:
	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* regions = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>();
	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* districts = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>();
	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* towns = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>();
};