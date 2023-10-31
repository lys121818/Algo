#pragma once
#include "HashItem.h"


template<typename DataType>
class HashTableExample
{
public:
	HashTableExample(size_t size)
		: m_size(0),
		  m_totalItem(0)
	{
		m_size = GetNextPrimeNum(size);
		m_pTable = new HashItem<DataType>[m_size];

		std::cout << "Desired size of table: " << size << std::endl;
		std::cout << "Actual size of table: " << m_size << std::endl;
	}
	~HashTableExample()
	{
		if (m_pTable != nullptr)
		{
			delete[] m_pTable;
			m_pTable = nullptr;
		}
	}
private:
	size_t m_size;
	size_t m_totalItem;

	HashItem<DataType>* m_pTable;

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
	bool Insert(int key,const DataType& obj)
	{
		if (m_totalItem == m_size)
			return false;

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