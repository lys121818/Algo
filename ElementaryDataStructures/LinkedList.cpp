#include "LinkedList.h"
#include <iostream>

//Node* LinkedList::FindNode(int dataToFind)
LinkedList::Node* LinkedList::FindNode(int DataToFind)
{
	if (m_pHead == nullptr)
	{
		
		return nullptr;
	}

	Node* pIterator = m_pHead;

	while (pIterator)
	{
		if (pIterator->data == DataToFind)
		{
			return pIterator;
		}
		pIterator = pIterator->m_pNext;
	}

	std::cout << "Data: " << DataToFind << " Not found! \n";

	return nullptr;
}

void LinkedList::Push_Front(int data)
{
	// Create new node
	Node* newNode = new Node(data);

	newNode->m_pNext = m_pHead;

	if(m_pHead != nullptr)
		m_pHead->m_pPrev = newNode;

	m_pHead = newNode;

}

void LinkedList::Push_Back(int data)
{
	Node* newNode = new Node(data);

	if (m_pHead == nullptr)
	{
		m_pHead = newNode;
		return;
	}

	Node* pIterator = m_pHead;
	while (pIterator)
	{
		if (pIterator->m_pNext == nullptr)
			newNode->m_pPrev = pIterator;
		pIterator = pIterator->m_pNext;
	}

	pIterator = newNode;
	pIterator->m_pPrev->m_pNext = newNode;

}

void LinkedList::Insert(int data, size_t position)
{
	size_t index = 0;
	Node* newNode = new Node(data);


	if (m_pHead == nullptr)
	{
		if (position != 0)
		{
			std::cout << "The size of list is smaller than the position \n";
			std::cout << "The data has stored in end of the list \n";
			std::cout << "Inserted on: " << index << std::endl;
		}

		m_pHead = newNode;
		return;
	}

	Node* pIterator = m_pHead;
	while (pIterator && index < position)
	{
		if (pIterator->m_pNext == nullptr)
			newNode->m_pPrev = pIterator;
		pIterator = pIterator->m_pNext;
		++index;
	}

	// size is smaller than position to insert
	if (index < position)
	{
		std::cout << "The size of list is smaller than the position \n";
		std::cout << "The data has stored in end of the list \n";
		std::cout << "Inserted on: " << index << std::endl;
		pIterator = newNode;
		pIterator->m_pPrev->m_pNext = newNode;
	}
	else
	{
		// last index
		if (pIterator == nullptr)
		{
			pIterator = newNode;
			pIterator->m_pPrev->m_pNext = newNode;
		}
		// first index
		else if (pIterator->m_pPrev == nullptr)
		{
			newNode->m_pNext = pIterator;
			pIterator->m_pPrev = newNode;
			m_pHead = newNode;
		}
		else
		{
			// new node setting

			newNode->m_pPrev = pIterator->m_pPrev;
			newNode->m_pNext = pIterator;

			pIterator->m_pPrev->m_pNext = newNode;
			pIterator->m_pPrev = newNode;
		}
	}

}



void LinkedList::Delete(int data)
{

	Node* pNodeToDelete = FindNode(data);

	if (pNodeToDelete != nullptr)
	{
		if (pNodeToDelete->m_pPrev != nullptr)
		{
			pNodeToDelete->m_pPrev->m_pNext = pNodeToDelete->m_pNext;
		}
		else
			m_pHead = pNodeToDelete->m_pNext;
		if (pNodeToDelete->m_pNext != nullptr)
		{
			pNodeToDelete->m_pNext->m_pPrev = pNodeToDelete->m_pPrev;
		}
		pNodeToDelete->clear();
		delete pNodeToDelete;
	}

}

void LinkedList::Print()
{
	Node* pIterator = m_pHead;

	while (pIterator)
	{
		std::cout << pIterator->data << " \n";
		pIterator = pIterator->m_pNext;
	}
}

void LinkedList::Node::clear()
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
}
