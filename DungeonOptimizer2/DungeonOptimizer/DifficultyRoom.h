#pragma once

#include "Room.h"

class DifficultyRoom : public Room
{
private:
    int m_difficulty;

    friend bool operator<(const DifficultyRoom& left, const DifficultyRoom& right) 
    {
        return left.m_difficulty < right.m_difficulty;
    }

    friend bool operator>(const DifficultyRoom& left, const DifficultyRoom& right)
    {
        return right.m_difficulty < left.m_difficulty;
    }

public:
    DifficultyRoom(size_t id, int difficulty) : Room{ id }, m_difficulty{ difficulty } {}
    int GetDifficulty() const { return m_difficulty; }
};