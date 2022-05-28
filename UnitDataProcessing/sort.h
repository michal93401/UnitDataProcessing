#pragma once
#include "CriteriaTerritorialUnit.h"
#include "unsorted_sequence_table.h"
#include "list.h"

namespace structures
{
	template <typename T, typename ValueType>
	class Sort
	{
	public:
		/// <summary> Destruktor. </summary>
		virtual ~Sort();

		/// <summary> Funkcny operator utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		/// <remarks> Využíva metódu sort. </remarks>
		void operator()(structures::List<T*>* list,
			CriteriaTerritorialUnit<ValueType>* criteria, bool ascending);

		/// <summary> Utriedi utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		virtual void sort(structures::List<T*>* list,
			CriteriaTerritorialUnit<ValueType>* criteria, bool ascending) = 0;
	};

	template<typename T, typename ValueType>
	inline Sort<T, ValueType>::~Sort()
	{
	}

	template<typename T, typename ValueType>
	inline void Sort<T, ValueType>::operator()(structures::List<T*>* list,
		CriteriaTerritorialUnit<ValueType>* criteria, bool ascending)
	{
		this->sort(list, criteria, ascending);
	}
}