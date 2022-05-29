#pragma once
#include "FilterWithCriteria.h"
#include "TerritorialUnit.h"

class Filter_CriteriaAffi : public FilterWithCriteria<TerritorialUnit, bool> {
public:
	Filter_CriteriaAffi(Criteria<TerritorialUnit, bool>* criteria) : FilterWithCriteria(criteria) {};
protected:
	bool passFilter(bool value) override {
		return value; 
	};
};