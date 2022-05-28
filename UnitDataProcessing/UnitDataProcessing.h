#pragma once
#include "Data.h"
#include "types.h"
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
private:
	Data* data_;
	bool loaded_;
	bool run_;
};