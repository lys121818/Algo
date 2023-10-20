#pragma once
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include "Others.h"
#include <assert.h>


template <class T>
void CountingSort(T* pArray, const size_t& size)
{
	std::cout << "Array Before Sortted\n";
	PrintArray(pArray, size);

	size_t maxValue = MaxValue(pArray, size);
	size_t arraySizeC = maxValue + 1;

	T* pSorted = new T[size]{ 0 };
	size_t* pCounting = new size_t[arraySizeC] {0};

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
	CopyArray(pArray,pSorted,size);
	std::cout << "Print Array" << std::endl;
	PrintArray(pArray, size);

	// delete pointer
	delete[] pSorted;
	delete[] pCounting;
}

template <class T>
void CountingSortForRadix(T* array, const size_t& size, size_t digit, bool ascending = true)
{
	T countArray[10] = { 0 };

	T* pSorted = new T[size];

	// add count to count array of value
	for (size_t i = 0; i < size; ++i)
	{
		size_t index = (array[i] / digit) % 10;
		countArray[index]++;
	}

	// Add previous index value to current index value of count array
	for (size_t i = 1; i < 10; ++i)
	{
		countArray[i] += countArray[i - 1];
	}


	if (ascending)
	{
		// Sorting array using count array
		for (size_t i = size; i > 0; --i)
		{
			size_t arrayElement = (array[i - 1] / digit) % 10;	
			size_t sortIndex;
	
			sortIndex = countArray[arrayElement] - 1;
			
			pSorted[sortIndex] = array[i-1];

			// Decrease the count array to handle duplicate value
			--countArray[arrayElement];
		}
	}
	// Descending
	else
	{
		for (size_t i = 0; i < size; ++i)
		{
			size_t arrayElement = (array[i] / digit) % 10;	
			size_t sortIndex;

			sortIndex = size - countArray[arrayElement];

			pSorted[sortIndex] = array[i];

			--countArray[arrayElement];
		}
	}

	// copy sorted array to the input array
	CopyArray(array, pSorted ,size);

	int memoryUsed = 0;
	memoryUsed = (sizeof(pSorted) * size) + (sizeof(countArray) * 10);
	std::cout << "Memory that has been used in this algorithmn: " << memoryUsed << std::endl;

	// delete pointer
	delete[] pSorted;
}

template<class T>
void RadixSort(T* array, const size_t& size, void(*sort)(T*,const size_t&,size_t,bool), bool ascending = true)
{
	T max = MaxValue(array, size);

	std::cout << "Array Before Sortted\n";
	PrintArray(array, size);

	// runs until the max value of digit
	for (size_t digit = 1; (max / digit) > 0; digit *= 10)
	{
		sort(array, size, digit,ascending);
	}

	std::cout << "Print Array" << std::endl;
	PrintArray(array, size);


}


#pragma region Not valid for current assignment

// Radix sort taking queick sort as sorting function doesn't work :(
template<class VariableType>
size_t PartitionForQuickSort(VariableType* array, size_t pivot, size_t digit, bool ascending)
{
	// pivot of searching array
	int thisPivot = (array[pivot] / digit) % 10;

	int thisLowIndex = -1;

	// element below the pivot
	for (int thisHighIndex = 0; thisHighIndex < pivot; ++thisHighIndex)
	{
		if(ascending)
		{
			// swap if it's lower than pivot
			if ( (array[thisHighIndex] / digit) % 10 <= thisPivot)
			{
				++thisLowIndex;
				Swap(&array[thisLowIndex], &array[thisHighIndex]);
			}
		}
		else
		{
			// swap if it's lower than pivot
			if ( (array[thisHighIndex] / digit) % 10 >= thisPivot)
			{
				++thisLowIndex;
				Swap(&array[thisLowIndex], &array[thisHighIndex]);
			}
		}
	}
	// add low index before swap
	++thisLowIndex;

	// swap with pivot and low index value
	Swap(&array[thisLowIndex], &array[pivot]);

	// return low index
	return thisLowIndex;
}



// Relize that this is not a standard library :(
template<class T>
std::vector<T> RadixSort(std::vector<T> array, std::vector<T>(*sort)(const std::vector<T>&, size_t))
{
	T max = MaxValue(array);
	size_t size = array.size();

	std::cout << "Array Before Sortted\n";
	PrintArray(array);

	// runs until the max value of digit
	for (size_t digit = 1; (max / digit) > 0; digit *= 10)
	{
		array = sort(array, digit);
	}

	std::cout << "Print Array" << std::endl;
	PrintArray(array);

	return array;
}

