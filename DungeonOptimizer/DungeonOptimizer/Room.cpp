#include <iostream>
#include "Room.h"

Room::Room(size_t id)
    : m_id{id}
{
    m_adjacentRooms.reserve(3);
}

void Room::AddPassageTo(Room& pRoom)
{
    m_adjacentRooms.push_back(&pRoom);
}

