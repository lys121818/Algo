#pragma once
#include <iostream>
#include <assert.h>


template <typename Value>
class LinkedList
{
private:

	struct Node
	{
	public:
		Value m_data;

		Node* m_pNext = nullptr;
		Node* m_pPrev = nullptr;

		Node(Value data) : m_data(data) {}
		~Node() { delete m_pNext; m_pNext = m_pPrev = nullptr; }


		void ClearNode()
		{
			m_pNext = nullptr;
			m_pPrev = nullptr;
		}


	};

public:
	class Iterator
	{
		friend class LinkedList;

	private:
		Node* m_pNode = nullptr;

	public:
		Iterator() = default;
		Iterator(Node* pNode)
			: m_pNode(pNode)
		{}
		

		// OPERATORS
		bool operator==(const Iterator& pOther) const { return m_pNode == pOther.m_pNode; }
		bool operator!=(const Iterator& pOther) const { return m_pNode != pOther.m_pNode; }

		void operator++() { m_pNode = m_pNode->m_pNext; }
		void operator--() { m_pNode = m_pNode->m_pPrev; }

		Node* operator*() { return m_pNode; }
		

	};

	Node* operator[](const size_t& index)
	{


		// the size of list is smaller than index
		assert(m_size > index);

		Iterator iter = m_pHead;
		for (size_t i = 0; i < index; ++i)
		{
			++iter;
		}

		return (*iter);
	}


public:
	LinkedList() = default;
	~LinkedList() { delete m_pHead, m_pTail; }

	void Insert(Value data, size_t position);

	void Push_Front(Value data);

	void Push_Back(Value data);

	void Pop_Back();
	void Pop_Front();

	void Clear();
	void Delete(Value data);
	void Print();

	Iterator begin() { return m_pHead; }
	Iterator end() { return m_pTail->m_pNext; }

private:

	Node* m_pHead = nullptr;
	Node* m_pTail = nullptr;

	size_t m_size = 0;


	/// <summary>
	/// Template functions
	//////////////////////////////////////////////////

public:


private:
	Node* FindNode(Value dataToFind)
	{
		// If there are no nodes in list
		if (m_pHead == nullptr)
		{
			return nullptr;
		}

		Node* pIterator = m_pHead;

		// Until end
		while (pIterator)
		{
			// FOUND
			if (pIterator->m_data == dataToFind)
			{
				return pIterator;
			}
			// iter++
			pIterator = pIterator->m_pNext;
		}

		std::cout << "Data: " << dataToFind << " Not found! \n";

		return nullptr;
	}



};


template <typename Value>
void LinkedList<Value>::Insert(Value data, size_t position)
{
	Node* newNode = new Node(data);
	size_t index;
	bool isCloseToHead;

	// if list is empty
	// or insert to first array
	if (m_pHead == nullptr || position == 0)
	{
		if (position != 0)
		{
			std::cout << "WARRNING: The array is Empty \n";
			std::cout << "\t  Inserted on index: " << m_size << "\n\n";

		}

		// Inser to head
		Push_Front(data);
		return;
	}

	// if position is bigger than current list size
	// or end of the list
	if (position >= m_size)
	{
		if (m_size != position)
		{
			std::cout << "WARRNING: Inser Index is too big \n";
			std::cout << "\t  Inserted on index: " << m_size << "\n\n";
		}

		// Insert to tail
		Push_Back(data);
		return;
	}

	Node* pIterator;


	// if position is lower half part of the linked list
	if (position <= (m_size / 2))
	{
		// Setting Iterator
		pIterator = m_pHead;
		isCloseToHead = true;
		index = 0;

		// looping Head -> Tail
		while (index < position)
		{
			pIterator = pIterator->m_pNext;
			++index;
		}
	}
	// if position is upper half part of the linked list
	else
	{
		// Setting Iterator
		pIterator = m_pTail;
		isCloseToHead = false;
		index = m_size - 1;

		// looping Tail -> Head
		while (index > position)
		{
			pIterator = pIterator->m_pPrev;
			--index;
		}
	}

	// Inserting to position
	newNode->m_pPrev = pIterator->m_pPrev;
	newNode->m_pNext = pIterator;

	pIterator->m_pPrev->m_pNext = newNode;
	pIterator->m_pPrev = newNode;

	// Add size
	++m_size;
}


// I made it to find the middle and started from either back or front but 
// but this wouldn't be too necessary since O(n / 2) is still O(n)

