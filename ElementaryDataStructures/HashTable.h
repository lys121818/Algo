#pragma once
#include "LinkedList.h"
#include "FNV.h"

#define HASH_SIZE 1000

using namespace FNV;

template<typename DataType>
class HashTable
{
	static const size_t s_khashSize = HASH_SIZE;

private:
	size_t m_hashSize = s_khashSize;
	LinkedList<DataType>* m_pTable;

	int m_totalItem;
	int m_size;

public:
	template<typename DataType>
	HashTable(const size_t hashSize = s_khashSize)
		: m_hashSize(hashSize)
	{
		m_pTable = new LinkedList<DataType>[m_hashSize];
	}
	~HashTable()
	{
	}



private:
	bool isNumPrime(int val)
	{
		for (int i = 2; (i * i) < val; ++i)
		{
			if ((val % i) == 0)
				return false;
		}
		return true;
	}

	int GetNextPrimeNum(int val)
	{
		int i;
		for (i = val + 1;; ++i)
		{
			if (isNumPrime(i))
				break;
		}
		return i;
	}

public:
	bool Insert(int key, const DataType& obj)
	{

		int hash = HashFunction(key);
		int step = StepHashFunction(key);

		std::cout << "Try and insert " << obj << " at hash index: " << hash <<
			" with step of " << step << std::endl;

		// Look for an empty cell
		while (m_pTable[hash].GetKey() != -1)
		{
			hash += step;
			hash %= m_size;
		}

		m_pTable[hash].SetKey(key);
		m_pTable[hash].SetObj(obj);

		std::cout << "	Actually insert " << obj << " at hash index: " << hash << "\n\n";

		m_totalItem++;

		return true;
	}

	void Delete(int key)
	{
		int hash = HashFunction(key);
		int step = StepHashFunction(key);

		int orginalHash = hash;

		while (m_pTable[hash].GetKey() != -1)
		{
			if (m_pTable[hash].GetKey() == key)
			{
				// Succesfully delete the entry
				m_pTable[hash].SetKey(-1);
				m_totalItem--;
				return;
			}

			hash += step;
			hash %= m_size;

			// Can't find entry
			if (orginalHash == hash)
				return;
		}
	}

	bool Find(int key, DataType* obj)
	{
		int hash = HashFunction(key);
		int step = StepHashFunction(key);

		int originalHash = hash;

		while (m_pTable[hash].GetKey() != -1)
		{
			if (m_pTable[hash].GetKey() == key)
			{
				if (obj != nullptr)
					*obj = m_pTable[hash].GetObject();
				return true;
			}

			hash += step;
			hash %= m_size;

			if (originalHash == hash)
				return false;
		}
		return false;
	}

	int StepHashFunction(int key)
	{
		return 4 - key % 4;
	}

	int HashFunction(int key)
	{
		return key % m_size;
	}

	int HashFunction(std::string& str)
	{
		int hash = 0;
		for (int i = 0; i < (int)str.size(); ++i)
		{
			int val = (int)str[i];
			hash = (hash & 256 + val) % m_size;
		}
		return hash;
	}

	int GetSize()
	{
		return m_size;
	}


};

