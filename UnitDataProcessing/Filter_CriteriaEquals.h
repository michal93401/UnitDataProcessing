#pragma once
#include "FilterWithCriteria.h"

template<typename ObjectType, typename ValueType>
class Filter_CriteriaEquals : public FilterWithCriteria<ObjectType, ValueType> {
public:
	Filter_CriteriaEquals(Criteria<ObjectType, ValueType>* criteria);
protected:
	bool passFilter(ValueType value) override;
};

template<typename ObjectType, typename ValueType>
inline Filter_CriteriaEquals<ObjectType, ValueType>::Filter_CriteriaEquals(Criteria<ObjectType, ValueType>* criteria) :
	FilterWithCriteria<ObjectType, ValueType>(criteria)
{
}

template<typename ObjectType, typename ValueType>
inline bool Filter_CriteriaEquals<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value == Filter_Type<ObjectType, ValueType>::getValue();
}