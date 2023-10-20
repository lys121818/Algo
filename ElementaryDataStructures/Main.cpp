#pragma once
#include "Widget.h"
#include "SortingWidgets.h"
#include "Sorting.h"

// This Would change whole data type of widget struct and functions
#define ASCENDING	false
#define SIZE		6
using DataType = float;
using ArraySize = size_t;


int main()
{
	const bool ascending = ASCENDING;

	const ArraySize size = SIZE;

	Widget<DataType> pArray[size];


	pArray[0].m_width = 21.3;
	pArray[0].m_height = 10.5;

	pArray[1].m_width = 13.0;
	pArray[1].m_height = 16.9;

	pArray[2].m_width = 14.6;
	pArray[2].m_height = 26.4;

	pArray[3].m_width = 11.2;
	pArray[3].m_height = 17.6;
	
	pArray[4].m_width = 12.5;
	pArray[4].m_height = 10.1;
	
	pArray[5].m_width = 12.7;
	pArray[5].m_height = 20.4;


	SortingWidgets<DataType, size>(pArray, ascending);
	//WidgetCountingSort<DataType, size>(pArray);

	return 0;
}