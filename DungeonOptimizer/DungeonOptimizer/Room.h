#pragma once

#include <vector>
#include <queue>

class Room
{
private:
    size_t m_id;
    std::vector<Room*> m_adjacentRooms;

public:
    Room(size_t id);

    void AddPassageTo(Room& pRoom);


    // [GETTERS]
    const std::vector<Room*>& GetAdjacentRooms() const { return m_adjacentRooms; }

    size_t GetID() const { return m_id; }
    
};

