#pragma once
#include "FilterWithCriteria.h"

template<typename ObjectType, typename ValueType>
class Filter_Range : public FilterWithCriteria<ObjectType, ValueType> {
public:
	Filter_Range(Criteria<ObjectType, ValueType>* criteria, ValueType minValue, ValueType maxValue);
protected:
	virtual bool passFilter(ValueType value);
	ValueType getMin() const;
	ValueType getMax() const;
private:
	ValueType minValue_;
	ValueType maxValue_;
};

template<typename ObjectType, typename ValueType>
inline Filter_Range<ObjectType, ValueType>::Filter_Range(Criteria<ObjectType, ValueType>* criteria, ValueType minValue, ValueType maxValue)
	: FilterWithCriteria<ObjectType, ValueType>(criteria), minValue_(minValue), maxValue_(maxValue)
{
}

template<typename ObjectType, typename ValueType>
inline bool Filter_Range<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value > minValue_ && value < maxValue_;
}

template<typename ObjectType, typename ValueType>
inline ValueType Filter_Range<ObjectType, ValueType>::getMin() const
{
	return minValue_;
}

template<typename ObjectType, typename ValueType>
inline ValueType Filter_Range<ObjectType, ValueType>::getMax() const
{
	return maxValue_;
}
