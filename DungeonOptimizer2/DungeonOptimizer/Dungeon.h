#pragma once

#include <vector>
#include "DifficultyRoom.h"

class Dungeon
{
private:
    struct Node
    {
        int m_dist = std::numeric_limits<int>::infinity();
        size_t m_prev = NULL;
    };

private:
    std::vector<DifficultyRoom> m_rooms;

    int m_currentDist;

    std::vector<size_t> m_path;

    Node* m_pNodes;

public:
    Dungeon(size_t expectedRoomCount);
    Dungeon(const std::vector<DifficultyRoom>& existingLayout);

    const DifficultyRoom& GetRoom(size_t id) const { return m_rooms[id]; }
    DifficultyRoom& GetRoom(size_t id) { return m_rooms[id]; }

    void AddRoom(int difficulty);

    void AddPassageBetween(size_t from, size_t to);

    std::vector<size_t> GetEasiestPath(size_t from, size_t to);

private:
    size_t GetEasiestFromAdj(const DifficultyRoom& roomToSearch);




};