#include "TerritorialUnit.h"

TerritorialUnit::TerritorialUnit(std::wstring officialTitle, std::wstring code, TerritorialUnitTypes type) :
	officialTitle_(officialTitle), code_(code), type_(type)
{
}

TerritorialUnit::~TerritorialUnit()
{
	/*for (auto item : *Units_) {
		delete item->accessData();
	}*/
	for (auto item : *education_) {
		delete item;
	}
	higherUnit_ = nullptr;
	delete Units_;
	delete man_;
	delete woman_;
	delete education_;
}

const std::wstring& TerritorialUnit::getOfficialTitle() const
{
	return officialTitle_;
}

const std::wstring& TerritorialUnit::getCode() const
{
	return code_;
}

TerritorialUnitTypes TerritorialUnit::getType() const
{
	return TerritorialUnitTypes();
}

void TerritorialUnit::setHigherUnit(TerritorialUnit* newHigherUnit)
{
	higherUnit_ = newHigherUnit;
}

TerritorialUnit* TerritorialUnit::getHigherUnit() const
{
	return higherUnit_;
}

structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* TerritorialUnit::getUnits() const
{
	return Units_;
}

void TerritorialUnit::setUnits(structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* newUnits)
{
	Units_ = newUnits;
}

int TerritorialUnit::getPeopleCount() const
{
	size_t people = 0;
	for (size_t i = 0; i < man_->size(); i++)
	{
		people += man_->at(i);
	}
	for (size_t i = 0; i < woman_->size(); i++)
	{
		people += woman_->at(i);
	}
	return people;
}

void TerritorialUnit::saveAge(structures::Array<int>& man, structures::Array<int>& woman)
{
	man_->assign(man);
	woman_->assign(woman);
}

void TerritorialUnit::saveEducation(structures::UnsortedSequenceTable<Education, int>& education)
{
	education_->assign(education);
}

int TerritorialUnit::getAge(int age, Pohlavie pohlavie) const
{
	switch (pohlavie)
	{
	case Pohlavie::Man:
		return man_->at(age);
	case Pohlavie::Woman:
		return woman_->at(age);
	default:
		return -1;
	}
}

int TerritorialUnit::getEducation(Education type) const
{
	return education_->find(type);
}

std::wstring TerritorialUnit::toString()
{
	return officialTitle_;
}
