#include <iostream>
#include "DungeonPathFinder.h"
#include "DungeonData.h"
#include "Room.h"


int main()
{
    std::vector<Room> dungeon = ConstructDungeon();

    DungeonPathFinder pathFinder(dungeon);

    std::vector<size_t> path;
    
    path = pathFinder.GetShortestPath(0,3);
    //should be 0,1,2,3
    
    for (auto& element : path)
    {
        std::cout << element << " -> ";
    }



    return 0;
}