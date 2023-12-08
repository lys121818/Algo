#include "DungeonData.h"

#include "Room.h"

// Don't modify this function. This is the layout
// you should be using for testing.
std::vector<class Room> ConstructDungeon()
{
    /*

    0 <-> 1 --> 2 --> 3
    ^     ^           ^
    |     |           |
    v     v           |
    4 <-> 5 <-> 6 <-> 7

    */

    std::vector<Room> dungeon{ 0,1,2,3,4,5,6,7 };

    dungeon[0].AddPassageTo(dungeon[1]);
    dungeon[0].AddPassageTo(dungeon[4]);

    dungeon[1].AddPassageTo(dungeon[0]);
    dungeon[1].AddPassageTo(dungeon[2]);
    dungeon[1].AddPassageTo(dungeon[5]);

    dungeon[2].AddPassageTo(dungeon[3]);

    dungeon[4].AddPassageTo(dungeon[0]);
    dungeon[4].AddPassageTo(dungeon[5]);

    dungeon[5].AddPassageTo(dungeon[1]);
    dungeon[5].AddPassageTo(dungeon[4]);
    dungeon[5].AddPassageTo(dungeon[6]);

    dungeon[6].AddPassageTo(dungeon[5]);
    dungeon[6].AddPassageTo(dungeon[7]);

    dungeon[7].AddPassageTo(dungeon[3]);

    return dungeon;

}
