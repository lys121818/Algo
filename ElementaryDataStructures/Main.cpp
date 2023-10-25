#pragma once
#include "Widget.h"
#include "SortingWidgets.h"
#include "Sorting.h"
#include "LinkedList.h"
#include <list>

// DEFINES TO TEST
/*	
#define WIDGET
*/
#define LINKED_LIST


// This Would change whole data type of widget struct and functions
#define ASCENDING	true
#define SIZE		6
#define RANDOMRANGE	10
using DataType = int;
using ArraySize = size_t;


int main()
{
	srand(time(nullptr));
	const size_t range = RANDOMRANGE;

	// WIDGET TEST
#ifdef WIDGET
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
#ifdef LINKED_LIST

	LinkedList linkedList;


	for (size_t j = 0; j < 1; ++j)
	{
		// Inserting Test
		for (size_t i = 0; i < 10; ++i)
		{
			size_t randIndex = rand() % range;
			size_t randValue = rand() % range;

			std::cout << randValue << " => Insert to Index[" << randIndex << "]\n\n";
			linkedList.Insert(randValue, randIndex);

			// Print
			//linkedList.Print();

		}

		linkedList.Print();

		// Delete Test
		for (size_t i = 0; i < 10; ++i)
		{
			size_t randValue = rand() % range;

			std::cout << "Delete [" << randValue << "]\n\n";
			linkedList.Delete(randValue);
		}

		linkedList.Print();
		linkedList.Clear();

		// Push Back & Push Front Test
		for (size_t i = 0; i < 10; ++i)
		{
			size_t randValueA = rand() % range;
			size_t randValueB = rand() % range;

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
	return 0;
}