#pragma once
#include "sorted_sequence_table.h"
#include "unsorted_sequence_table.h"
#include "TerritorialUnit.h"
#include "State.h"
#include "Region.h"
#include "District.h"
#include "Town.h"
#include "Filter_Type.h"
#include <string>
#include <fstream>
#include <codecvt>


class Data {
public:
	Data() = default;
	~Data();
	bool loadData(std::string& message_p);
	void print();
	TerritorialUnit* findUnitByName(TerritorialUnitTypes type, std::wstring& name);
	Town* findCityByName(std::wstring& name);
	structures::ArrayList<Town*>* findCityDuplicates(std::wstring& name);

	//template<typename ObjectType, typename ValueType>
	//structures::ArrayList<TerritorialUnit*>* getFilteredUnits(Filter_Type<ObjectType, ValueType>& filter, TerritorialUnitTypes type);
	structures::ArrayList<TerritorialUnit*>* getFilteredUnits(Filter<TerritorialUnit>& filter, TerritorialUnitTypes type);

private:
	bool loadRegions(std::string& message_p);
	bool loadDistricts(std::string& message_p);
	bool loadTowns(std::string& message_p);
	bool loadAgeGroups(std::string& message_p);
	bool loadEducation(std::string& message_p);
	bool loadTerritorialUnits(const char* fileName_p, structures::ArrayList<std::wstring*>* titles, structures::ArrayList<std::wstring*>* codes,
		structures::ArrayList<std::wstring*>* notes);
	void setUpState();
	void deleteContainer(structures::ArrayList<std::wstring*>* container);
private:
	TerritorialUnit* State_ = new State();
	structures::SortedSequenceTable<std::wstring, Region*>* regions_ = new structures::SortedSequenceTable<std::wstring, Region*>();
	structures::SortedSequenceTable<std::wstring, District*>* districts_ = new structures::SortedSequenceTable<std::wstring, District*>();
	structures::SortedSequenceTable<std::wstring, Town*>* towns_ = new structures::SortedSequenceTable<std::wstring, Town*>();
	structures::UnsortedSequenceTable<std::wstring, Town*>* problemTowns_ = new structures::UnsortedSequenceTable<std::wstring, Town*>();
};