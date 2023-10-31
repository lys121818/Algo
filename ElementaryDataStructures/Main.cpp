#pragma once
#include "Widget.h"
#include "SortingWidgets.h"
#include "Sorting.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "HashTableExample.h"
#include <list>

// DEFINES TO TEST
#define WIDGET 0
#define LINKED_LIST 0
#define HASH_TABLE 1


// This Would change whole data type of widget struct and functions
#define ASCENDING	true
#define SIZE		6
#define RANDOMRANGE	10
using DataType = int;
using ArraySize = size_t;

// Hash Table



int main()
{
	srand(time(nullptr));
	const size_t range = RANDOMRANGE;

	// WIDGET TEST
#if WIDGET
	// SETTINGS


	const bool ascending = ASCENDING;

	const ArraySize size = SIZE;

	Widget<DataType> pArray[size];

	for (size_t i = 0; i < 100; ++i)
	{
		//SortingWidgets<Widget<DataType>, DataType, size>(pArray, ascending);
		// Random Set Widget
		SetRandomizeNumbers<Widget<DataType>,DataType>(pArray, size, range);

		// Counting Sort Widget.ver
		WidgetCountingSort<Widget<DataType>, DataType>(pArray, size, ascending);

		// Check if it's sorted
		CheckSorted<Widget<DataType>, DataType>(pArray, size, ascending);

	}
#endif

	// LINKED_LIST TEST
#if LINKED_LIST

	LinkedList<DataType> linkedList;


	for (size_t j = 0; j < 1; ++j)
	{
		// Inserting Test
		for (size_t i = 0; i < 10; ++i)
		{
			size_t randIndex = rand() % range;
			DataType randValue = rand() % range + 97;

			std::cout << randValue << " => Insert to Index[" << randIndex << "]\n\n";
			linkedList.Insert(randValue, randIndex);

			// Print
			//linkedList.Print();

		}
		linkedList.Print();

		LinkedList<DataType>::Iterator iter = linkedList.begin();
		for (iter; iter != linkedList.end(); ++iter)
		{
			std::cout << (*iter)->m_data << std::endl;
			
		}

		std::cout << std::endl;
		iter = linkedList.begin();
		for (iter = linkedList.begin(); iter != linkedList.end(); ++iter)
		{
			(*iter)->m_data;
		}
		linkedList.Print();

		//iter = linkedList.begin();
		//for (iter; iter != linkedList.end(); ++iter)
		//{
		//	std::cout << iter.data;
		//}

		// Delete Test
		for (size_t i = 0; i < 10; ++i)
		{
			DataType randValue = rand() % range + 97;

			std::cout << "Delete [" << randValue << "]\n\n";
			linkedList.Delete(randValue);
		}

		linkedList.Print();
		linkedList.Clear();

		// Push Back & Push Front Test
		for (size_t i = 0; i < 10; ++i)
		{
			DataType randValueA = rand() % range + 97;
			DataType randValueB = rand() % range + 97;

			linkedList.Push_Back(randValueA);
			linkedList.Push_Front(randValueB);
		}

		linkedList.Print();

		// Pop_Back Test
		for (size_t i = 0; i < 10; ++i)
		{
			linkedList.Pop_Front();
		}

		linkedList.Print();


		// Push_Back Test
		for (size_t i = 0; i < 10; ++i)
		{
			linkedList.Pop_Back();
		}



		linkedList.Print();


		// Clean List
		linkedList.Clear();

	}

#endif

#if HASH_TABLE

	
#endif
	return 0;
}