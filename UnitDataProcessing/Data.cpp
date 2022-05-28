#include "Data.h"
#include "Town.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
Data::~Data()
{
	for (auto item : *regions_) {
		delete item->accessData();
	}
	for (auto item : *districts_) {
		delete item->accessData();
	}
	for (auto item : *towns_) {
		delete item->accessData();
	}
	for (auto item : *problemTowns_) {
		delete item->accessData();
	}
	delete regions_;
	delete districts_;
	delete towns_;
	delete problemTowns_;
	delete State_;
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
	//return true;
}

bool Data::loadRegions(std::string& message_p)
{
	auto titles = new structures::ArrayList<std::wstring*>();
	auto codes = new structures::ArrayList<std::wstring*>();
	auto notes = new structures::ArrayList<std::wstring*>();
	auto units = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>;
	auto education = new structures::UnsortedSequenceTable<Education, int>;
	structures::Array<int> man(101);
	structures::Array<int> woman(101);
	if (loadTerritorialUnits("../data/kraje.csv", titles, codes, notes)) {
		/*for (size_t i = 0; i < titles->size(); i++)
		{
			regions_->add(*titles->at(i), new Region(*titles->at(i), *codes->at(i), TerritorialUnitTypes::Region));
		}
		return true;*/
		for (int i = 0; i < titles->size(); i++)
		{
			auto newRegion = new Region(*titles->at(i), *codes->at(i), TerritorialUnitTypes::Region);
			regions_->add(*titles->at(i), newRegion);
			std::wstring comparedCode = notes->at(i)->substr(5, 5);
			for (auto item : *districts_) {
				if (comparedCode.compare(item->accessData()->getCode().substr(0, 5)) == 0) {
					item->accessData()->setHigherUnit(newRegion);
					units->add(item->accessData()->getOfficialTitle(), item->accessData());
					for (int j = 1; j <= 8; j++) {
						education->find(Education(j)) += item->accessData()->getEducation(Education(j));
					}

					for (int j = 0; j < 101; j++) {
						man[j] += item->accessData()->getAge(j, Pohlavie::Man);
						woman[i] += item->accessData()->getAge(j, Pohlavie::Woman);
					}
				}
			}
			newRegion->saveEducation(*education);
			newRegion->saveAge(man, woman);
		}
		deleteContainer(titles);
		deleteContainer(codes);
		deleteContainer(notes);
		delete units;
		delete education;
		return true;
	}
	else {
		message_p = "Could not load kraje.csv";
		deleteContainer(titles);
		deleteContainer(codes);
		deleteContainer(notes);
		delete units;
		delete education;
		return false;
	}
}

bool Data::loadDistricts(std::string& message_p)
{
	auto titles = new structures::ArrayList<std::wstring*>();
	auto codes = new structures::ArrayList<std::wstring*>();
	auto units = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>;
	auto education = new structures::UnsortedSequenceTable<Education, int>;
	structures::Array<int> man(101);
	structures::Array<int> woman(101);
	if (loadTerritorialUnits("../data/okresy.csv", titles, codes, nullptr)) {
		for (int i = 0; i < titles->size(); i++)
		{
			auto newDistrict = new District(*titles->at(i), *codes->at(i), TerritorialUnitTypes::District);
			districts_->add(*titles->at(i), newDistrict);
			std::wstring comparedcode = *codes->at(i);
			for (auto item : *towns_) {
				if (comparedcode.compare(item->accessData()->getCode().substr(0, 6)) == 0) {
					item->accessData()->setHigherUnit(newDistrict);
					units->add(item->accessData()->getOfficialTitle(), item->accessData());
					for (int j = 1; j <= 8; j++) {
						//try
						//{
							education->find(Education(j)) += item->accessData()->getEducation(Education(j));
						//}
						//catch (const std::exception&)
						//{
						//	break;
						//}
					}

					for (int j = 0; j < 101; j++) {
						man[j] += item->accessData()->getAge(j, Pohlavie::Man);
						woman[i] += item->accessData()->getAge(j, Pohlavie::Woman);
					}
				}
			}
			for (auto item : *problemTowns_) {
				if (*codes->at(i) == item->accessData()->getCode().substr(0, 5)) {
					item->accessData()->setHigherUnit(newDistrict);
					units->add(item->accessData()->getOfficialTitle(), item->accessData());
					for (int j = 1; j <= 8; j++) {
						try
						{
							education->find(Education(j)) += item->accessData()->getEducation(Education(j));
						}
						catch (const std::exception&)
						{
							break;
						}
					}

					for (int j = 0; j < 101; j++) {
						man[j] += item->accessData()->getAge(j, Pohlavie::Man);
						woman[i] += item->accessData()->getAge(j, Pohlavie::Woman);
					}
				}
			}
			newDistrict->saveEducation(*education);
			newDistrict->saveAge(man, woman);
		}
		deleteContainer(titles);
		deleteContainer(codes);
		delete units;
		delete education;
		return true;
	}
	else {
		message_p = "Could not load okresy.csv";
		deleteContainer(titles);
		deleteContainer(codes);
		delete units;
		delete education;
		return false;
	}
}

