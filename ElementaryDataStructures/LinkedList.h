#pragma once


class LinkedList
{
private:

	struct Node
	{
		int data;

		Node* m_pNext = nullptr;
		Node* m_pPrev = nullptr;

		Node(int data) : data(data) {}
		~Node() { delete m_pNext; m_pNext = m_pPrev = nullptr; }

		void ClearNode();

	};

	Node* m_pHead = nullptr;
	Node* m_pTail = nullptr;
	Node* FindNode(int dataToFind);

	size_t m_size = 0;

public:
	LinkedList() = default;
	~LinkedList() { delete m_pHead, m_pTail; }

	void Insert(int data, size_t position);

	void Push_Front(int data);
	void Push_Back(int data);

	void Pop_Back();
	void Pop_Front();

	void Clear();
	void Delete(int data);
	void Print();
private:

};

