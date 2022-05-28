#pragma once
#include "sort.h"

namespace structures
{
    /// <summary> Triedenie Quick sort. </summary>
    template <typename T, typename ValueType>
    class QuickSort : public Sort<T, ValueType>
    {
    public:
        /// <summary> Utriedi tabulku triedenim Quick sort. </summary>
        /// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
        void sort(structures::List<T*>* list,
            CriteriaTerritorialUnit<ValueType>* criteria, bool ascending) override;
    private:
        void quick(structures::List<T*>* list, CriteriaTerritorialUnit<ValueType>* criteria, bool ascending, int min, int max);
        bool rulling(ValueType value, ValueType pivot, bool greater, bool ascending);
    };

    template <typename T, typename ValueType>
    inline void QuickSort<T, ValueType>::sort(structures::List<T*>* list,
        CriteriaTerritorialUnit<ValueType>* criteria, bool ascending) {
        quick(list, criteria, ascending, 0, list->size() - 1);
    }

    template <typename T, typename ValueType>
    inline void QuickSort<T, ValueType>::quick(structures::List<T*>* list, CriteriaTerritorialUnit<ValueType>* criteria, bool ascending, int min, int max) {
        auto pivot = criteria->evaluate(*list->at((min + max) / 2));
        auto left = min;
        auto right = max;
        do {
            while (rulling(criteria->evaluate(*list->at(left)), pivot, false, ascending))
                left++;
            while (rulling(criteria->evaluate(*list->at(right)), pivot, true, ascending))
                right--;

            if (left <= right) {
                structures::Utils::swap(list->at(left), list->at(right));
                right--;
                left++;
            }
        } while (left <= right);

        if (min < right) {
            quick(list, criteria, ascending, min, right);
        }
        if (left < max) {
            quick(list, criteria, ascending, left, max);
        }
    }

    template<typename T, typename ValueType>
    bool QuickSort<T, ValueType>::rulling(ValueType value, ValueType pivot, bool greater, bool ascending) {
        if (greater) {
            if (ascending) {
                return value > pivot;
            }
            else {
                return value < pivot;
            }
        }
        else {
            if (ascending) {
                return value < pivot;
            }
            else {
                return value > pivot;
            }
        }
    }


}