#pragma once


#include <iostream>


// DEFINES TO TEST

#define WIDGET			0
#define LINKED_LIST		0
#define HASH_TABLE		1

// DEFINE FOR HEADERS
#define WIDGET_HEADER			1
#define LINKED_LIST_HEADER		0
#define HASH_TABLE_HEADER		1


#if WIDGET_HEADER
#include "Widget.h"
#include "SortingWidgets.h"
#include "Widget.h"

#endif

#if LINKED_LIST_HEADER
#include "LinkedList.h"
#endif

#if HASH_TABLE_HEADER
#include "FNV.h"
#include "HashTable.h"
#define HASH_SIZE 100
#endif



// This Would change whole data type of widget struct and functions
#define ASCENDING	true
#define SIZE		6
#define RANDOMRANGE	10

// size of the array
using ArraySize = size_t;

// General Data Type
using DataType = float;	// currently widget is using this for data type





int main()
{
	srand(time(nullptr));
	const size_t range = RANDOMRANGE;


	// HASH TABLE TEST
#if HASH_TABLE
	// For Test Purpose
	/*---------------------------------------------------------
	
	 Testing for Hash Table											       [Current set up for Testing]
																	<HashDataType>			<KeyType>
	 Use Testing define under to test hash table					Widget					Widget
																	Float/Double			float/double
	 KeyType and DataType is on top of the main function			Unsigned int			Widget
																	const char*				int/float/double
	 
	----------------------------------------------------------*/

	// Data Type using in Hash table
	using HashDataType = float;

	// Key variable for the hash table			
	using KeyType = float;

	// Make sure you only define one of from testing defines
	#define TESTING_WIDGET			0
	#define TESTING_DOUBLE_FLOAT	1
	#define TESTING_STRING			0
	#define TESTING_UINT			0

	// Test for string keys
#if TESTING_STRING
	HashTable<KeyType, HashDataType> hash(HASH_SIZE);
	KeyType* string = new KeyType [10];

	string[0] = "Astring";
	string[1] = "Bstring";
	string[2] = "Cstring";
	string[3] = "Dstring";
	string[4] = "Estring";
	string[5] = "Fstring";
	string[6] = "Gstring";
	string[7] = "Hstring";
	string[8] = "Istring";
	string[9] = "Jstring";


	hash.Insert(string[0], 345);
	hash.Insert(string[1], 123);
	hash.Insert(string[2], 2);
	hash.Insert(string[3], 4534);
	hash.Insert(string[4], 423444);
	hash.Insert(string[5], 78653);
	hash.Insert(string[6], 34);
	hash.Insert(string[7], 4);
	hash.Insert(string[8], 45340);
	hash.Insert(string[9], 98752);

	hash.ShowHashTable();

	hash.Insert("Hstring", 5);

	hash.Delete("Hstring");

	hash.Delete("Istring");
	hash.Delete("Istring");

	hash.Delete("NOT EXIST");

	hash.ShowHashTable();


#endif	//TESTING_STRING

#if TESTING_WIDGET

	HashTable<KeyType, HashDataType> hash(HASH_SIZE);

	// Test With Widget


	KeyType keyWidget[10];
	HashDataType dataWidget[10];


	SetRandomizeNumbers<Widget<DataType>, DataType>(keyWidget, 10, RANDOMRANGE);
	SetRandomizeNumbers<Widget<DataType>, DataType>(dataWidget, 10, RANDOMRANGE);

	hash.Insert(keyWidget[0], dataWidget[0]);
	hash.Insert(keyWidget[1], dataWidget[1]);
	hash.Insert(keyWidget[2], dataWidget[2]);
	hash.Insert(keyWidget[3], dataWidget[3]);
	hash.Insert(keyWidget[4], dataWidget[4]);
	hash.Insert(keyWidget[5], dataWidget[5]);
	hash.Insert(keyWidget[6], dataWidget[6]);
	hash.Insert(keyWidget[7], dataWidget[7]);
	hash.Insert(keyWidget[8], dataWidget[8]);
	hash.Insert(keyWidget[9], dataWidget[9]);

	hash.ShowHashTable();
#endif	//TESTING_WIDGET

#if TESTING_UINT

	HashTable<KeyType, HashDataType> hash(HASH_SIZE);

	// Test With Widget
	Widget<DataType> widget[10];

	SetRandomizeNumbers<Widget<DataType>, DataType>(widget, 10, RANDOMRANGE);

	// Test With Widget
	KeyType u_int[10];

	u_int[0] = 465;
	u_int[1] = 45754;
	u_int[2] = 234;
	u_int[3] = 845545;
	u_int[4] = 124125;
	u_int[5] = 123;
	u_int[6] = 6536;
	u_int[7] = 123;
	u_int[8] = 2;
	u_int[9] = 546;

	hash.Insert(u_int[0], widget[0]);
	hash.Insert(u_int[1], widget[1]);
	hash.Insert(u_int[2], widget[2]);
	hash.Insert(u_int[3], widget[3]);
	hash.Insert(u_int[4], widget[4]);
	hash.Insert(u_int[5], widget[5]);
	hash.Insert(u_int[6], widget[6]);
	hash.Insert(u_int[7], widget[7]);
	hash.Insert(u_int[8], widget[8]);
	hash.Insert(u_int[9], widget[9]);

	hash.ShowHashTable();
#endif

#if TESTING_DOUBLE_FLOAT

	HashTable<KeyType, HashDataType> hash(HASH_SIZE);

	KeyType keys[10];

	keys[0] = 123.815;
	keys[1] = 4654.32;
	keys[2] = 321.51;
	keys[3] = 0.563;
	keys[4] = 135.68;
	keys[5] = 461;
	keys[6] = 4156.2;
	keys[7] = 1654.21;
	keys[8] = 5461.645;
	keys[9] = 48914;



	hash.Insert(keys[0], 25.4);
	hash.Insert(keys[1], 27.512);
	hash.Insert(keys[2], 29.23);
	hash.Insert(keys[3], 29.23);
	hash.Insert(keys[4], 12);
	hash.Insert(keys[5], 13);
	hash.Insert(keys[6], 14);
	hash.Insert(keys[7], 15);
	hash.Insert(keys[8], 16);
	hash.Insert(keys[9], 17);

	hash.Insert(333.333, 32.2);
	hash.Insert(222.222, 11.111);

	HashDataType data;

	hash.ShowHashTable();
	std::cout << '\n';

	hash.Delete(461);

	// Print if data is not found
	if (!hash.Find(461))
	{
		std::cout << "Fstring has not found in hashTable\n";
	}

	if (!hash.Find(keys[5]))
	{
		std::cout << keys[5] << " has not found in hashTable\n";
	}

	if (!hash.Find(keys[8], &data))
	{
		std::cout << "Istring has not found in hashTable\n";
	}

	hash.Delete(keys[6]);

	hash.ShowHashTable();
	std::cout << '\n';
#endif	// TESTING_DOUBLE_FLOAT

#endif	// HASH_TABLE


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Test from passed assignment


	// WIDGET TEST
#if WIDGET

	// SETTINGS


	const bool ascending = ASCENDING;

	const ArraySize size = SIZE;

	Widget<DataType> pArray[size];

	for (size_t i = 0; i < 100; ++i)
	{
		//SortingWidgets<Widget<DataType>, DataType, size>(pArray, ascending);
		// Random Set Widget
		SetRandomizeNumbers<Widget<DataType>,DataType>(pArray, size, range);

		// Counting Sort Widget.ver
		WidgetCountingSort<Widget<DataType>, DataType>(pArray, size, ascending);

		// Check if it's sorted
		CheckSorted<Widget<DataType>, DataType>(pArray, size, ascending);

	}
#endif

	// LINKED_LIST TEST
#if LINKED_LIST

	LinkedList<DataType> linkedList;


	for (size_t j = 0; j < 1; ++j)
	{
		// Inserting Test
		for (size_t i = 0; i < 10; ++i)
		{
			size_t randIndex = rand() % range;
			DataType randValue = rand() % range + 97;

			std::cout << randValue << " => Insert to Index[" << randIndex << "]\n\n";
			linkedList.Insert(randValue, randIndex);

			// Print
			//linkedList.Print();

		}
		linkedList.Print();

		LinkedList<DataType>::Iterator iter = linkedList.Begin();
		for (iter; iter != linkedList.End(); ++iter)
		{
			std::cout << (*iter)->m_data << std::endl;
			
		}

		std::cout << std::endl;
		iter = linkedList.Begin();
		for (iter = linkedList.Begin(); iter != linkedList.End(); ++iter)
		{
			(*iter)->m_data;
		}
		linkedList.Print();

		//iter = linkedList.Begin();
		//for (iter; iter != linkedList.End(); ++iter)
		//{
		//	std::cout << iter.data;
		//}

		// Delete Test
		for (size_t i = 0; i < 10; ++i)
		{
			DataType randValue = rand() % range + 97;

			std::cout << "Delete [" << randValue << "]\n\n";
			linkedList.Delete(randValue);
		}

		linkedList.Print();
		linkedList.Clear();

		// Push Back & Push Front Test
		for (size_t i = 0; i < 10; ++i)
		{
			DataType randValueA = rand() % range + 97;
			DataType randValueB = rand() % range + 97;

			linkedList.Push_Back(randValueA);
			linkedList.Push_Front(randValueB);
		}

		linkedList.Print();

		// Pop_Back Test
		for (size_t i = 0; i < 10; ++i)
		{
			linkedList.Pop_Front();
		}

		linkedList.Print();


		// Push_Back Test
		for (size_t i = 0; i < 10; ++i)
		{
			linkedList.Pop_Back();
		}



		linkedList.Print();


		// Clean List
		linkedList.Clear();

	}

#endif

	return 0;
}

#pragma endregion