bool Data::loadTowns(std::string& message_p)
{
	auto titles = new structures::ArrayList<std::wstring*>();
	auto codes = new structures::ArrayList<std::wstring*>();
	int duplicates = 2;
	if (loadTerritorialUnits("../data/obce.csv", titles, codes, nullptr)) {
		for (int i = 0; i < titles->size(); i++)
		{
			auto town = new Town(*titles->at(i), *codes->at(i), TerritorialUnitTypes::Town);
			try
			{
				towns_->insert(*titles->at(i), town);
			}
			catch (const std::exception&)
			{
				std::wstring problemTitle = *titles->at(i) + std::to_wstring(duplicates);
				problemTowns_->insert(problemTitle, town);
				duplicates++;
			}
		}
		deleteContainer(titles);
		deleteContainer(codes);
		return true;
	}
	else {
		message_p = "Could not load obce.csv";
		deleteContainer(titles);
		deleteContainer(codes);
		return false;
	}
}

bool Data::loadAgeGroups(std::string& message_p)
{
	std::wstring row;
	std::wifstream file("../data/vek.csv");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		//int counter = 0;
		std::wstring searched = { L';' };
		std::wstring code, title;
		size_t index = 0;
		int number = 0;
		structures::Array<int> man(101);
		structures::Array<int> woman(101);

		std::getline(file, row);
		while (std::getline(file, row)) {
			index = row.find(searched);
			code = row.substr(0, index);
			row.erase(0, index + searched.length());
			index = row.find(searched);
			title = row.substr(0, index);
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

			Town* town = nullptr;
			if (towns_->tryFind(title, town)) {
				if (town != nullptr && town->getCode() != code) {
					for (auto item : *problemTowns_)
					{
						//town = item->accessData()->getCode() == code ? item->accessData() : nullptr;
						town = nullptr;
						if (item->accessData()->getCode() == code) {
							town = item->accessData();
							break;
						}
					}
					town->saveAge(man, woman); // a taktiez je to hodnota nie referencia
				}
			}
			//town.saveThings(man, woman);
			//counter++;
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
		std::wstring code, title;
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
			code = row.substr(0, index);
			row.erase(0, index + searched.length());
			index = row.find(searched);
			title = row.substr(0, index);
			row.erase(0, index + searched.length());

			structures::UnsortedSequenceTable<Education, int>* education = new structures::UnsortedSequenceTable<Education, int>();
			for (int i = 0; i < 8; i++)
			{
				Education TYPE = Education(i + 1);
				index = row.find(searched);
				number = std::stoi(row.substr(0, index));
				education->insert(TYPE, number);
				row.erase(0, index + searched.length());
			}
			Town* town = nullptr;
			if (towns_->tryFind(title, town)) {
				if (town != nullptr && town->getCode() != code) {
					for (auto item : *problemTowns_)
					{
						//town = item->accessData()->getCode() == code ? item->accessData() : nullptr;
						town = nullptr;
						if (item->accessData()->getCode() == code) {
							town = item->accessData();
							break;
						}
					}
					town->saveEducation(*education);
				}
			}
			delete education;
			//Town& town = dynamic_cast<Town&>(*towns->at(counter));
			//counter++;
		}
		return true;
	}
	else {
		message_p = "Could not load vzdelanie.csv";
		return false;
	}
}

