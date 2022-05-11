#pragma once
#include "FilterWithCriteria.h"

template<typename KeyType, typename ObjectType, typename ValueType>
class SelectionCriteria
{
public:
	SelectionCriteria(Criteria<ObjectType, ValueType>* criteria);
	~SelectionCriteria();
	ObjectType& selectBest();
protected:
	virtual bool isTestedValueBetter(ValueType bestNow, ValueType bestTested);
private:
	Criteria<ObjectType, ValueType>* criteria_;
};