#pragma once
#include "Widget.h"
#include "UtilitiesForWidget.h"
#include <assert.h>
#include <iostream>


template<typename T, typename HashDataType, size_t size>
void SortingWidgets(T* pArray, bool ascending = true)
{
	
	T* low;


	for (size_t i = 0; i < size - 1; ++i)	
	{
		low = &pArray[i];

		for (size_t j = i + 1; j < size; ++j)							
		{
			if (ascending)
			{
				// Save address if the area is lower
				if (Compare<T, HashDataType>(*low, pArray[j]) )
				{
					low = &pArray[j];
				}
			}
			else
			{
				// Save address if the area is larger
				if (!Compare<T, HashDataType>(*low, pArray[j]))
				{
					low = &pArray[j];
				}
			}
		}

		// Swap widget with low value
		if (low != &pArray[i])
		{
			SwapWidget<T, HashDataType>(&pArray[i], low);
		}
	}
	PrintArrayWidget<T ,HashDataType>(pArray, size);

}


template<typename T,typename HashDataType>
void WidgetCountingSort(T* pArray, const size_t size,bool ascending = true)
{

	std::cout << "Array Before Sortted\n";
	PrintArrayWidget<T, HashDataType>(pArray, size);

	// Find index of max Widget
	size_t max = FindMax <T, HashDataType>(pArray, size);

	// Data of max widget
	T maxArea = pArray[max];

	// Create array size of max of widget
	const size_t arraySizeC = GetArea<T, HashDataType>(maxArea) + 1;

	// Might overflow since it's creating the array with size of area
	assert(arraySizeC < 100000);

	// Create array for counting
	size_t* pCounting = new size_t[arraySizeC]{0};

	// Create array to store sorted value
	T* pSorted = new T[size]{0};

	// add count to count array of value
	for (size_t i = 0; i < size; ++i)
	{
		size_t index = GetArea<T,HashDataType>( pArray[i]);
		pCounting[index]++;
	}

	// Add previous index value to current index value of count array
	for (size_t i = 1; i < arraySizeC; ++i)
	{
		pCounting[i] += pCounting[i - 1];
	}


	if (ascending)
	{
		// Sorting array using count array
		for (size_t i = size; i > 0; --i)
		{
			size_t arrayElement = GetArea<T,HashDataType>( pArray[i - 1]);
			size_t sortIndex = pCounting[arrayElement] - 1;

			pSorted[sortIndex] = pArray[i - 1];

			// Decrease the count array to handle duplicate value
			--pCounting[arrayElement];
		}
	}
	// descending
	else
	{
		for (size_t i = 1; i < size + 1; ++i)
		{
			size_t arrayElement = GetArea<T, HashDataType>(pArray[i - 1]);
			size_t sortIndex = size - pCounting[arrayElement];

			pSorted[sortIndex] = pArray[i - 1];

			pSorted[sortIndex] = pArray[i - 1];

			--pCounting[arrayElement];
		}
	}

	// Copy Sorted Widget to original Widget
	CopyWidget<T,HashDataType>(pArray, pSorted,size);

	std::cout << "Print Array" << std::endl;
	PrintArrayWidget<T, HashDataType>(pArray, size);

	// delete pointer
	delete[] pSorted;
	delete[] pCounting;
}

