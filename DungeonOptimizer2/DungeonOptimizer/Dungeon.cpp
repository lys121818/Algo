#include "Dungeon.h"

Dungeon::Dungeon(size_t expectedRoomCount)
    : m_rooms{},
    m_currentDist(std::numeric_limits<int>::infinity())

{
    m_rooms.reserve(expectedRoomCount);

    m_pNodes = new Node[expectedRoomCount];

}

Dungeon::Dungeon(const std::vector<DifficultyRoom>& existingLayout)
    : m_rooms(existingLayout),
    m_currentDist(std::numeric_limits<int>::infinity())
{
    m_pNodes = new Node[existingLayout.size()];
}

void Dungeon::AddRoom(int difficulty)
{
    m_rooms.emplace_back(m_rooms.size(), difficulty);
}

void Dungeon::AddPassageBetween(size_t from, size_t to)
{
    m_rooms[from].AddPassageTo(m_rooms[to]);
}

std::vector<size_t> Dungeon::GetEasiestPath(size_t from, size_t to)
{
    //TODO: Complete this function to correctly return the path with
    // the least cumulative difficulty. Think of difficulty like a cost
    // you pay to enter the room.

    //m_path.push_back(from);

    // low priority queue of difficulty



    GetEasiestFromAdj(m_rooms[from]);



    return std::vector<size_t>();
}

size_t Dungeon::GetEasiestFromAdj(const DifficultyRoom& roomToSearch)
{
    const std::vector<Room*>& adjRooms = roomToSearch.GetAdjacentRooms();

    //std::priority_queue<Room, std::vector<Room>, std::greater<DifficultyRoom>> frontier(adjRooms.begin(),adjRooms.end());

    if (adjRooms[0] > adjRooms[1])
    {
        m_currentDist++;
    }

    size_t index;

    for (auto& room : adjRooms)
    {
        size_t currentRoom = room->GetId();

        // if the node hasn't visited from any other node
        if (m_pNodes[currentRoom].m_prev = NULL)
        {

        }

        if (m_rooms[currentRoom].GetDifficulty() < m_currentDist)
        {

        }
    }



    return size_t();
}
