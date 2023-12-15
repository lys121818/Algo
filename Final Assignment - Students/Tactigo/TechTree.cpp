// TechTree.cpp
#include "TechTree.h"
#include "lib/Tech.h"

#define _DEBUG 0
#if _DEBUG
#include <iostream>
#include <assert.h>
#endif  // _DEBUG

#include <queue>

//---------------------------------------------------------------------------------------------------------------------
// This function finds the best path to the tech we want.
//      * goalTech: The index of the tech we're looking for.  Call GetTechByIndex() to get the actual Tech instance.
//      * return: 	The best path to the goal tech.  This should be a vector sorted in the order of the best path  
//                  from the start to the goal.  The best path is what you need to populate with this function and return.
//---------------------------------------------------------------------------------------------------------------------
TechTree::Path TechTree::FindBestPath(size_t goalTech)
{
#if _DEBUG  // Test Purpose
    for (size_t i = 0; i < 13; ++i)
    {
        std::cout << GetTechByIndex(i)->GetTechName() << '\n';
        std::cout << GetTechByIndex(i)->GetCost() << '\n' << '\n';
    }

#endif  // _DEBUG
    
    const Tech* targetTech = GetTechByIndex(goalTech);



    // BFS Search
    //if(!m_isSearched)
        BFS_BestPathFind();

    Path bestPath;
    bestPath.reserve(m_expectedSize);   // reserved by max size of tech which was created on BFS function call

    if (targetTech->HasTech())
        return bestPath;

    // Set best Path to return type vector
    SetBestPath(&bestPath, targetTech);

    // Return the path
    return bestPath;
}

/*--------------------------------
    Set Best Path to Return
--------------------------------*/
void TechTree::SetBestPath(Path* path, const Tech* target)
{
    assert(target);

    const Tech* currentTech = target;

    std::string key = target->GetTechName();

    while(m_techInfos[key].m_pParentTech != nullptr)
    {
        // Previous has been purchased
        if (currentTech->HasTech())
            break;

        path->emplace_back(currentTech);

        key = currentTech->GetTechName();

        //if(m_techInfos.find(key) != m_techInfos.end())
            currentTech = m_techInfos[key].m_pParentTech;

    }


    std::reverse(path->begin(),path->end());
}

/*--------------------------------------
    True if it pass the test
    (pass = find best case)
---------------------------------------*/
bool TechTree::ExceptionTest(Path* path, const Tech* target)
{
    bool isPass = false;

    return isPass;
}


/*---------------------------
    Stores Data Into Info
---------------------------*/
void TechTree::BFS_BestPathFind()
{
    const Tech* test;

    // Social Tech
    test = GetBasicSocialTech();
    BFS_BestPathTactigo(test);

    // Military Tech
    test = GetBasicMilitaryTech();
    BFS_BestPathTactigo(test);

    // Science Tech
    test = GetBasicScienceTech();
    BFS_BestPathTactigo(test);

    m_isSearched = true;
}

/*---------------------------
    Stores Data of Tactigo
---------------------------*/
void TechTree::BFS_BestPathTactigo(const Tech* tactigo)
{
    std::queue<const Tech*> techList;

    techList.emplace(tactigo);

    /*---------------------------------------
        Looping through all posible techs
    ----------------------------------------*/
    while (!techList.empty())
    {
        const Tech* currentTech;

        int currentTechCost;

        std::string currentKey;

        std::vector<Tech*> currentTechUnlocks;

        currentTech = techList.front();

        currentKey = currentTech->GetTechName();

        currentTechCost = currentTech->GetCost();

        currentTechUnlocks = currentTech->GetAllUnlocks();


        techList.pop();

        TechInfo_BestPath info;

        std::pair<std::string, TechInfo_BestPath> pair;

        if (m_techInfos.find(currentKey) == m_techInfos.end())
        {
            if (currentTech->HasTech())
                info.m_bestCost = 0;
            else
                info.m_bestCost = currentTechCost;

            pair.first = currentKey;
            pair.second = info;

            m_techInfos.insert(pair);
            ++m_expectedSize;
        }
        else
        {
            if (currentTech->HasTech())
                m_techInfos[currentKey].m_bestCost = 0;
        }


        /*----------------------------------
            Add able unlocks to queue and
            add info to techInfos
        -----------------------------------*/
        for (auto& tech : currentTechUnlocks)
        {
            std::string key = tech->GetTechName();

            // Set new info of the tech
            if (m_techInfos.find(key) == m_techInfos.end())
            {

                info.m_pParentTech = currentTech;
                info.m_bestCost = tech->GetCost() + m_techInfos[currentKey].m_bestCost;


                pair.first = key;
                pair.second = info;

                m_techInfos.insert(pair);

                techList.emplace(tech);

                ++m_expectedSize;
            }
            // if the tech already have saved info
            else
            {
                if ( (m_techInfos[key].m_bestCost) > (m_techInfos[currentKey].m_bestCost + tech->GetCost()) )
                {
                    m_techInfos[key].m_bestCost = m_techInfos[currentKey].m_bestCost + tech->GetCost();
                    m_techInfos[key].m_pParentTech = currentTech;
                }
            }
        }
    }
}

