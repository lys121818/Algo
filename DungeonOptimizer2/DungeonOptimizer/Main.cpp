#include <iostream>

#include "Dungeon.h"
#include "DungeonData.h"


int main()
{
    const std::vector<DifficultyRoom>& rooms = ConstructDifficultDungeon();
    Dungeon dungeon{ rooms };

    std::vector<size_t> path;
    path.reserve(12);

    path = dungeon.GetEasiestPath(3, 0);
    path = dungeon.GetEasiestPath(0, 3);
    // should be 0,4,8,9,10,6,7,3

    path = dungeon.GetEasiestPath(5, 5);
    path = dungeon.GetEasiestPath(0, 7);
    path = dungeon.GetEasiestPath(0, 6);
    path = dungeon.GetEasiestPath(0, 11);
    path = dungeon.GetEasiestPath(2, 1);
    path = dungeon.GetEasiestPath(1, 4);
    path = dungeon.GetEasiestPath(0, 3);



    return 0;
}