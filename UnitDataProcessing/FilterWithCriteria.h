#pragma once
#include "Filter.h"
#include "Criteria.h"

template<typename ObjectType, typename ValueType>
class FilterWithCriteria : public Filter<ObjectType> {
public:
	FilterWithCriteria(Criteria<ObjectType, ValueType>* criteria);
	~FilterWithCriteria();
	bool pass(const ObjectType& object);
protected:
	virtual bool passFilter(ValueType value) = 0;
private:
	Criteria<ObjectType, ValueType>* criteria_;
};

template<typename ObjectType, typename ValueType>
inline FilterWithCriteria<ObjectType, ValueType>::FilterWithCriteria(Criteria<ObjectType, ValueType>* criteria)
	: criteria_(criteria)
{
}

template<typename ObjectType, typename ValueType>
inline FilterWithCriteria<ObjectType, ValueType>::~FilterWithCriteria()
{
	delete criteria_;
}

template<typename ObjectType, typename ValueType>
inline bool FilterWithCriteria<ObjectType, ValueType>::pass(const ObjectType& object)
{
	return passFilter(criteria_->evaluate(object));
}

//template<typename ObjectType, typename ValueType>
//inline bool FilterWithCriteria<ObjectType, ValueType>::passFilter(ValueType value) 
//{
//	return true;
//}