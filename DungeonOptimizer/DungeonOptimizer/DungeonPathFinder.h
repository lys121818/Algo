#pragma once
#include <vector>
#include <queue>

class Room;

class DungeonPathFinder
{
private:
	std::vector<Room> m_dungeon;

	// check if the room is visited
	bool* m_pVisitedRooms;

	// holds the privious visited room index
	int* m_pParentRoom;		// -1 = default

	const size_t m_size;
public:
	DungeonPathFinder(std::vector<Room>& dungeon);
	~DungeonPathFinder() { delete[] m_pVisitedRooms; delete[] m_pParentRoom; }

	std::vector<size_t> GetShortestPath( size_t from, size_t to);

private:
	// add adjacent rooms to the queue
	void AddAdjToQueue(std::queue<size_t>& queue, const size_t& index);

	// it returns the shortest path to the point
	void SetShortestPath(std::vector<size_t>& path, size_t destination);

	// reset the 
	void SetToDefault();
};

