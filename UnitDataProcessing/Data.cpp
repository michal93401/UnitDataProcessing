#include "Data.h"
#include "Town.h"

Data::~Data()
{
	delete regions_;
	delete districts_;
	delete towns_;
}

bool Data::loadData(std::string& message_p)
{
	if (loadTowns(message_p) &&
		loadAgeGroups(message_p) &&
		loadEducation(message_p) && 
		loadDistricts(message_p) && 
		loadRegions(message_p)) {
		return true;
	}
	return false;
}

bool Data::loadRegions(std::string& message_p)
{
	if (loadTerritorialUnits("../data/kraje.csv")) {
		return true;
	}
	else {
		message_p = "Could not load kraje.csv";
		return false;
	}
}

bool Data::loadDistricts(std::string& message_p)
{
	if (loadTerritorialUnits("../data/okresy.csv")) {
		return true;
	}
	else {
		message_p = "Could not load okresy.csv";
		return false;
	}
}

bool Data::loadTowns(std::string& message_p)
{
	if (loadTerritorialUnits("../data/obce.csv")) {
		return true;
	}
	else {
		message_p = "Could not load obce.csv";
		return false;
	}
}

bool Data::loadAgeGroups(std::string& message_p)
{
	std::wstring row;
	std::wifstream file("../data/vek.csv");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		int counter = 0;
		std::wstring searched = { L';' };
		std::wstring help;
		size_t index = 0;
		int number = 0;
		structures::Array<int> man(101);
		structures::Array<int> woman(101);

		std::getline(file, row);
		while (std::getline(file, row)) {
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());
			for (int i = 0; i < 101; i++) {
				index = row.find(searched);
				number = std::stoi(row.substr(0, index));
				man[i] = number;
				row.erase(0, index + searched.length());
			}
			for (int i = 0; i < 101; i++) {
				index = row.find(searched);
				number = std::stoi(row.substr(0, index));
				woman[i] = number;
				row.erase(0, index + searched.length());
			}
			//Town& town = dynamic_cast<Town&>(*towns->at(counter));
			//town.saveThings(man, woman);
			counter++;
		}
		return true;
	}
	else {
		message_p = "Could not load vek.csv";
		return false;
	}
}

bool Data::loadEducation(std::string& message_p)
{
	std::wstring row;
	std::wifstream file("../data/vek.csv");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		int counter = 0;
		std::wstring searched = { L';' };
		std::wstring help;
		size_t index = 0;
		int number = 0;

		std::getline(file, row);
		/*index = row.find(searched);
		help = row.substr(0, index);
		row.erase(0, index + searched.length());
		index = row.find(searched);
		help = row.substr(0, index);
		row.erase(0, index + searched.length());*/
		while (std::getline(file, row)) {
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());


			//Town& town = dynamic_cast<Town&>(*towns->at(counter));
			counter++;
		}
		return true;
	}
	else {
		message_p = "Could not load vzdelanie.csv";
		return false;
	}
}

bool Data::loadTerritorialUnits(const char* fileName_p)
{
	std::wstring row;
	std::wifstream file(fileName_p);
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		std::wstring searched = { L';' };
		std::wstring code, ofTitle, help;
		size_t index = 0;
		std::getline(file, row);
		while (std::getline(file, row)) {
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			code = row.substr(0, index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			ofTitle = row.substr(0, index);
			row.erase(0, index + searched.length());
			//regions_->insert(ofTitle, new TerritorialUnit(ofTitle, code, TerritorialUnitTypes::Region));
		}
		return true;
	}
	else {
		return false;
	}
}

