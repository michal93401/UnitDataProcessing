#pragma once
#include "Filter_Composite.h"
#include "TerritorialUnit.h"

class Filter_CompositeAND : Filter_Composite<TerritorialUnit> {
public:
	bool pass(const TerritorialUnit& unit);
};

inline bool Filter_CompositeAND::pass(const TerritorialUnit& unit) {
    bool passed = true;
    for (Filter<TerritorialUnit>* filter : *filters_) {
        passed = passed && filter->pass(unit);
    }
    return passed;

}