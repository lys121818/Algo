#pragma once
#include "lib/TechTreeBase.h"

//---------------------------------------------------------------------------------------------------------------------
// Your comments go here:
// 
//---------------------------------------------------------------------------------------------------------------------
#include <unordered_map>
#include <string>

class TechTree : public TechTreeBase
{
public:
    using Path = std::vector<const Tech*>;

    using TechRef = const Tech*;
    Path FindBestPath(size_t goalTech);



/*------------------------------------------------ Under Here
            Designed by Jason Lee                   ||
---------------------------------------------------*/
// [Member Functions]
private:

    // Store all data using BFS search
    void BFS_BestPathFind();

    void BFS_BestPathTactigo(TechRef tactigo);

    void SetBestPath(Path* path, TechRef target);

    // TODO: check data using hasTech to set isSearched
    void CheckData();

    void ResetInfo();

// [Member Variable]
private:
    // struct stored value of each nodes
    struct TechInfo_BestPath
    {
        int m_bestCost = std::numeric_limits<int>::infinity();
        TechRef m_pParentTech = nullptr;
        bool m_hasTech = false; // to check if the data is same as last path find function run
    };

    // Unordered Map to store TechInfo
    std::unordered_map<std::string, TechInfo_BestPath> m_techInfos;

    size_t m_expectedSize = 0;  // size to reserve memeories

    bool m_isSearched = false;  // To check if the BFS Function has been run
};
