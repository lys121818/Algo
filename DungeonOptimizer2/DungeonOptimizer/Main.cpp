#include <iostream>

#include "Dungeon.h"
#include "DungeonData.h"


int main()
{
    const std::vector<DifficultyRoom>& rooms = ConstructDifficultDungeon();
    Dungeon dungeon{ rooms };

    std::vector<size_t> path = dungeon.GetEasiestPath(0, 3);
    // should be 0,4,8,9,10,6,7,3

    return 0;
}