#pragma once
#include "Widget.h"
#include "Others.h"
#include <iostream>


template<class DataType, size_t size>
void SortingWidgets(Widget<DataType>* pArray, bool ascending = true)
{

	Widget<DataType>* low;


	for (size_t i = 0; i < size - 1; ++i)	
	{
		low = &pArray[i];

		for (size_t j = i + 1; j < size; ++j)							
		{
			if (ascending)
			{
				if (Compare<Widget<DataType>, DataType>(*low, pArray[j]) )
				{
					low = &pArray[j];
				}
			}
			else
			{
				if (!Compare<Widget<DataType>, DataType>(*low, pArray[j]))
				{
					low = &pArray[j];
				}
			}
		}

		if (low != &pArray[i])
		{
			SwapWidget<Widget<DataType>, DataType>(&pArray[i], low);
		}
	}
	PrintArrayWidget<Widget<DataType> ,DataType>(pArray, size);

}


// TODO: WORKING ON COUNTING SORT

template<class DataType, size_t size>
void WidgetCountingSort(Widget<DataType>* pArray)
{
	/*
	std::cout << "Array Before Sortted\n";
	PrintArrayWidget<Widget<DataType>, DataType>(pArray, size);

	size_t maxValue = FindMax(pArray, size);
	const size_t arraySizeC = maxValue + 1;

	Widget<DataType>* pSorted[size]{ 0 };
	size_t* pCounting[arraySizeC]{ 0 };

	// add count to count array of value
	for (size_t i = 0; i < size; ++i)
	{
		size_t index = pArray[i];
		pCounting[index]++;
	}




	// Add previous index value to current index value of count array
	for (size_t i = 1; i < arraySizeC; ++i)
	{
		pCounting[i] += pCounting[i - 1];
	}

	// Sorting array using count array
	for (size_t i = size; i > 0; --i)
	{
		size_t arrayElement = pArray[i - 1];
		size_t sortIndex = pCounting[arrayElement] - 1;

		pSorted[sortIndex] = arrayElement;

		// Decrease the count array to handle duplicate value
		--pCounting[arrayElement];
	}
	std::cout << "Print Array" << std::endl;
	PrintArrayWidget(pArray, size);

	// delete pointer
	delete[] pSorted;
	delete[] pCounting;
	*/
}

