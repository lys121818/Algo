#pragma once
#include "Widget.h"
#include "SortingWidgets.h"
#include "Sorting.h"
#include "LinkedList.h"
#include <list>

/*	TEST DEFINES
#define WIDGET
*/
#define LINKED_LIST


// This Would change whole data type of widget struct and functions
#define ASCENDING	true
#define SIZE		6
#define RANDOMRANGE	1000
using DataType = float;
using ArraySize = size_t;


int main()
{
	srand(time(nullptr));
	// WIDGET TEST
#ifdef WIDGET
	// SETTINGS

	const size_t range = RANDOMRANGE;

	const bool ascending = ASCENDING;

	const ArraySize size = SIZE;

	Widget<DataType> pArray[size];

	SetRandomizeNumbers<Widget<DataType>,DataType>(pArray, size, range);
	SortingWidgets<DataType, size>(pArray, ascending);
	CheckSorted<Widget<DataType>, DataType>(pArray, size, ascending);
#endif

	// LINKED_LIST TEST
#ifdef LINKED_LIST

	LinkedList linkedList;
	for (size_t j = 0; j < 1000; ++j)
	{

		for (size_t i = 0; i < 10; ++i)
		{
			
			size_t randIndex = rand() % 5;
			std::cout << i << " => Insert Index[" << randIndex << "]\n\n";
			std::cout << "Delete [" << randIndex << "]\n\n";

			linkedList.Insert( i , randIndex);
			linkedList.Delete(randIndex);
			linkedList.Print();
			std::cout << "\n";
		}
		linkedList.Clear();

	}

#endif
	return 0;
}