bool Data::loadTerritorialUnits(const char* fileName_p, structures::ArrayList<std::wstring*>* titles,
	structures::ArrayList<std::wstring*>* codes, structures::ArrayList<std::wstring*>* notes)
{
	std::wstring row;
	std::wifstream file(fileName_p);
	//size_t duplicates = 2;
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

		std::wstring searched = { L';' };
		std::wstring code, ofTitle, note, help;
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

			if (notes != nullptr) {
				index = row.find(searched);
				help = row.substr(0, index);
				row.erase(0, index + searched.length());
				index = row.find(searched);
				help = row.substr(0, index);
				row.erase(0, index + searched.length());
				note = row;
				notes->add(new std::wstring{ note });
			}

			titles->add(new std::wstring{ ofTitle });
			codes->add(new std::wstring{ code });
			/*try
			{
				container.insert(ofTitle, new TerritorialUnit(ofTitle, code, type));
			}
			catch (const std::exception&)
			{
				std::wstring problemTitle = ofTitle + std::to_wstring(duplicates);
				problemTowns_->insert(problemTitle, new Town(ofTitle, code, type));
				duplicates++;
			}*/
		}
		return true;
	}
	else {
		return false;
	}
}

void Data::deleteContainer(structures::ArrayList<std::wstring*>* container)
{
	for (auto item : *container) {
		delete item;
	}
	delete container;
}

void Data::print()
{
	/*for (size_t i = 0; i < towns_->size(); i++)
	{
		std::wcout << towns_->at(i).accessData()->getOfficialTitle() << std::endl;
	}*/
	_setmode(_fileno(stdout), _O_U16TEXT);
	/*for (auto item : *towns_) {
		std::wcout << item->accessData()->getOfficialTitle() << std::endl;
	}*/
	/*auto titles = new structures::ArrayList<std::wstring*>();
	auto codes = new structures::ArrayList<std::wstring*>();
	auto units = new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>;
	auto education = new structures::UnsortedSequenceTable<Education, int>;
	structures::Array<int> man(101);
	structures::Array<int> woman(101);
	loadTerritorialUnits("../data/okresy.csv", titles, codes);
	for (size_t i = 0; i < titles->size(); i++)
	{
		auto newDistrict = new District(*titles->at(i), *codes->at(i), TerritorialUnitTypes::District);
		districts_->add(*titles->at(i), newDistrict);
		std::wstring comparedcode = *codes->at(i);
		for (auto item : *towns_) {
			std::wstring comparedcode2 = item->accessData()->getCode().substr(0, 6);
			if (comparedcode.compare(comparedcode2) == 0) {
				item->accessData()->setHigherUnit(newDistrict);
				units->add(item->accessData()->getOfficialTitle(), item->accessData());
				for (int j = 1; j <= 8; j++) {
					education->find(Education(j)) += item->accessData()->getEducation(Education(j));
				}

				for (int j = 0; j < 101; j++) {
					man[j] += item->accessData()->getAge(j, Pohlavie::Man);
					woman[i] += item->accessData()->getAge(j, Pohlavie::Woman);
				}
			}
		}
		for (auto item : *problemTowns_) {
			if (*codes->at(i) == item->accessData()->getCode().substr(0, 5)) {
				item->accessData()->setHigherUnit(newDistrict);
				units->add(item->accessData()->getOfficialTitle(), item->accessData());
				for (int j = 1; j <= 8; j++) {
					education->find(Education(j)) += item->accessData()->getEducation(Education(j));
				}

				for (int j = 0; j < 101; j++) {
					man[j] += item->accessData()->getAge(j, Pohlavie::Man);
					woman[i] += item->accessData()->getAge(j, Pohlavie::Woman);
				}
			}
		}
		newDistrict->saveEducation(*education);
		newDistrict->saveAge(man, woman);
	}*/
}

