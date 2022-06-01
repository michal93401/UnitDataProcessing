#pragma once
#include "Data.h"
#include "types.h"
#include "CriteriaTerritorialUnitEducationCount.h"
#include "CriteriaTerritorialUnitEducationPortion.h"
#include "CriteriaTerritorialUnitAffiliation.h"
#include "CriteriaTerritorialUnitName.h"
#include "CriteriaTerritorialUnitType.h"
#include "Filter_CriteriaAffi.h"
#include "Filter_TypeEqualLess.h"
#include "Filter_TypeEqualMore.h"
#include "Filter_TypeEquals.h"
#include "Filter_TypeLess.h"
#include "Filter_TypeMore.h"
#include "Filter_TypeEquals.h"
#include "Filter_CompositeAND.h"
#include "Filter_Range.h"
#include "quick_sort.h"
#include "shell_sort.h"
#include "sorter.h"
#include <codecvt>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <io.h>

std::wstring educationToString(Education type);
std::wstring genderToString(Pohlavie type);
std::wstring unitTypeToString(TerritorialUnitTypes type);

class UnitDataProcessing {
public:
	UnitDataProcessing();
	~UnitDataProcessing();
	void load();
	void start();
private:
	std::wstring getUserRequest();
	int userRequest();
	void searchByName();
	void searchMakingFilter();
	void searchUsingMadeFilter();
	int convertUserInputToNumber(int max);
	Town* findCityByName(std::wstring name);
	void writeUnitInfo(TerritorialUnit* unit, bool percentualy);
private:
	Data* data_;
	bool loaded_;
	bool run_;
private:
	structures::ArrayList<TerritorialUnit*>* filterOnContainer(Filter<TerritorialUnit>& filter, structures::ArrayList<TerritorialUnit*>* units);

	template<typename T, typename ValueType>
	void userSort(structures::ArrayList<TerritorialUnit*>* units, CriteriaTerritorialUnit<ValueType>* criteria, bool vzostupne);
};