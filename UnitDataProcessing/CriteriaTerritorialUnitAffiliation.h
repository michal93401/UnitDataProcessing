#pragma once
#include "CriteriaTerritorialUnit.h"
#include <string>

class CriteriaTerritorialUnitAffiliation : public CriteriaTerritorialUnit<bool>
{
private:
	const TerritorialUnit* unit_;
public:
	CriteriaTerritorialUnitAffiliation(const TerritorialUnit& unit) : unit_(&unit)
	{}
	bool evaluate(const TerritorialUnit& unit) {
		if (unit_ == &unit) {
			return true;
		}
		auto parent = unit.getHigherUnit();
		while (parent != nullptr) {
			if (parent == unit_) {
				return true;
			}
			parent = parent->getHigherUnit();
		}
		return false;
	}
};