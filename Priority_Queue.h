#pragma once
#include <assert.h>
#include <iostream>
#include <queue>

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
			if (m_key % 2 == 0)
				m_pParent->m_pLeft = nullptr;
			else
				m_pParent->m_pRight = nullptr;

			m_pParent = m_pLeft = m_pRight = nullptr; 
		}

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

	std::queue<Node*> m_pQueue;
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

		size_t GetKey() { return m_pNode->m_key; }

		// return node
		Node* operator*() { return m_pNode; }

	};

public:
	Priority_Queue() = default;
	~Priority_Queue() {};

	// Inset data into queue
	void Push(DataType data);

	void Delete(size_t key);
private:
	size_t Parent(size_t index) const { return index / 2; }
	size_t Left(size_t index) const { return index * 2; }
	size_t Right(size_t index) const { return index * 2 + 1; }

	Node* GetIndexNode(const size_t& index)
	{
		// index should be always smaller than the max size
		assert(index < m_size && m_pRoot != nullptr);

		Iterator iter = m_pRoot;
		while (iter.GetKey() != index)
		{
			size_t nextIndex = index;

			size_t leftChildKey = Priority_Queue<DataType>::Left(iter.GetKey());
			size_t rightChildKey = Priority_Queue<DataType>::Right(iter.GetKey());

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
		return *iter;
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
		while (iter.GetKey() != index)
		{
			size_t nextIndex = index;

			// if left or right is nullptr (reach the last element)
			if ((*iter)->m_pRight == nullptr)
			{
				iter.Left();
				break;
			}
			// left always exist
			else
				assert((*iter)->m_pLeft != nullptr);

			

			size_t leftChildKey = (*iter)->m_pLeft->m_key;
			size_t rightChildKey = (*iter)->m_pRight->m_key;

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
		return *iter;
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
		m_pQueue.push(newNode);
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

	m_pQueue.push(newNode);

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
		Maybe better name for this?
	*/
	Node* pDeleteNode = Find(key);
	Node* pLastIndexNode = Find(m_size);

	// set value to biggest
	pDeleteNode->m_value = ++m_maxElement;

	// sorting on the way to the root
	SortOnUp(pDeleteNode);

	//m_pQueue.pop();

	// Swap
	SwapValues(m_pRoot, pLastIndexNode);

	delete pLastIndexNode;

	pLastIndexNode = nullptr;

	--m_size;
	
	SortOnDown(m_pRoot);

	// Set max element
	m_maxElement = m_pRoot->m_value;
}

template<typename DataType>
inline void Priority_Queue<DataType>::SwapValues(Node* pNode_a, Node* pNode_b)
{
	DataType temp = pNode_a->m_value;
	pNode_a->m_value = pNode_b->m_value;
	pNode_b->m_value = temp;
}

template<typename DataType>
inline void Priority_Queue<DataType>::SortOnDown(Node* pNode)
{
	Node* searchingNode = pNode;

	// Until there are no child
	while (searchingNode->m_pLeft != nullptr)
	{
		// when left child is bigger
		if (*searchingNode->m_pLeft > *searchingNode)
		{
			// when left child is bigger than right child
			if (*searchingNode->m_pLeft > *searchingNode->m_pRight)
			{
				SwapValues(searchingNode->m_pLeft, searchingNode);
				searchingNode = searchingNode->m_pLeft;
			}
			// when right child is bigger than left child
			else
			{
				SwapValues(searchingNode->m_pRight, searchingNode);
				searchingNode = searchingNode->m_pRight;
			}
		}
		// when right child is bigger
		else if (*searchingNode->m_pRight > *searchingNode)
		{
			SwapValues(searchingNode->m_pRight, searchingNode);
			searchingNode = searchingNode->m_pRight;
		}
		// done sorting
		else
			break;
	}

}

template<typename DataType>
inline void Priority_Queue<DataType>::SortOnUp(Node* pNode)
{
	Node* searchingNode = pNode;

	// if node is bigger than maxElement
	if (*searchingNode > *m_pRoot)
	{
		SwapValues(searchingNode, m_pRoot);
		m_maxElement = searchingNode->m_value;
	}

	// Until it reachs the root
	while (searchingNode->m_pParent != nullptr)
	{
		// if the value is bigger than parents value
		if (*searchingNode > *searchingNode->m_pParent)
			SwapValues(searchingNode, searchingNode->m_pParent);
		else
			break;

		searchingNode = searchingNode->m_pParent;
	}


}


/*

template<typename DataType>
class Priority_Queue
{
private:
	struct Node
	{
	private:
		size_t m_key;
		DataType m_value;

	public:
		Node() = default;
		Node(size_t key, DataType value) { m_key = key; m_value = value; }
		~Node() { m_pParent = m_pLeft = m_pRight = nullptr; }
		Node* m_pParent = nullptr;
		Node* m_pLeft = nullptr;
		Node* m_pRight = nullptr;

		// Getters
		size_t GetKey() const { return m_key; }
		DataType GetValue() const { return m_value; }

		// Setters
		void SetValue(const DataType& value) { m_value = value; }
	};

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

		size_t GetKey() { m_pNode->GetKey(); }

		// return node
		Node* operator*() { return m_pNode; }

	};

	// Functions
public:
	Priority_Queue() = default;
	~Priority_Queue() {};

	Node* operator[](const size_t& index)
	{
		return Find(index);
	}

	void Insert(const DataType& value);
	void Remove(const size_t& indexKey);

private:



	// Variables
private:
	Node* m_pRoot = nullptr;

	size_t m_size = 0;
};

template<typename DataType>
void Priority_Queue<DataType>::Insert(const DataType& value)
{
	++m_size;

	Node* m_pNewNode;
	Node* m_pParentNode = Find(m_size)->m_pParent;
	
	m_pNewNode = new Node(m_size, value);



}
*/

