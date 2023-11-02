#pragma once
#include "LinkedList.h"
#include "FNV.h"

#define HASH_SIZE	1000
#define HASH_MAX	1001

using namespace FNV;

template<typename KeyType, typename HashDataType>
class HashTable
{
	// Store key and data
	struct HashInfo
	{
		KeyType m_key;
		HashDataType m_data;

		bool operator==(const HashInfo& other) const
		{
			return (m_key == other.m_key && m_data == other.m_data);
		}
		bool operator!=(const HashInfo& other) const
		{
			return (m_key != other.m_key || m_data != other.m_data);
		}
	};


private:
	// default hash size
	static const size_t s_kHashSize = HASH_SIZE;

	size_t m_hashSize;
	LinkedList<HashInfo>* m_pTable;


public:
	// Constructor
	HashTable(const size_t hashSize = s_kHashSize)
		: m_hashSize(hashSize)
	{
		assert(m_hashSize > 0 && m_hashSize < (size_t)HASH_MAX);

		m_pTable = new LinkedList<HashInfo>[s_kHashSize];
	}
	// Destructor
	~HashTable()
	{
		if (m_pTable != nullptr)
		{
			delete[] m_pTable;
		}
	}

	void Insert(KeyType key, HashDataType data)
	{
		uint_32 hash;
		HashInfo hInfo;


		hInfo.m_data = data;
		hInfo.m_key = key;


		hash = HashFuction(key);

		size_t size = m_pTable[hash].GetSize();

		// Check if same key have inserted before
		for (size_t i = 0; i < size; ++i)
		{
			if (Find(key))
			{
				std::cout << "[HashTable] INSERTION FAIL: Same Key has already Saved in hash Table\n";
				return;
			}
		}

		m_pTable[hash].Push_Back(hInfo);

	}

	void Delete(KeyType key)
	{
		uint_32 hash;
		hash = HashFuction(key);

		size_t size = m_pTable[hash].GetSize();

		// Iterator
		for (size_t i = 0; i < size; ++i)
		{
			HashInfo searchDataInHash = m_pTable[hash][i]->m_data;

			// Found inside the table
			if (searchDataInHash.m_key == key)
			{
				m_pTable[hash].Delete(searchDataInHash);
				return;
			}
		}

		std::cout << "[HashTable] DELETION FAIL: [" << key << "] Not Found\n";
		return;
	}

	bool Find(KeyType key, HashDataType* obj = nullptr)
	{
		uint_32 hash;
		hash = HashFuction(key);

		size_t size = m_pTable[hash].GetSize();

		// Iterator
		for (size_t i = 0; i < size; ++i)
		{
			// Found inside the table
			if (m_pTable[hash][i]->m_data.m_key == key)
			{
				// Save in pointer if there are given data pointer
				if(obj != nullptr)
					*obj = m_pTable[hash][i]->m_data.m_data;

				return true;
			}
		}

		// Key has not found in hashtable
		return false;
	}

	// Hashing Algorithm using fav-1a
	uint_32 HashFuction(KeyType key)
	{
		size_t size = sizeof(key);

		uint_32 hash;

		hash = FNV::Fnv_1a(&key) % m_hashSize;

		return hash;
	}


	void ShowHashTable()
	{
		for (size_t j = 0; j < m_hashSize; ++j)
		{
			if (m_pTable[j].Begin() != nullptr)
			{
				std::cout << "HashTable[" << j << "]: ";
				size_t searchingHashSize = m_pTable[j].GetSize();
				for (size_t i = 0; i < searchingHashSize; ++i)
				{
					std::cout << "\t==> Key<" << m_pTable[j][i]->m_data.m_key << "> Data[" << m_pTable[j][i]->m_data.m_data << "]";
				}
				std::cout << '\n';
			}
		}
	}

};

