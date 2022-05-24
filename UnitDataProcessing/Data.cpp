#include "Data.h"
#include "Town.h"

Data::~Data()
{
	delete regions;
	delete districts;
	delete towns;
}

void Data::loadData()
{
	loadRegions();
	loadDistricts();
	loadTowns();
	loadAgeGroups();
	loadEducation();
}

void Data::loadRegions()
{
	std::wstring row;
	std::wifstream file("../data/kraje.csv");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		std::wstring searched = { L';'};
		std::wstring code;
		std::wstring ofTitle;
		std::wstring type;
		std::wstring help;
		size_t index = 0;
		std::getline(file, row);
		while (std::getline(file, row)) {
			index = row.find(searched);
			help = row.substr(0 , index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			code = row.substr(0, index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			ofTitle = row.substr(0, index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			type = row.substr(0, index);
			row.erase(0, index + searched.length());

			regions->insert(ofTitle, new TerritorialUnit(ofTitle, code, type));
		}
	}
	else {
		throw std::runtime_error("Could not open a file");
	}
}

void Data::loadDistricts()
{
	std::wstring row;
	std::wifstream file("../data/okresy.csv");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		std::wstring searched = { L';' };
		std::wstring code;
		std::wstring ofTitle;
		std::wstring type;
		std::wstring help;
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

			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			type = row.substr(0, index);
			row.erase(0, index + searched.length());

			districts->insert(ofTitle, new TerritorialUnit(ofTitle, code, type));
		}
	}
	else {
		throw std::runtime_error("Could not open a file");
	}
}

void Data::loadTowns()
{
	std::wstring row;
	std::wifstream file("../data/obce.csv");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		std::wstring searched = { L';' };
		std::wstring code;
		std::wstring ofTitle;
		std::wstring type;
		std::wstring help;
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

			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());
			index = row.find(searched);
			help = row.substr(0, index);
			row.erase(0, index + searched.length());

			index = row.find(searched);
			type = row.substr(0, index);
			row.erase(0, index + searched.length());

			towns->insert(ofTitle, new TerritorialUnit(ofTitle, code, type));
		}
	}
	else {
		throw std::runtime_error("Could not open a file");
	}
}

void Data::loadAgeGroups()
{
	std::wstring row;
	std::wifstream file("../data/vek.csv");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		int counter = 0;
		std::wstring searched = { L';' };
		size_t index = 0;
		int number = 0;
		std::getline(file, row);
		while (std::getline(file, row)) {
			structures::Array<int> man(101);
			structures::Array<int> woman(101);
			for (int i = 0; i < 101; i++) {
				index = row.find(searched);
				number = std::stoi(row.substr(0, index));
				man[i] = number;
				row.erase(0, index + searched.length());
			}
			Town& town = dynamic_cast<Town&>(towns->at(counter)->accessData());
			town.saveThings(man, woman);
		}
	}
	else {
		throw std::runtime_error("Could not open a file");
	}
}

void Data::loadEducation()
{
}
