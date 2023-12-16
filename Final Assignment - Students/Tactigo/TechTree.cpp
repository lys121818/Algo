// TechTree.cpp
#include "TechTree.h"
#include "lib/Tech.h"

#define _DEBUG 1
#if _DEBUG
#include <iostream>
#include <assert.h>

static size_t _debug_count_1 = 0;
static size_t _debug_count_2 = 0;

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
    
    TechRef targetTech = GetTechByIndex(goalTech);


    CheckData();

    // BFS Search
    if (!m_isSearched)
    {
        ResetInfo();
#if _DEBUG  // Test Purpose
        std::cout << "Checking \n";

#endif  // _DEBUG

        BFS_BestPathFind();
    }

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
void TechTree::SetBestPath(Path* path, TechRef target)
{
    assert(target);

    TechRef currentTech = target;

    std::string key = target->GetTechName();

    bool isLastTech = false;

    do
    {
        // already purchased
        if (currentTech->HasTech())
            break;

        path->emplace_back(currentTech);


        // has parent tech
        if (m_techInfos[key].m_pParentTech == nullptr)
            isLastTech = true;
        else
        {
            currentTech = m_techInfos[key].m_pParentTech;
            key = m_techInfos[key].m_pParentTech->GetTechName();
        }

    } while (!isLastTech);
    

    std::reverse(path->begin(),path->end());
}

/*--------------------------------
    Checks the saved data with
    current data
--------------------------------*/
void TechTree::CheckData()
{
#if _DEBUG
#endif

    bool isDone = false;

    std::queue<TechRef> techList;   // queue for check data

    techList.emplace(GetBasicSocialTech());

    techList.emplace(GetBasicMilitaryTech());

    techList.emplace(GetBasicScienceTech());

    TechRef currentTech = techList.front();

    const std::string currentKey = currentTech->GetTechName();

    techList.pop();



    while (!isDone && !techList.empty())    // while call tobe done or queue is empty
    {
#if _DEBUG
        ++_debug_count_1;
#endif
        if (m_techInfos.find(currentKey) != m_techInfos.end())
        {
            // if current Tech and last info both doesn't have
            if (currentTech->HasTech() == m_techInfos[currentKey].m_hasTech)
            {
                if (currentTech->HasTech())
                {
                    const std::vector<Tech*>& UnlockTech = currentTech->GetAllUnlocks();

                    for (auto& tech : UnlockTech)
                    {
                        techList.push(tech);
                    }
                }
                else
                    m_isSearched = true;


            }
            else
            {
                m_isSearched = false;
                isDone = true;
            }

            currentTech = techList.front();

            techList.pop();
        }
        // Data Not found
        else
        {
            m_isSearched = false;
            isDone = true;
        }

    }

#if _DEBUG
    std::cout << "Times of Loop run on [CheckData]: " << _debug_count_1 << std::endl;
    _debug_count_1 = 0;
#endif

}


/*--------------------------------
    Reset InfoData
--------------------------------*/
void TechTree::ResetInfo()
{
    for (auto& element : m_techInfos)
    {
        element.second.m_bestCost = std::numeric_limits<int>::infinity();
        element.second.m_pParentTech = nullptr;
        element.second.m_hasTech = false; 
    }
}

/*---------------------------
    Stores Data Into Info
---------------------------*/
void TechTree::BFS_BestPathFind()
{
    TechRef test;

    // Social Tech
    test = GetBasicSocialTech();
    BFS_BestPathTactigo(test);

    // Military Tech
    test = GetBasicMilitaryTech();
    BFS_BestPathTactigo(test);

    // Science Tech
    test = GetBasicScienceTech();
    BFS_BestPathTactigo(test);

}

/*---------------------------
    Stores Data of Tactigo
---------------------------*/
void TechTree::BFS_BestPathTactigo(TechRef tactigo)
{
    std::queue<TechRef> techList;

    techList.emplace(tactigo);

    /*---------------------------------------
        Looping through all posible techs
    ----------------------------------------*/
    while (!techList.empty())
    {
#if _DEBUG
        std::cout << "Main Loop of \"" << techList.front()->GetTechName() << "\" \n";
        ++_debug_count_1;
#endif

        TechInfo_BestPath info;

        std::pair<std::string, TechInfo_BestPath> pair;

        int currentTechCost;

        TechRef currentTech = techList.front();

        const std::vector<Tech*>& currentTechUnlocks = currentTech->GetAllUnlocks();

        const std::string& currentKey = currentTech->GetTechName();

        currentTechCost = currentTech->GetCost();

        techList.pop();

        // New tech info
        if (m_techInfos.find(currentKey) == m_techInfos.end())
        {
            if (currentTech->HasTech())
                info.m_bestCost = 0;
            else
                info.m_bestCost = currentTechCost;

            info.m_hasTech = currentTech->HasTech();

            pair.first = currentKey;
            pair.second = info;

            m_techInfos.insert(pair);
            ++m_expectedSize;
        }
        else
        {
            if (currentTech->HasTech())
                m_techInfos[currentKey].m_bestCost = 0;
            else
            {
                // head node
                if(m_techInfos[currentKey].m_pParentTech == nullptr)
                    m_techInfos[currentKey].m_bestCost = currentTechCost;
                else
                {
                    std::string parentKey = m_techInfos[currentKey].m_pParentTech->GetTechName();

                    m_techInfos[currentKey].m_bestCost = m_techInfos[parentKey].m_bestCost + currentTechCost;
                }
            }

            m_techInfos[currentKey].m_hasTech = currentTech->HasTech();
        }


        /*----------------------------------
            Add able unlocks to queue and
            add info to techInfos
        -----------------------------------*/
        for (auto& tech : currentTechUnlocks)
        {
#if _DEBUG
            ++_debug_count_2;
#endif
            std::string key = tech->GetTechName();

            // Set new info of the tech
            if (m_techInfos.find(key) == m_techInfos.end())
            {

                info.m_pParentTech = currentTech;
                info.m_bestCost = tech->GetCost() + m_techInfos[currentKey].m_bestCost;
                info.m_hasTech = tech->HasTech();

                pair.first = key;
                pair.second = info;

                m_techInfos.insert(pair);

                techList.emplace(tech);

                ++m_expectedSize;
            }
            // if the tech already have saved info
            else
            {
                if ( (m_techInfos[key].m_bestCost) > (m_techInfos[currentKey].m_bestCost + tech->GetCost())
                    || m_techInfos[key].m_bestCost == std::numeric_limits<int>::infinity())
                {
                    m_techInfos[key].m_bestCost = m_techInfos[currentKey].m_bestCost + tech->GetCost();
                    m_techInfos[key].m_pParentTech = currentTech;
                    m_techInfos[key].m_hasTech = tech->HasTech();
                    techList.emplace(tech);
                }
            }
        }
    }
#if _DEBUG
    std::cout << "Times of Main Loop run on [BFS_BestPathTactigo]: " << _debug_count_1 << std::endl;
    std::cout << "Times of Iner Loop run on [BFS_BestPathTactigo]: " << _debug_count_2 << std::endl;
    std::cout << '\n';
    _debug_count_1 = 0;
    _debug_count_2 = 0;
#endif
}

