#pragma once

#include "Room.h"

class DifficultyRoom : public Room
{
private:
    int m_difficulty;

public:
    DifficultyRoom(size_t id, int difficulty) : Room{ id }, m_difficulty{ difficulty } {}
    int GetDifficulty() const { return m_difficulty; }
};