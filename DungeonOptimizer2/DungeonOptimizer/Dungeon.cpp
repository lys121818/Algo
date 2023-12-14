#include "Dungeon.h"

Dungeon::Dungeon(size_t expectedRoomCount)
    : 
    m_rooms{},
    m_size(expectedRoomCount),
    m_sourceIndex(-1)
{
    m_rooms.reserve(m_size);

    m_pNodes = new Node[m_size];
}

Dungeon::Dungeon(const std::vector<DifficultyRoom>& existingLayout)
    : 
    m_rooms(existingLayout),
    m_size(existingLayout.size()),
    m_sourceIndex(-1)
{
    m_pNodes = new Node[m_size];
}

void Dungeon::AddRoom(const int& difficulty)
{
    m_rooms.emplace_back(m_rooms.size(), difficulty);
}

void Dungeon::AddPassageBetween(const size_t& from, const size_t& to)
{
    m_rooms[from].AddPassageTo(m_rooms[to]);
}


/*----------------------------
    Main Function for BFS
----------------------------*/
std::vector<size_t> Dungeon::GetEasiestPath(const size_t& from, const size_t& to)
{

    // Easiest Path to return
    std::vector<size_t> path;

    // edge connection between nodes
    std::pair<size_t, size_t> edge;


    /*  Excptions   */ 
    if (from == to)
    {
        path.push_back(from);
    }
    else if (from >= m_size || to >= m_size)
    {
        return path;
    }
    // Same Source room (previous path find)
    else if (m_sourceIndex == from)
    {
        // already visited the target node
        if (m_pNodes[to].GetVisit())
            SetEasiestPath(&path, to);

        // Continue from last path finding resault
    }
    // Start New
    else
    {
        m_sourceIndex = from;
        DefaultSettings();

        m_pNodes[from].m_visit = true;
        m_pNodes[from].m_dist = 0;

        AddAdjVertex(m_rooms[from], &m_frontier);
    }

    /*  BFS  */ 
    while (path.empty() && !m_frontier.empty())
    {

#if _debug
        ++countFunc1;
#endif

        // Move Next
        size_t onSearchingID = m_frontier.top().second.second;

        m_frontier.pop();

        // Unvisited Node
        if (m_pNodes[onSearchingID].GetVisit() != true)
        {
            m_pNodes[onSearchingID].m_visit = true;
            AddAdjVertex(m_rooms[onSearchingID], &m_frontier);
        }

        // found
        if (onSearchingID == to)
        {
            SetEasiestPath(&path, to);
        }
    }

#if _debug
    PrintLoopCount(path, to);

#endif

    return path;
}

/*--------------------------
    Add Adjacency Vertex
     to Priority queue
--------------------------*/
void Dungeon::AddAdjVertex(const DifficultyRoom& roomToSearch, std::priority_queue<RoomDif, std::vector<RoomDif>, std::greater<RoomDif>>* queue)
{
    const std::vector<Room*>& adjRooms = roomToSearch.GetAdjacentRooms();

    for (auto& room : adjRooms)
    {
#if _debug
        ++countFunc2;
#endif
        // pair to add in queue
        RoomDif adjroom;

        // <searching node, Next node>
        std::pair<size_t, size_t> edge;

        // adjacency node info
        const int difficulty = room->GetDifficulty();
        const size_t roomID = room->GetId();

        if (m_pNodes[roomID].GetVisit())
            continue;


        edge.first = roomToSearch.GetId();
        edge.second = roomID;


        adjroom.first = m_pNodes[edge.first].GetDist() + difficulty;
        adjroom.second = edge;

        // save the shortest path to node
        if (m_pNodes[roomID].GetDist() == std::numeric_limits<int>::infinity() || 
            (m_pNodes[roomID].GetDist() > m_pNodes[edge.first].GetDist() + difficulty ))
        {
            m_pNodes[roomID].m_dist = m_pNodes[edge.first].GetDist() + difficulty;
            m_pNodes[roomID].m_prev = edge.first;
            queue->push(adjroom);
        }
    }
}

/*--------------------------
    Set nodes in Default
--------------------------*/
void Dungeon::DefaultSettings()
{
    for (size_t i = 0; i < m_size; ++i)
    {
        m_pNodes[i].m_dist = std::numeric_limits<int>::infinity();
        m_pNodes[i].m_prev = -1;
        m_pNodes[i].m_visit = false;
    }

    while (!m_frontier.empty())
    {
        m_frontier.pop();
    }

}

/*--------------------------
    Set Path to return
--------------------------*/
void Dungeon::SetEasiestPath(std::vector<size_t>* path, const size_t& target)
{
    int element = target;

    do
    {
        path->push_back(element);
        element = m_pNodes[element].GetPrev();

    } while (element != -1);

    std::reverse(path->begin(), path->end());
}


#if _debug
void Dungeon::PrintLoopCount(const std::vector<size_t>& path, const size_t& target)
{
    std::cout << "=================================================================\n";

    std::cout << "Sortest Path: ";

    for (auto& element : path)
    {
        std::cout << element << " -> ";
    }
    std::cout << '\n' << '\n';

    std::cout << "Total counts of loop [" << m_sourceIndex << "] to [" << target << "]\n";
    std::cout << "[GetEasiestPath]: " << countFunc1 << '\n';
    std::cout << "[AddAdjVertex]: " << countFunc2 << '\n';
    std::cout << "=================================================================\n";



    std::cout << '\n';

    countFunc1 = 0;
    countFunc2 = 0;
}
#endif