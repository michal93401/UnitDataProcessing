#pragma once
#include "Filter.h"
#include "array_list.h"

template<typename ObjectType>
class Filter_Composite : Filter<ObjectType> {
public:
	Filter_Composite();
	~Filter_Composite();
	void registerFilter(Filter<ObjectType>* filter);
protected:
	structures::ArrayList<Filter<ObjectType>*>* filters_ = new structures::ArrayList<Filter<ObjectType>*>;
};

template<typename ObjectType>
inline Filter_Composite<ObjectType>::Filter_Composite()
{
}

template<typename ObjectType>
inline Filter_Composite<ObjectType>::~Filter_Composite()
{
	for (auto item : *filters_) {
		delete item;
	}
	delete filters_;
}

template<typename ObjectType>
inline void Filter_Composite<ObjectType>::registerFilter(Filter<ObjectType>* filter)
{
	filters_->add(filter);
}
