#pragma once
#include <iostream>

// true if left is bigger
template<class Data, class DataType>
bool Compare(Data widgetA, Data widgetB)
{
	DataType a, b;

	a = widgetA.m_width * widgetA.m_height;
	b = widgetB.m_width * widgetB.m_height;

	if (a > b)
		return true;
	return false;
}

template<class Data, class DataType>
DataType GetArea(Data widgetA)
{
	DataType area;

	area = widgetA.m_width * widgetA.m_height;

	return area;
}


template<class Array, class DataType>
void PrintArrayWidget(Array* pArray, DataType size)
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
size_t FindMax(Array* pArray, DataType size)
{
	size_t maxIndex = 0;
	for (size_t i = 1; i < size; ++i)
	{
		if (Compare(pArray[maxIndex], pArray[i]))
		{
			maxIndex = i;
		}
	}

}