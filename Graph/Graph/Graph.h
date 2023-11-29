#pragma once
#include "GraphVertex.h"
#include <assert.h>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>
#include <iostream>

#define _Debug 1

template<typename DataType>
class Graph
{
public:

	Graph(int size, bool isDirected) 
		: 
		m_maxVerts((size_t)size), 
		m_isDirected(isDirected)
	{
		// error call when size is not valid
		assert(size > 0);
		m_pVectexes.reserve(m_maxVerts);
	}
	~Graph() 
	{
		// delete list
		
	}

	bool AddNode(DataType node)
	{
		// if the Nodes are full
		if (m_pVectexes.size() >= m_maxVerts)
			return false;

		// Add node to the list
		m_pVectexes.push_back(new GraphVertex<DataType>(node, m_pVectexes.size()));

		return true;
	}

	int GetNextUnvisitedVertex(size_t index)
	{
		assert(m_pVectexes.empty() != true);

		GraphVertex<DataType>* searchingVertex;
		searchingVertex = m_pVectexes[index];

		// while there are no more linked vertex
		while (searchingVertex)
		{
			// if the node is already visited
			if (searchingVertex->GetVisited())
			{
				searchingVertex = searchingVertex->GetNextNode();
			}
			else
			{
				// Check if the actual node is set as visited
				if (m_pVectexes[searchingVertex->GetNodeIndex()]->GetVisited())
				{
					searchingVertex->SetVisited(true);
					continue;
				}

				// Set visited true
				searchingVertex->SetVisited(true);

				// return index of next node
				return searchingVertex->GetNodeIndex();
			}

		}

		// no more next node
		return -1;
	}

	// Set DirectEdge A -> B
	void AttachDirectEdge(size_t vertex_a, size_t vertex_b)
	{
		GraphVertex<DataType>* pNewNode;

		// Create New node to set next node
		pNewNode = new GraphVertex<DataType>(m_pVectexes[vertex_b]->GetNode(), vertex_b);

		// if it already has the next node
		if (m_pVectexes[vertex_a])
		{
			// Set B next node to A's next node
			pNewNode->SetNextNode(m_pVectexes[vertex_a]->GetNextNode());
		
			// Set A's next node to B
			m_pVectexes[vertex_a]->SetNextNode(pNewNode);
		
			/*
				A -> C
		
				to
		
				A -> B -> C
		
				Why?: Inseting front has O(1) time complexity
			*/
		
		}
		else
		{
			m_pVectexes[vertex_a]->SetNextNode(pNewNode);
		}
	}

	void AttachUndirectEdge(size_t vertex_a, size_t vertex_b)
	{
		AttachDirectEdge(vertex_a, vertex_b);
		AttachDirectEdge(vertex_b, vertex_a);
	}

	// Searching through
	bool DepthFirstSearch(size_t startIndex, size_t endIndex)
	{
		// Set visited
		m_pVectexes[startIndex]->SetVisited(true);

#if _Debug
		// Debug output
		std::cout << m_pVectexes[startIndex]->GetNode();
#endif // _Debug

		int currentVertex = 0;
		
		std::stack<int> searchStack;

		// Add the starting index to stack
		searchStack.push(startIndex);
		
		// Loop for searching
		while (searchStack.empty() != true)
		{
			currentVertex = GetNextUnvisitedVertex(searchStack.top());

			// No more next node
			if (currentVertex == -1)
				searchStack.pop();
			else
			{
				// set visited
				m_pVectexes[currentVertex]->SetVisited(true);

#if _Debug
				// Debug output
				std::cout << "->" << m_pVectexes[currentVertex]->GetNode();
#endif // _Debug

				// Add new vertex to stack
				searchStack.push(currentVertex);
			}

			// Found!
			if (currentVertex == endIndex)
			{
				ResetVisited();

				return true;
			}
		}

		// no found
#if _Debug
		// Debug output
		std::cout << "\nNot Found";
#endif // _Debug

		ResetVisited();
		return false;
	}

	// reset visited
	void ResetVisited()
	{
		for (auto& element : m_pVectexes)
			element->SetVisited(false);
	}


	// Todo printing
#if _Debug
	// Debug output
	std::cout << "\nNot Found";
	void Print()
	{
		int currentNode = 0;
		while (currentNode <= m_pVectexes.size())
		{

		}
	}
#endif // _Debug


private:
	std::vector<GraphVertex<DataType>*> m_pVectexes;

	size_t m_maxVerts;

	bool m_isDirected;
};