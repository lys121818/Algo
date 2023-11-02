#pragma once
#include <iostream>


// Return W * H
template<class Data, class HashDataType>
HashDataType GetArea(const Data& widgetA)
{
	HashDataType area;

	area = widgetA.m_width * widgetA.m_height;

	return area;
}

// true if left is bigger
template<class Data, class HashDataType>
bool Compare(const Data& widgetA,const Data& widgetB)
{
	HashDataType a, b;

	a = GetArea<Data, HashDataType>(widgetA);
	b = GetArea<Data, HashDataType>(widgetB);

	if (a > b)
		return true;
	return false;
}

// Print the Widget
template<class Array, class HashDataType>
void PrintArrayWidget(const Array* pArray, const size_t& size)
{

	HashDataType width;	
	HashDataType height;
	HashDataType area;


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
template<class Data, class HashDataType>
void SwapWidget(Data* widgetA, Data* widgetB)
{
	Data temp;

	temp = *widgetA;
	*widgetA = *widgetB;
	*widgetB = temp;

}

// Return index of Max Widget
template<class Data, class HashDataType>
size_t FindMax(const Data* pArray, const HashDataType& size)
{
	size_t maxIndex = 0;
	for (size_t i = 1; i < size; ++i)
	{
		if (Compare<Data, HashDataType>(pArray[i], pArray[maxIndex]))
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}

// Check if the Widget is sorted in ascending or descending
template<class Data, class HashDataType>
void CheckSorted(const Data* pArray, size_t size, bool ascending = true)
{
	for (size_t i = 1; i < size; ++i)
	{
		if (ascending)
		{
			if (Compare<Data, HashDataType> ( pArray[i - 1], pArray[i] ))
			{
				std::cout << "This is Not Sorted! \n";
			}
		}
		else if (!ascending)
		{
			if (!Compare<Data, HashDataType>(pArray[i - 1], pArray[i]))
			{
				std::cout << "This is Not Sorted! \n";
			}
		}
	}
}

// Set Random width and height to the widget
template <class Data, class HashDataType>
void SetRandomizeNumbers(Data* pArray, const size_t& size, const size_t& range)
{
	HashDataType randomNumber;

	for (size_t i = 0; i < size; ++i)
	{
		randomNumber = rand() % range;
		pArray[i].m_width = randomNumber;
		randomNumber = rand() % range;
		pArray[i].m_height = randomNumber;
	}
}

// Copy B to A
template<typename Data, typename HashDataType>
void CopyWidget(Data* pArrayA, const Data* pArrayB, const size_t& size)
{
	for (size_t i = 0; i < size; ++i)
	{
		pArrayA[i] = pArrayB[i];
	}
}