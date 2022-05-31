#pragma once
#include "array_list.h"
#include "Criteria.h"
#include "TerritorialUnit.h"

template <typename K>
class Sorter
{
public:
	Sorter(Criteria<TerritorialUnit, K>* p_criterion) : criteria_(p_criterion) {};
	~Sorter() { delete criteria_; };
	void sort(structures::ArrayList<TerritorialUnit*>* list, bool direction);
	void quick(structures::ArrayList<TerritorialUnit*>* list, int min, int max, bool direction);
private:
	Criteria<TerritorialUnit, K>* criteria_;
};

template<typename K>
inline void Sorter<K>::sort(structures::ArrayList<TerritorialUnit*>* list, bool direction)
{
	quick(list, 0, list->size() - 1, direction);
}

template<typename K>
inline void Sorter<K>::quick(structures::ArrayList<TerritorialUnit*>* list, int min, int max, bool direction)
{
	K pivot = criteria_->evaluate(*list->at((min + max) / 2));
	int left = min;
	int right = max;

	do
	{
		if (direction) {
			while (criteria_->evaluate(*list->at(left)) < pivot)
			{
				left++;
			}
			while (criteria_->evaluate(*list->at(right)) > pivot)
			{
				right--;
			}
		}
		else
		{
			while (criteria_->evaluate(*list->at(left)) > pivot)
			{
				left++;
			}
			while (criteria_->evaluate(*list->at(right)) < pivot)
			{
				right--;
			}
		}
		/// <summary>
		/// like fucking fucking ajdontknow fucking ajdontknow
		/// </summary>
		/// <typeparam name="K"></typeparam>
		/// <param name="list"></param>
		/// <param name="min"></param>
		/// <param name="max"></param>
		/// <param name="direction"></param>
		if (left <= right)
		{
			//swap
			auto temp = list->at(left);
			list->at(left) = list->at(right);
			list->at(right) = temp;
			left++;
			right--;
		}
	} while (left <= right);
	if (min < right)
	{
		quick(list, min, right, direction);
	}
	if (left < max)
	{
		quick(list, left, max, direction);
	}
}