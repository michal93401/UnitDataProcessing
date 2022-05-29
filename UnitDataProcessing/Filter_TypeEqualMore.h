#pragma once
#include "Filter_Type.h"

template<typename ObjectType, typename ValueType>
class Filter_TypeEqualMore : public Filter_Type<ObjectType, ValueType> {
public:
	Filter_TypeEqualMore(Criteria<ObjectType, ValueType>* criteria, ValueType value);
protected:
	bool passFilter(ValueType value) override;
};

template<typename ObjectType, typename ValueType>
inline Filter_TypeEqualMore<ObjectType, ValueType>::Filter_TypeEqualMore(Criteria<ObjectType, ValueType>* criteria, ValueType value) :
	Filter_Type<ObjectType, ValueType>(criteria, value)
{
}

template<typename ObjectType, typename ValueType>
inline bool Filter_TypeEqualMore<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value >= Filter_Type<ObjectType, ValueType>::getValue();
}