#pragma once
#include <iostream>


// Return W * H
template<class Data, class DataType>
DataType GetArea(Data widgetA)
{
	DataType area;

	area = widgetA.m_width * widgetA.m_height;

	return area;
}

// true if left is bigger
template<class Data, class DataType>
bool Compare(Data widgetA, Data widgetB)
{
	DataType a, b;

	a = GetArea<Data, DataType>(widgetA);
	b = GetArea<Data, DataType>(widgetB);

	if (a > b)
		return true;
	return false;
}

// Print the Widget
template<class Array, class DataType>
void PrintArrayWidget(Array* pArray, size_t size)
{

	DataType width;	
	DataType height;
	DataType area;


	for (size_t i = 0; i < size; ++i)
	{
		width = pArray[i].m_width;
		height = pArray[i].m_height;
		area = width * height;

		std::cout << "Widget[" << i << "]" << std::endl;
		std::cout << "Width: " << width << std::endl;
		std::cout << "Height: " << height << std::endl;

		std::cout << "Area: " << area << std::endl;

		std::cout << '\n';
	}
	
}

// Swap A and B
template<class Data, class DataType>
void SwapWidget(Data* widgetA, Data* widgetB)
{
	Data temp;

	temp = *widgetA;
	*widgetA = *widgetB;
	*widgetB = temp;

}

// Return index of Max Widget
template<class Data, class DataType>
size_t FindMax(Data* pArray, DataType size)
{
	size_t maxIndex = 0;
	for (size_t i = 1; i < size; ++i)
	{
		if (Compare<Data, DataType>(pArray[i], pArray[maxIndex]))
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}

// Check if the Widget is sorted in ascending or descending
template<class Data, class DataType>
void CheckSorted(Data* pArray, size_t size, bool ascending = true)
{
	for (size_t i = 1; i < size; ++i)
	{
		if (ascending)
		{
			if (Compare<Data, DataType> ( pArray[i - 1], pArray[i] ))
			{
				std::cout << "This is Not Sorted! \n";
			}
		}
		else if (!ascending)
		{
			if (!Compare<Data, DataType>(pArray[i - 1], pArray[i]))
			{
				std::cout << "This is Not Sorted! \n";
			}
		}
	}
}

// Set Random width and height to the widget
template <class Data, class DataType>
void SetRandomizeNumbers(Data* pArray, size_t size, size_t range)
{
	DataType randomNumber;

	for (size_t i = 0; i < size; ++i)
	{
		randomNumber = rand() % range;
		pArray[i].m_width = randomNumber;
		randomNumber = rand() % range;
		pArray[i].m_height = randomNumber;
	}
}

// Copy B to A
template<typename Data, typename DataType>
void CopyWidget(Data* pArrayA, Data*pArrayB, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		pArrayA[i] = pArrayB[i];
	}
}