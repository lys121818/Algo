#pragma once
#include <assert.h>
#include <iostream>

// Debug mode to see visual changes
#define _DEBUG 1

template<typename DataType>
class Priority_Queue
{
private:
	struct Node
	{
	public:
		size_t m_key;
		DataType m_value;

		Node* m_pParent = nullptr;
		Node* m_pLeft = nullptr;
		Node* m_pRight = nullptr;

		Node(size_t key, DataType data) : m_key(key), m_value(data) {}
		~Node() 
		{ 
			// root
			if (m_key == 1)
				return;

			//left
			if (m_key % 2 == 0)
				m_pParent->m_pLeft = nullptr;
			//right
			else
				m_pParent->m_pRight = nullptr;

			m_pParent = m_pLeft = m_pRight = nullptr; 
		}

		// Compare values
		bool operator < (const Node& other) const
		{
			if (this->m_value < other.m_value) return true; 
			else return false; 
		}
		bool operator > (const Node& other) const { return (other < *this); }
	};

private:
	Node* m_pRoot = nullptr;

	size_t m_size = 0;

	DataType m_maxElement;

public:


	class Iterator
	{
		friend class Priority_Queue;

	private:
		Node* m_pNode = nullptr;

	public:
		Iterator() = default;
		Iterator(Node* pNode)
			: m_pNode(pNode)
		{}

		// Move to Next Node
		void Parent() { m_pNode = m_pNode->m_pParent; }
		void Left() { m_pNode = m_pNode->m_pLeft; }
		void Right() { m_pNode = m_pNode->m_pRight; }

		Node* GetNode() { return m_pNode; }
	};

public:
	Priority_Queue() = default;
	~Priority_Queue() { Clear(m_pRoot); delete m_pRoot; }

	// Inset data into queue
	void Push(DataType data);

	void Delete(size_t key);

	void Print();
private:

	// print visualized tree in recursive
	void Print(Node* pNode, int merge);

	// delete all the child node in recursive
	void Clear(Node* pNode);

#if _DEBUG
	void DebugPrint(Node* pNode_a = nullptr, Node* pNode_b = nullptr);
#endif

	size_t Parent(size_t index) const { return index / 2; }
	size_t Left(size_t index) const { return index * 2; }
	size_t Right(size_t index) const { return index * 2 + 1; }

	Node* GetIndexNode(const size_t& index)
	{
		// index should be always smaller than the max size
		assert(index < m_size && m_pRoot != nullptr);

		Iterator iter = m_pRoot;
		while (iter.GetNode()->m_key != index)
		{
			size_t nextIndex = index;

			size_t leftChildKey = iter.GetNode()->m_pLeft->m_key;
			size_t rightChildKey = iter.GetNode()->m_pRight->m_key;

			// devide in half until index is lower than current nodes biggest child
			while (nextIndex > rightChildKey)
			{
				nextIndex /= 2;
			}

			// nextIndex's key is same value with either left child or right child's key
			assert(nextIndex == leftChildKey || nextIndex == rightChildKey);

			// Move to next index
			if (nextIndex == leftChildKey)
				iter.Left();
			else
				iter.Right();
		}
		return iter.GetNode();
	}

	void SwapValues(Node* pNode_a, Node* pNode_b);
	void SortOnDown(Node* pNode);
	void SortOnUp(Node* pNode);

	Node* Find(const size_t& index)
	{
		// index should be always smaller than the max size
		assert(index <= m_size && m_pRoot != nullptr);

		Iterator iter = m_pRoot;

		// Until find the index
		while (iter.GetNode()->m_key != index)
		{
			size_t nextIndex = index;

			// if left or right is nullptr (reach the last element)
			if (iter.GetNode()->m_pRight == nullptr)
			{
				iter.Left();
				break;
			}
			// left always exist
			else
				assert(iter.GetNode()->m_pLeft != nullptr);

			

			size_t leftChildKey = iter.GetNode()->m_pLeft->m_key;
			size_t rightChildKey = iter.GetNode()->m_pRight->m_key;

			// devide in half until index is lower than current nodes biggest child
			while (nextIndex > rightChildKey)
			{
				nextIndex /= 2;
			}

			// nextIndex's key is same value with either left child or right child's key
			assert(nextIndex == leftChildKey || nextIndex == rightChildKey);

			if (nextIndex == leftChildKey)
				iter.Left();
			else
				iter.Right();

		}
		return iter.GetNode();
	}


};

template<typename DataType>
void Priority_Queue<DataType>::Push(DataType data)
{
	++m_size; 
	
	// node to insert
	Node* newNode = new Node(m_size, data);

	// if Queue is empty
	if (m_size == 1)
	{

		m_pRoot = newNode;
		m_maxElement = newNode->m_value;

#if _DEBUG
		DebugPrint(newNode);
#endif // DEBUG
		return;
	}


	// connect with parent
	size_t parentIndex = Parent(m_size);
	Node* parentNode = GetIndexNode(parentIndex);
	newNode->m_pParent = parentNode;

	// if it's even: left child / odd: right child
	if (m_size % 2 == 0)
		parentNode->m_pLeft = newNode;
	else
		parentNode->m_pRight = newNode;

#if _DEBUG
	DebugPrint(newNode);
#endif // DEBUG

	// Sort in order
	SortOnUp(newNode);

	// Set max element
	m_maxElement = m_pRoot->m_value;


}