template <typename Value>
void LinkedList<Value>::Push_Front(Value data)
{
	// Create new node
	Node* newNode = new Node(data);

	// newNode->nextNode = current head
	newNode->m_pNext = m_pHead;

	// If list is not empty
	if (m_pHead != nullptr)
	{
		// Current head -> prevNode = newNode
		m_pHead->m_pPrev = newNode;
	}
	// Set newNode to head
	m_pHead = newNode;

	// if list was empty
	if (m_pTail == nullptr)
		m_pTail = newNode;

	// Add size
	++m_size;
}

template <typename Value>
void LinkedList<Value>::Push_Back(Value data)
{
	Node* newNode = new Node(data);

	// newNode->prevNode = current tail
	newNode->m_pPrev = m_pTail;

	// if node is empty
	if (m_pHead == nullptr || m_pTail == nullptr)
	{
		m_pHead = newNode;
		m_pTail = newNode;
		++m_size;
		return;
	}

	// Set newNode->prev = current tail
	newNode->m_pPrev = m_pTail;

	m_pTail->m_pNext = newNode;
	m_pTail = newNode;

	// Add size
	++m_size;
}

template <typename Value>
void LinkedList<Value>::Delete(Value data)
{

	Node* pNodeToDelete = FindNode(data);

	// if data doen't exist
	if (pNodeToDelete == nullptr)
		return;

	// Setting Prev node
	// data is not head
	if (pNodeToDelete->m_pPrev != nullptr)
	{
		pNodeToDelete->m_pPrev->m_pNext = pNodeToDelete->m_pNext;
	}
	else
		m_pHead = pNodeToDelete->m_pNext;

	// Setting next node
	// data is not tail
	if (pNodeToDelete->m_pNext != nullptr)
	{
		pNodeToDelete->m_pNext->m_pPrev = pNodeToDelete->m_pPrev;
	}
	else
		m_pTail = pNodeToDelete->m_pPrev;

	pNodeToDelete->ClearNode();
	delete pNodeToDelete;

	// decrease size
	--m_size;

}


// delete from tail
template <typename Value>
void LinkedList<Value>::Pop_Back()
{
	if (m_pHead == nullptr)
	{
		std::cout << "Nothing inside the list";
		return;
	}
	Node* pNodeToDelete = m_pTail;

	// Set Tail Node
	m_pTail = pNodeToDelete->m_pPrev;

	// Array is empty
	if (m_pTail == nullptr)
	{
		m_pHead = nullptr;
	}
	else
	{
		// Set Tail Node
		m_pTail->m_pNext = nullptr;
	}

	pNodeToDelete->ClearNode();
	delete pNodeToDelete;

	// decrease size
	--m_size;
}

// delete from head
template <typename Value>
void LinkedList<Value>::Pop_Front()
{
	if (m_pHead == nullptr)
	{
		std::cout << "Nothing inside the list";
		return;
	}

	Node* pNodeToDelete = m_pHead;

	// Set Head Node;
	m_pHead = pNodeToDelete->m_pNext;

	// Array is empty
	if (m_pHead == nullptr)
	{
		m_pTail = nullptr;
	}
	else
	{
		// Set Tail Node
		m_pHead->m_pPrev = nullptr;
	}

	// Delete
	pNodeToDelete->ClearNode();
	delete pNodeToDelete;

	// decrease size
	--m_size;
}






template <typename Value>
void LinkedList<Value>::Clear()
{
	if (m_pHead != nullptr)
	{
		Node* pIterator = m_pHead;
		// looping through and delete from head
		while (m_pHead)
		{
			m_pHead = pIterator->m_pNext;
			pIterator->ClearNode();
			delete pIterator;
			pIterator = m_pHead;
		}

		// reset value for tail and size
		m_pTail = nullptr;
		m_size = 0;
	}
}


// Print Linked List
template <typename Value>
void LinkedList<Value>::Print()
{
	Node* pIterator = m_pHead;
	size_t index = 0;

	if (m_pHead == nullptr)
	{
		std::cout << "No Array Found\n\n";
		std::cout << "\n===================================================\n";
		return;
	}

	std::cout << "Size: " << m_size << std::endl;

	std::cout << "Index: ";
	while (pIterator)
	{
		std::cout << "[" << index << "] ";
		pIterator = pIterator->m_pNext;
		++index;
	}

	std::cout << '\n';
	pIterator = m_pHead;
	std::cout << "Array: ";
	while (pIterator)
	{
		std::cout << "[" << pIterator->m_data << "] ";
		pIterator = pIterator->m_pNext;
	}

	std::cout << '\n' << '\n';
	std::cout << "Head: " << m_pHead->m_data << std::endl;
	std::cout << "Tail: " << m_pTail->m_data << std::endl;


	std::cout << "\n===================================================\n";

}
