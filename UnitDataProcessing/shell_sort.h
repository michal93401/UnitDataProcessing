#pragma once

#include "sort.h"
#include <cmath>
#include "unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Shell sort. </summary>
	template <typename T, typename ValueType>
	class ShellSort : public Sort<T, ValueType>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(structures::List<T*>* list,
			CriteriaTerritorialUnit<ValueType>* criteria, bool ascending) override;
	private:
		void shell(int krok, structures::List<T*>* list,
			CriteriaTerritorialUnit<ValueType>* criteria, bool ascending);
	};

	template<typename T, typename ValueType>
	inline void ShellSort<T, ValueType>::sort(structures::List<T*>* list,
		CriteriaTerritorialUnit<ValueType>* criteria, bool ascending)
	{
		int krok = std::log(list.size());
		shell((int)krok, list, criteria, ascending);
	}

	template<typename T, typename ValueType>
	inline void ShellSort<T, ValueType>::shell(int krok, structures::List<T*>* list,
		CriteriaTerritorialUnit<ValueType>* criteria, bool ascending)
	{
		for (int delta = 0; delta <= krok - 1; delta++) {
			for (int i = delta; i <= list.size() - 1; i += krok) {
				int j = i;
				if (ascending) {
					if ((j - krok >= delta) && (criteria->evaluate(list->at(j)) < criteria->evaluate(list->at(j - krok)))) {
						//if ((j - krok >= delta) && (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(j - krok).getKey())) {
						structures::Utils::swap(list->at(j), list->at(j - krok)); //list.swap(j, j - krok);
						j -= krok;
					}
				}
				else {
					if ((j - krok >= delta) && (criteria->evaluate(list->at(j)) > criteria->evaluate(list->at(j - krok)))) {
						//if ((j - krok >= delta) && (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(j - krok).getKey())) {
						structures::Utils::swap(list->at(j), list->at(j - krok)); //list.swap(j, j - krok);
						j -= krok;
					}
				}
			}
			if (krok > 1) {
				shell(krok - 1, list, criteria, ascending);
			}
		}
	}
}