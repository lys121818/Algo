#include "DungeonPathFinder.h"
#include <stack>
#include "Room.h"
#include <assert.h>

DungeonPathFinder::DungeonPathFinder(std::vector<Room>& dungeon)
    :
    m_dungeon(dungeon),
    m_size(dungeon.size())
{
    assert(m_size > 0);

    m_pVisitedRooms = new bool[m_size];

    m_pParentRoom = new int[m_size];

    SetToDefault();
}

/*---------------------------------- *
 |   Where Main BFS Algorithm runs   |
 *-----------------------------------*/
std::vector<size_t> DungeonPathFinder::GetShortestPath(size_t from, size_t to)
{
    // Write this function to correctly return the path between two Rooms by id.
    std::vector<size_t> shortestPath;

    // add starting point
    shortestPath.push_back(from);

    // BFS queue
    std::queue<size_t> roomsToCheck;

    // First Room
    roomsToCheck.push(from);

    // Until the BFS queue is empty
    while (!roomsToCheck.empty())
    {
        // Room to search
        size_t currentRoomID = roomsToCheck.front();

        // Set Checked
        m_pVisitedRooms[currentRoomID] = true;
        roomsToCheck.pop();

        // found the room
        if (currentRoomID == to)
        {
            SetShortestPath(shortestPath, to);

            SetToDefault();

            return shortestPath;
        }

        AddAdjToQueue(roomsToCheck, currentRoomID);

    }

    SetToDefault();

    // Not Found
    return std::vector<size_t>();
}

/*----------------------------------- *
 |   Add adjacent room to the queue   |
 * -----------------------------------*/
void DungeonPathFinder::AddAdjToQueue(std::queue<size_t>& queue, const size_t& index)
{
    // current checking adjacent rooms (color::gray)
    std::vector<Room*> adjacentRooms;

    adjacentRooms = m_dungeon[index].GetAdjacentRooms();

    // add adjacent rooms to the queue
    for (auto& room : adjacentRooms)
    {
        int roomIndex = room->GetID();

        // if the room hasnt been visited
        if (!m_pVisitedRooms[roomIndex])
        {
            queue.push(roomIndex);

            m_pParentRoom[roomIndex] = index;
        }
            
    }
}

/*------------------------------------- *
 |   Set shortest path into the vector  |
 |      in right order using stack      |
 * -------------------------------------*/
void DungeonPathFinder::SetShortestPath(std::vector<size_t>& path, size_t destination)
{
    size_t index = destination;

    std::stack<size_t> pathStack;

    // Pointer of the room to get ID
    Room* currentRoom;

    // Path until the reach the begining
    while (m_pParentRoom[index] != -1)
    {
        currentRoom = &m_dungeon[index];

        size_t roomID = currentRoom->GetID();

        pathStack.push(roomID);

        // Move Next
        index = (size_t)m_pParentRoom[index];

    }

    // set path in right order
    while (!pathStack.empty())
    {
        path.push_back(pathStack.top());

        pathStack.pop();
    }
}

/*------------------------- *
 |  Reset to default value  |
 * -------------------------*/
void DungeonPathFinder::SetToDefault()
{
    for (size_t i = 0; i < m_size; ++i)
    {
        m_pVisitedRooms[i] = false;
        m_pParentRoom[i] = -1;
    }
}
