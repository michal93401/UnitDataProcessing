#pragma once
#include "Filter_Composite.h"
#include "TerritorialUnit.h"

class Filter_CompositeAND : public Filter_Composite<TerritorialUnit> {
public:
	bool pass(const TerritorialUnit& unit);
};

inline bool Filter_CompositeAND::pass(const TerritorialUnit& unit) {
    /*bool passed = true;
    for (Filter<TerritorialUnit>* filter : *filters_) {
        passed = passed && filter->pass(unit);
        if (!passed) {
            return passed;
        }
    }
    return passed;*/

    bool passed = true;
    for (int i = 0; i < filters_->size(); i++)
    {
        passed = passed && filters_->at(i)->pass(unit);
        if (!passed) {
            return passed;
        }
    }
    return passed;
}