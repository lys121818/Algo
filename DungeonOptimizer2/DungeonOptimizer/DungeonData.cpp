#include "DungeonData.h"

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
    dungeon[7].AddPassageTo(dungeon[6]);

    return dungeon;
}

std::vector<DifficultyRoom> ConstructDifficultDungeon()
{
    /*

    00 <-> 01 --> 02 --> 03
    ^      ^             ^
    |      |             |
    v      v             |
    04 <-> 05 <-> 06 <-> 07
    ^             ^      ^
    |             |      |
    v             v      v
    08 <-> 09 <-> 10 <-> 11

    // Difficulties
    00: 0
    01: 4
    02: 6
    03: 10
    04: 1
    05: 6
    06: 1
    07: 3
    08: 1
    09: 2
    10: 1
    11: 4

    */

    std::vector<DifficultyRoom> dungeon{
        {0,0},{1,4},{2,6},{3,10},
        {4,1},{5,6},{6,1},{7,3},
        {8,1},{9,2},{10,1},{11,4}
    };

    dungeon[0].AddPassageTo(dungeon[1]);
    dungeon[0].AddPassageTo(dungeon[4]);

    dungeon[1].AddPassageTo(dungeon[0]);
    dungeon[1].AddPassageTo(dungeon[2]);
    dungeon[1].AddPassageTo(dungeon[5]);

    dungeon[2].AddPassageTo(dungeon[3]);

    dungeon[4].AddPassageTo(dungeon[0]);
    dungeon[4].AddPassageTo(dungeon[5]);
    dungeon[4].AddPassageTo(dungeon[8]);

    dungeon[5].AddPassageTo(dungeon[1]);
    dungeon[5].AddPassageTo(dungeon[4]);
    dungeon[5].AddPassageTo(dungeon[6]);

    dungeon[6].AddPassageTo(dungeon[5]);
    dungeon[6].AddPassageTo(dungeon[7]);
    dungeon[6].AddPassageTo(dungeon[10]);

    dungeon[7].AddPassageTo(dungeon[3]);
    dungeon[7].AddPassageTo(dungeon[6]);
    dungeon[7].AddPassageTo(dungeon[11]);

    dungeon[8].AddPassageTo(dungeon[4]);
    dungeon[8].AddPassageTo(dungeon[9]);

    dungeon[9].AddPassageTo(dungeon[8]);
    dungeon[9].AddPassageTo(dungeon[10]);

    dungeon[10].AddPassageTo(dungeon[6]);
    dungeon[10].AddPassageTo(dungeon[9]);
    dungeon[10].AddPassageTo(dungeon[11]);

    dungeon[11].AddPassageTo(dungeon[7]);
    dungeon[11].AddPassageTo(dungeon[10]);

    return dungeon;
}
