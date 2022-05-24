#pragma once

#include "sort.h"
#include <cmath>
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Shell sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class ShellSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;

		void shell(int krok, UnsortedSequenceTable<K, T>& table);
	private:

	};

	template<typename K, typename T>
	inline void ShellSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		int krok = std::log(table.size());
		shell((int)krok, table);

		/*for (int delta = 0; delta < krok - 1; delta++) {
			for (int i = delta; i < size - 1; i += krok) {
				int j = i;
				if (j - krok = > delta) && (table->getItemAtIndex(j) < table->getItemAtIndex(j - krok)) {
					table->swap(j, j - krok);
					j -= krok;
				}

			}
			if (krok > 1) {
				shell(krok - 1);
			}
		}*/
	}

	template<typename K, typename T>
	inline void ShellSort<K, T>::shell(int krok, UnsortedSequenceTable<K, T>& table)
	{
		for (int delta = 0; delta <= krok - 1; delta++) {
			for (int i = delta; i <= table.size() - 1; i += krok) {
				int j = i;
				if ((j - krok >= delta) && (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(j - krok).getKey())) {
					table.swap(j, j - krok);
					j -= krok;
				}
			}
			if (krok > 1) {
				shell(krok - 1, table);
			}
		}
	}
}