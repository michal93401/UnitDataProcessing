#pragma once
#include "Filter_Type.h"

template<typename ObjectType, typename ValueType>
class Filter_TypeEqualLess : public Filter_Type<ObjectType, ValueType> {
public:
	Filter_TypeEqualLess(Criteria<ObjectType, ValueType>* criteria, ValueType value);
protected:
	bool passFilter(ValueType value) override;
};

template<typename ObjectType, typename ValueType>
inline Filter_TypeEqualLess<ObjectType, ValueType>::Filter_TypeEqualLess(Criteria<ObjectType, ValueType>* criteria, ValueType value) :
	Filter_Type<ObjectType, ValueType>(criteria, value)
{
}

template<typename ObjectType, typename ValueType>
inline bool Filter_TypeEqualLess<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value <= Filter_Type<ObjectType, ValueType>::getValue();
}