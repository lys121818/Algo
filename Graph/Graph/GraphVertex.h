#pragma once

template<typename DataType>
class GraphVertex
{
public:
    GraphVertex() = default;
    GraphVertex(DataType node,int index)
        : 
        m_node(node),
        m_index(index)
    {

    }
    ~GraphVertex()
    {
        delete[] m_pNext;
    }

    DataType GetNode()
    {
        return m_node;
    }


    void SetNextNode(GraphVertex* pNext) { m_pNext = pNext; }

    GraphVertex* GetNextNode() { return m_pNext; }

    int GetNodeIndex() { return m_index; }

    // return ture if m_pNext exist
    bool HasNextNode() { return m_pNext == nullptr ? false : true; }

    bool GetVisited() { return m_isVisited; }

    void SetVisited(bool set) { m_isVisited = set; }

private:
    DataType m_node;

    GraphVertex* m_pNext = nullptr;

    bool m_isVisited = false;

    int m_index;
};