#include "LinkedList.h"
#include <iostream>
#include <assert.h>


LinkedList::Node* LinkedList::FindNode(int dataToFind)
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
		if (pIterator->data == dataToFind)
		{
			return pIterator;
		}
		// iter++
		pIterator = pIterator->m_pNext;
	}

	std::cout << "Data: " << dataToFind << " Not found! \n";

	return nullptr;
}

void LinkedList::Push_Front(int data)
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

void LinkedList::Push_Back(int data)
{
	Node* newNode = new Node(data);

	// newNode->prevNode = current tail
	newNode->m_pPrev = m_pTail;

	// if node is empty
	if (m_pHead == nullptr || m_pTail == nullptr)
	{
		m_pHead = newNode;
		m_pTail = newNode;
		return;
	}

	// Set newNode->prev = current tail
	newNode->m_pPrev = m_pTail;

	m_pTail->m_pNext = newNode;
	m_pTail = newNode;

	// Add size
	++m_size;

}

// I made it to find the middle and started from either back or front but 
// but this wouldn't be too necessary since O(n / 2) is still O(n)
void LinkedList::Insert(int data, size_t position)
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

	// Insert on middle
	newNode->m_pPrev = pIterator->m_pPrev;
	newNode->m_pNext = pIterator;

	pIterator->m_pPrev->m_pNext = newNode;
	pIterator->m_pPrev = newNode;

	// Add size
	++m_size;
}



void LinkedList::Delete(int data)
{

	Node* pNodeToDelete = FindNode(data);

	// if data doen't exist
	if (pNodeToDelete == nullptr)
		return;

	// data is not head
	if (pNodeToDelete->m_pPrev != nullptr)
	{
		pNodeToDelete->m_pPrev->m_pNext = pNodeToDelete->m_pNext;
	}
	else
		m_pHead = pNodeToDelete->m_pNext;
	// data is not tail
	if (pNodeToDelete->m_pNext != nullptr)
	{
		pNodeToDelete->m_pNext->m_pPrev = pNodeToDelete->m_pPrev;
	}
	else
		m_pTail = pNodeToDelete->m_pPrev;

	pNodeToDelete->clear();
	delete pNodeToDelete;
	--m_size;

}


void LinkedList::Clear()
{
	if (m_pHead != nullptr)
	{
		Node* pIterator = m_pHead;
		// looping through and delete from head
		while (m_pHead)
		{
			m_pHead = pIterator->m_pNext;
			pIterator->clear();
			delete pIterator;
			pIterator = m_pHead;
		}

		// reset value for tail and size
		m_pTail = nullptr;
		m_size = 0;
	}
}


// Print Linked List
void LinkedList::Print()
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
		std::cout << "[" << pIterator->data << "] ";
		pIterator = pIterator->m_pNext;
	}

	std::cout << '\n' << '\n';
	std::cout << "Head: " << m_pHead->data << std::endl;
	std::cout << "Tail: " << m_pTail->data << std::endl;


	std::cout << "\n===================================================\n";

}

void LinkedList::Node::clear()
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
}
