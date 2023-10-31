#pragma once
#include "LinkedList.h"

#define HASH_SIZE 1000

template<typename DataType>
class HashTable
{
	static const size_t s_khashSize = HASH_SIZE;

private:
	size_t m_hashSize = s_khashSize;
	LinkedList<DataType>* m_table;

public:
	template<typename DataType>
	HashTable(const size_t hashSize = s_khashSize)
		: m_hashSize(hashSize)
	{
		m_table = new LinkedList<DataType>[m_hashSize];
	}
	~HashTable();


};

