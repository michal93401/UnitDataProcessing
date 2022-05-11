#pragma once
#include "FilterWithCriteria.h"

template<typename ObjectType, typename ValueType>
class Filter_Range : public FilterWithCriteria<ObjectType, ValueType> {
public:
	Filter_Range(Criteria<ObjectType, ValueType>* criteria, ValueType minValue, ValueType maxValue);
protected:
	virtual bool passFilter(ValueType value) = 0;
private:
	ValueType minValue_;
	ValueType maxValue_;
};