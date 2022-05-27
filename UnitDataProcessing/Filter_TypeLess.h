#pragma once
#include "Filter_Type.h"

template<typename ObjectType, typename ValueType>
class Filter_TypeLess : public Filter_Type<ObjectType, ValueType> {
public:
	Filter_TypeLess(Criteria<ObjectType, ValueType>* criteria, ValueType value);
protected:
	bool passFilter(ValueType value) override;
};

template<typename ObjectType, typename ValueType>
inline Filter_TypeLess<ObjectType, ValueType>::Filter_TypeLess(Criteria<ObjectType, ValueType>* criteria, ValueType value) :
	Filter_Type<ObjectType, ValueType>(criteria, value)
{
}

template<typename ObjectType, typename ValueType>
inline bool Filter_TypeLess<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value < getValue();
}