template<typename DataType>
inline void Priority_Queue<DataType>::Delete(size_t key)
{
	// key should be always bigger than max size
	assert(key <= m_size);

	/*
	 	On this function pDeleteNode is actually deleting values 
		but after sorting is done pLastIndexNode is one actaully being deleted
	*/

	Node* pDeleteNode = Find(key);
	Node* pLastIndexNode = Find(m_size);

#if _DEBUG

	system("cls");
	std::cout << "Deleting Node[" << key << "]" << pDeleteNode->m_value << "\n\n";
	Print();
	system("pause");

#endif // DEBUG

	// set value to biggest
	pDeleteNode->m_value = m_maxElement;

#if _DEBUG

	system("cls");
	std::cout << "Change Value to maxElement Node[" << key << "]" << pDeleteNode->m_value << "\n\n";
	Print();
	system("pause");

#endif // DEBUG

	// sorting on the way to the root
	SortOnUp(pDeleteNode);

	// Swap
	SwapValues(m_pRoot, pLastIndexNode);

	// delete last element
	delete pLastIndexNode;

	pLastIndexNode = nullptr;

#if _DEBUG
	DebugPrint();
#endif // DEBUG

	--m_size;
	
	// sort down after moved last element to root
	SortOnDown(m_pRoot);

	// Set max element
	m_maxElement = m_pRoot->m_value;
}

template<typename DataType>
inline void Priority_Queue<DataType>::Print()
{
	Print(m_pRoot,0);
	std::cout << "\n\n";
}

template<typename DataType>
inline void Priority_Queue<DataType>::Print(Node* pNode, int merge)
{
	merge += m_size;

	if (pNode == nullptr)
		return;

	// Move to right end node
	Print(pNode->m_pRight, merge);

	std::cout << "\n";

	for (int i = m_size; i < merge; ++i)
		std::cout << " ";
	std::cout << "[" << pNode->m_key << "]" << pNode->m_value;

	Print(pNode->m_pLeft, merge);

}

template<typename DataType>
inline void Priority_Queue<DataType>::Clear(Node* pNode)
{
	if (pNode == nullptr)
		return;

	// Move to very left node
	Clear(pNode->m_pLeft);

	// delete child
	if (pNode->m_pLeft)
		delete pNode->m_pLeft;
	else if (pNode->m_pRight)
		delete pNode->m_pRight;

	// Move to right node
	Clear(pNode->m_pRight);

}

template<typename DataType>
inline void Priority_Queue<DataType>::SwapValues(Node* pNode_a, Node* pNode_b)
{
	// Swap values
	DataType temp = pNode_a->m_value;
	pNode_a->m_value = pNode_b->m_value;
	pNode_b->m_value = temp;

#if _DEBUG
	DebugPrint(pNode_a, pNode_b);
#endif // DEBUG
}

template<typename DataType>
inline void Priority_Queue<DataType>::SortOnDown(Node* pNode)
{
	Iterator iter = pNode;
	
	// Until there are no child on right (no more to go down)
	while (iter.GetNode()->m_pRight != nullptr)
	{
		// when left child is bigger
		if (*iter.GetNode()->m_pLeft > *iter.GetNode())
		{
			// when left child is bigger than right child
			if (*iter.GetNode()->m_pLeft > *iter.GetNode()->m_pRight)
			{
				SwapValues(iter.GetNode()->m_pLeft, iter.GetNode());
				iter.Left();
			}
			// when right child is bigger than left child
			else
			{
				SwapValues(iter.GetNode()->m_pRight, iter.GetNode());
				iter.Right();
			}
		}
		// when right child is bigger
		else if (*iter.GetNode()->m_pRight > *iter.GetNode())
		{
			SwapValues(iter.GetNode()->m_pRight, iter.GetNode());
			iter.Right();
		}
		// done sorting
		else
			break;
	}

}

template<typename DataType>
inline void Priority_Queue<DataType>::SortOnUp(Node* pNode)
{
	Iterator iter = pNode;

	// Until it reachs the root
	while (iter.GetNode()->m_pParent != nullptr)
	{
		// if the value is bigger than parents value
		if (*iter.GetNode() > *iter.GetNode()->m_pParent)
			SwapValues(iter.GetNode(), iter.GetNode()->m_pParent);
		else
			break;

		iter.Parent();
	}
}

#if _DEBUG
template<typename DataType>
inline void Priority_Queue<DataType>::DebugPrint(Node* pNode_a, Node* pNode_b)
{
	system("cls");


	if (pNode_b)
	{
		std::cout << "Node Change [" << pNode_a->m_key << "] "<< pNode_a->m_value << "   <--->   " << "[" << pNode_b->m_key << "]" << pNode_b->m_value << "\n\n";
	}
	else if(pNode_a)
	{
		std::cout << "Node Insert [" << pNode_a->m_key << "] " << pNode_a->m_value << "\n\n";
	}
	else
	{
		std::cout << "Delete last node [" << m_size << "]\n\n";
	}

	Print();
	system("pause");

}

#endif // DEBUG
