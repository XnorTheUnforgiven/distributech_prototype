/*
Name:               abstract.cpp
Description:        Distributech machine structures
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#include <iostream>
#include <fstream>
#include <string>

#include <lib\nlohmann\json.hpp>

#include "include\abstract.h"

using std::string;
using std::ifstream;
using json = nlohmann::json;

/********************************************************************
Name:       

Description:        Constructor

Args:         

Returns:

Exception:

*********************************************************************/
DistributechAbstract::DistributechAbstract(const string itemsFilePath)
{
    _loadData(itemsFilePath);
}

/********************************************************************
Name:       

Description:        Destructor

Args:         

Returns:

Exception:

*********************************************************************/
DistributechAbstract::~DistributechAbstract()
{
}

/********************************************************************
Name:       

Description:        Copy Constructor

Args:         

Returns:

Exception:

*********************************************************************/
DistributechAbstract::DistributechAbstract(const DistributechAbstract &ref)
{
}

/********************************************************************
Name:               loadData

Description:        Loads the machine data iinto usable structures

Args:         

Returns:

Exception:

*********************************************************************/
void DistributechAbstract::_loadData(const string itemsFilePath)
{
    ifstream inputFile;
    inputFile.open(itemsFilePath);

    if (!inputFile.is_open()){
        throw;
    }

    json inputJsonData;
    inputFile >> inputJsonData;

    // Iterate through rows of items to create a display of some sort
    json rowsData = inputJsonData[0];
    for (json::iterator rowIt = rowsData.begin(); rowIt != rowsData.end(); ++rowIt) {
        json itemsData = rowIt.value();

        ItemsRow itemsRow;
        for (json::iterator itemIt = itemsData.begin(); itemIt != itemsData.end(); ++itemIt) {
            itemsRow.emplace(itemIt.key(), itemIt.value());
        }
        _items.push_back(itemsRow);
    }
}

/********************************************************************
Name:               displayItems

Description:        Displays available machine items

Args:         

Returns:

Exception:

*********************************************************************/
void DistributechAbstract::displayItems()
{
    for (Items::iterator itemIt = _items.begin(); itemIt != _items.end(); ++itemIt) {
        ItemsRow itemRow = *itemIt;
        for (ItemsRow::iterator rowIt = itemRow.begin(); rowIt != itemRow.end(); ++rowIt) {
            std::cout << rowIt->first << "-" << rowIt->second << "   ";
        }
        std::cout << std::endl;
    }
}