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
#include <iomanip>

#include <lib\nlohmann\json.hpp>

#include "include\distributech.h"

using std::string;
using std::ifstream;
using json = nlohmann::json;

using std::find;
using std::to_string;

/********************************************************************
Name:       

Description:        Constructor

Args:         

Returns:

Exception:

*********************************************************************/
Distributech::Distributech()
{
}

/********************************************************************
Name:       

Description:        Destructor

Args:         

Returns:

Exception:

*********************************************************************/
Distributech::~Distributech()
{
}

/********************************************************************
Name:       

Description:        Copy Constructor

Args:         

Returns:

Exception:

*********************************************************************/
Distributech::Distributech(const Distributech &ref)
{
}

/********************************************************************
Name:               loadData

Description:        Loads the machine data into usable structures

Args:         

Returns:

Exception:

*********************************************************************/
void Distributech::loadData(const string itemsFilePath, const string region)
{
    ifstream inputFile;
    inputFile.open(itemsFilePath);

    if (!inputFile.is_open()){
        throw;
    }

    json inputJsonData;
    inputFile >> inputJsonData;

    // Iterate through rows of items to load data in a usable structure
    for (json::iterator rowIt = inputJsonData.begin(); rowIt != inputJsonData.end(); ++rowIt) {
        json itemsData = rowIt.value();

        ItemsRow itemsRow;
        for (json::iterator itemIt = itemsData.begin(); itemIt != itemsData.end(); ++itemIt) {
            string key = itemIt.key();
            float value = itemIt.value();
            itemsRow.emplace(key, value);
        }
        _items.push_back(itemsRow);
    }

    _currency = _regionToCurrency(region);
}

/********************************************************************
Name:               displayItems

Description:        Displays available machine items

Args:         

Returns:

Exception:

*********************************************************************/
void Distributech::displayItems()
{
    // Set price value display at 2 decimals
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Items prices are set in " << _currency << " currency."<< std::endl;
    std::cout << std::endl;

    // Display data into rows, including item name and price
    unsigned rowNumber;
    for (Items::iterator itemIt = _items.begin(); itemIt != _items.end(); ++itemIt) {
        ItemsRow itemRow = *itemIt;
        rowNumber = std::distance(_items.begin(), itemIt) + 1;

        std::cout << "Row #" << rowNumber << ":   ";
        for (ItemsRow::iterator rowIt = itemRow.begin(); rowIt != itemRow.end(); ++rowIt) {
            std::cout << rowIt->first << "(" <<  rowIt->second << ")   ";
        }
        std::cout << std::endl;
    }
}

/********************************************************************
Name:               getItemPriceStr

Description:        Get the price of a specific item with currency
                    in a string format

Args:         

Returns:

Exception:

*********************************************************************/
void Distributech::displayItemPrice(unsigned row, string itemName)
{
    float price;

    // Set price value display at 2 decimals
    std::cout << std::fixed << std::setprecision(2);

    ItemsRow itemsRow = _items.at(row);
    if (itemsRow.find(itemName) == itemsRow.end() ) {
        std::cout << "Item name "<< itemName <<" was not found in row #" << row << "!" << std::endl;
        throw;
    }

    price = itemsRow.at(itemName);

    std::cout << "Insert " << price << _currency << " to receive the item!" << std::endl;
}

/********************************************************************
Name:               _regionToCurrency

Description:        Converts the region to the used currency and 
                    returns the associated currency

Args:         

Returns:

Exception:

*********************************************************************/
string Distributech::_regionToCurrency(string region)
{
    if (region == "eu"){
        return "EU";
    }
    else if (region == "can") {
        return "CAD";
    }
    else if (region == "us") {
        return "USD";
    }
    // Unhandled and unexpected region
    throw;
}