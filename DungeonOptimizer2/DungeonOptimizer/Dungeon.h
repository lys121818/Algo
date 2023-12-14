#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include "DifficultyRoom.h"

#define _debug 1

class Dungeon
{
private:

    // contains difficulty and edge
    typedef std::pair<int, std::pair<size_t,size_t>> RoomDif;

private:

    struct Node
    {
        int m_dist = std::numeric_limits<int>::infinity();
        int m_prev = -1;
        bool m_visit = false;

        // [GETTERS]
        const int& GetPrev() const { return m_prev; }
        const int& GetDist() const { return m_dist; }
        const bool& GetVisit() const { return m_visit; }
    };


/*================
    FUNTIONS
================*/
public:
    Dungeon(size_t expectedRoomCount);
    Dungeon(const std::vector<DifficultyRoom>& existingLayout);
    ~Dungeon() { delete[] m_pNodes; }

    const DifficultyRoom& GetRoom(size_t id) const { return m_rooms[id]; }
    DifficultyRoom& GetRoom(size_t id) { return m_rooms[id]; }

    void AddRoom(const int& difficulty);

    void AddPassageBetween(const size_t& from,const size_t& to);

    std::vector<size_t> GetEasiestPath(const size_t& from, const size_t& to);

private:
    void AddAdjVertex(const DifficultyRoom& roomToSearch, std::priority_queue<RoomDif, std::vector<RoomDif>, std::greater<RoomDif>>* queue);

    void DefaultSettings();

    void SetEasiestPath(std::vector<size_t>* path,const size_t& target);

/*================
    VARIABLES
================*/
private:
    // rooms involved in dungeon
    std::vector<DifficultyRoom> m_rooms;

    // Priority queue (Distance lower in Priority)
    std::priority_queue<RoomDif, std::vector<RoomDif>, std::greater<RoomDif>> m_frontier;

    // size of the dungeon
    const size_t m_size;

    // room infos
    Node* m_pNodes;

    // Source room
    int m_sourceIndex;


#if _debug
    size_t countFunc1 = 0;  // GetEasiestPath
    size_t countFunc2 = 0;  // AddAdjVertex

    void PrintLoopCount(const std::vector<size_t>& path, const size_t& target);
#endif

};