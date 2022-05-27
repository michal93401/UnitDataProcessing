#pragma once
#include "FilterWithCriteria.h"

template<typename ObjectType, typename ValueType>
class Filter_Type : public FilterWithCriteria<ObjectType, ValueType> {
public:
	Filter_Type(Criteria<ObjectType, ValueType>* criteria, ValueType value);
protected:
	virtual bool passFilter(ValueType value) = 0;
	ValueType getValue() const;
private:
	ValueType value_;
};

template<typename ObjectType, typename ValueType>
inline Filter_Type<ObjectType, ValueType>::Filter_Type(Criteria<ObjectType, ValueType>* criteria, ValueType value) :
	FilterWithCriteria<ObjectType, ValueType>(criteria), value_(value)
{
}

template<typename ObjectType, typename ValueType>
inline ValueType Filter_Type<ObjectType, ValueType>::getValue() const
{
	return value_;
}
