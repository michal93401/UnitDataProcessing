#pragma once
#include "Filter.h"

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