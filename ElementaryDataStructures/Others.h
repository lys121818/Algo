#pragma once
#include <iostream>


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

	a = GetArea<Widget<DataType>, DataType>(widgetA);
	b = GetArea<Widget<DataType>, DataType>(widgetB);

	if (a > b)
		return true;
	return false;
}

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

template<class Data, class DataType>
void SwapWidget(Data* widgetA, Data* widgetB)
{
	Widget<DataType> temp;

	temp = *widgetA;
	*widgetA = *widgetB;
	*widgetB = temp;

}

template<class Array, class DataType>
const size_t FindMax(Array* pArray, DataType size)
{
	const size_t maxIndex = 0;
	for (size_t i = 1; i < size; ++i)
	{
		if (Compare<Widget<DataType>, DataType>(pArray[maxIndex], pArray[i]))
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}

template<class Array, class DataType>
void CheckSorted(Array* pArray, size_t size, bool ascending = true)
{
	for (size_t i = 1; i < size; ++i)
	{
		if (ascending)
		{
			if (Compare<Widget<DataType>, DataType> ( pArray[i - 1], pArray[i] ))
			{
				std::cout << "This is Not Sorted! \n";
			}
		}
		else if (!ascending)
		{
			if (!Compare<Widget<DataType>, DataType>(pArray[i - 1], pArray[i]))
			{
				std::cout << "This is Not Sorted! \n";
			}
		}
	}
}

template <class Array, class DataType>
void SetRandomizeNumbers(Array* pArray, size_t size, size_t range)
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