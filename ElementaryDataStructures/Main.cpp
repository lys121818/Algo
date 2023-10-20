#pragma once
#include "Widget.h"
#include "SortingWidgets.h"
#include "Sorting.h"
#include "LinkedList.h"

/*	TEST DEFINES
#define WIDGET
*/
#define LINKED_LIST


// This Would change whole data type of widget struct and functions
#define ASCENDING	true
#define SIZE		6
#define RANDOMRANGE	1000
using DataType = int;
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

	//linkedList.Push_Back(1);
	//linkedList.Push_Front(2);
	//linkedList.Push_Back(3);
	//linkedList.Push_Front(4);
	//linkedList.Push_Back(5);
	for (size_t i = 0; i < 10; ++i)
	{
		size_t randIndex = rand() % 5;
		linkedList.Insert(i, randIndex);

		randIndex = rand() % 5;
		linkedList.Delete(randIndex);
	}
	//linkedList.Insert(1, 3);
	//linkedList.Insert(2, 2);
	//linkedList.Insert(3, 2);
	//linkedList.Insert(4, 2);
	//linkedList.Insert(5, 2);
	//
	//linkedList.Delete(4);
	//linkedList.Delete(4);
	//
	//linkedList.Delete(3);
	linkedList.Print();

#endif
	return 0;
}