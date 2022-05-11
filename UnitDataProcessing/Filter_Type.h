#pragma once
#include "FilterWithCriteria.h"

template<typename ObjectType, typename ValueType>
class Filter_Type : public FilterWithCriteria<ObjectType, ValueType> {
public:
	Filter_Type(Criteria<ObjectType, ValueType>* criteria, ValueType value);
protected:
	virtual bool passFilter(ValueType value) = 0;
private:
	ValueType value_;
};