template <class T>
std::vector<T> CountingSort(const std::vector<T>& array)
{
	// size of the array input
	size_t size = array.size();
	// max value inside input array
	T maxValue = MaxValue(array);

	// create vector to counting array
	std::vector<T> count(maxValue + 1, 0);

	// create array to store sort
	std::vector<T> sorted(size, 0);

	std::cout << "Array Before Sortted\n";
	PrintArray(array);


	for (size_t i = 0; i < size; ++i)
	{
		// add A[i] element to index of C
		size_t index = array[i];
		count[index]++;
	}

	// Add previous index value to current index value
	for (size_t i = 1; i < maxValue + 1; ++i)
	{
		count[i] += count[i - 1];
	}

	for (size_t i = size; i > 0; --i)
	{
		size_t arrayElement = array[i - 1];	// a[i]
		size_t sortIndex = count[arrayElement] - 1;	// C is pointing of the index of array, so decrease the value of index
		sorted[sortIndex] = arrayElement;
		--count[arrayElement];	// decrease element to handle duplicate values
	}

	std::cout << "Print Array" << std::endl;
	PrintArray(sorted);

	return sorted;

}

template <class T>
std::vector<T> CountingSortForRadix(const std::vector<T>& array, size_t digit)
{
	// size of the array
	size_t size = array.size();

	// array to count 
	//std::vector<T> countArray(10);

	// Add the count array to be mapped since creating with array allocates unnecessary memeory 
	std::map<T, size_t> countArray;

	// array of sorted input
	std::vector<T> sorted(size);

	for (size_t i = 0; i < size; ++i)
	{
		// add A[i] element's digit to index of count
		T index = (array[i] / digit) % 10;
		if (countArray.find(index) == countArray.end())
		{
			// add key if the element hasn't been added
			std::pair<T, size_t> pair;
			pair.first = index;
			pair.second = 1;
			countArray.insert(pair);
		}
		else
			countArray[index]++;	// add if the element is already exist as key value
	}

	// Add previous index value to current index value
	for(auto iter = ++countArray.begin(); iter != countArray.end(); ++iter)
	{
		iter->second += (--iter)->second;
		++iter;	// add the value that has decrease on top
	}

	for (size_t i = size; i > 0; --i)
	{
		T arrayElement = (array[i - 1] / digit) % 10;	// a[i]
		size_t sortIndex = countArray[arrayElement] - 1;	// C is pointing of the index of array, so decrease the value of index
		sorted[sortIndex] = array[i - 1];
		--countArray[arrayElement];	// decrease element to handle duplicate values
	}

	size_t memoryAllocated = 0;
	memoryAllocated += (sizeof(countArray) * sorted.size());
	memoryAllocated += (sizeof(sorted) * sorted.size());
	std::cout << "Memory used: " << memoryAllocated << std::endl;


	return sorted;
}




template <class T>
void SortingFunction(T* pArray, const size_t& size)
{
	int* low;
	int temp;

	using LineNumber = unsigned int;
	using VisitCount = unsigned int;
	std::unordered_map<LineNumber, VisitCount> visitMap;

	//Continue in this manner until the array has been sorted.
	for (size_t i = 0; ++visitMap[1], i < size - 1; ++i)	// O(n)			//[1]
	{
		++visitMap[2];
		low = &pArray[i];	// n - 1										//[2]
		//std::cout << "i: " << i << std::endl;
		//Searches the array to find the smallest element.
		//Search for the second smallest element.
		for (size_t j = i + 1; ++visitMap[3], j < size; ++j)								//[3]
		{
			//std::cout << "j: " << j << std::endl;
			// if element in low is bigger then searched element, keep the address of array[j]
			++visitMap[4];
			if (*low > pArray[j])											//[4]
			{
				++visitMap[5];
				low = &pArray[j];											//[5]
			}
		}
		//Swap this element with the first element in the array.
		//Swap this element with the second element of the array.
		if (low != &pArray[i])
		{
			++visitMap[6];
			temp = pArray[i];													//[6]
			++visitMap[7];
			pArray[i] = *low;													//[7]
			++visitMap[8];
			*low = temp;														//[8]
		}
	}
	// Print the array to see if it's sorted
	for (size_t i = 0; i < size; i++)
	{
		std::cout << i << ": " << pArray[i] << std::endl;
	}

	for (auto iter = visitMap.begin(); iter != visitMap.end(); ++iter)
	{
		std::cout << iter->first << ":" << iter->second << '\n';
	}
}

#pragma endregion