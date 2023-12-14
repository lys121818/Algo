#pragma once

#include <vector>

class Room
{
private:
    size_t m_id;
    std::vector<Room*> m_adjacentRooms;

public:
    Room(size_t id);

    size_t GetId() const { return m_id; }
    const std::vector<Room*>& GetAdjacentRooms() const { return m_adjacentRooms; }

    virtual int GetDifficulty() const { return std::numeric_limits<int>::infinity(); }
        

    void AddPassageTo(Room& pRoom);
};

