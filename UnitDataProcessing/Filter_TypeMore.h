#pragma once
#include "Filter_Type.h"

template<typename ObjectType, typename ValueType>
class Filter_TypeMore : public Filter_Type<ObjectType, ValueType> {
public:
	Filter_TypeMore(Criteria<ObjectType, ValueType>* criteria, ValueType value);
protected:
	bool passFilter(ValueType value) override;
};

template<typename ObjectType, typename ValueType>
inline Filter_TypeMore<ObjectType, ValueType>::Filter_TypeMore(Criteria<ObjectType, ValueType>* criteria, ValueType value) :
	Filter_Type<ObjectType, ValueType>(criteria, value)
{
}

template<typename ObjectType, typename ValueType>
inline bool Filter_TypeMore<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value > getValue();
}