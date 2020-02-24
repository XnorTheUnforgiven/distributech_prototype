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
using std::ofstream;
using json = nlohmann::json;

using std::find;
using std::to_string;

const string Distributech::_moneyFilePath = "..\\doc\\machine_money.json";
const string Distributech::_statusFilePath = "..\\doc\\machine_status.json";

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

    inputFile.close();
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
    _selectedItem = itemName;

    // Set price value display at 2 decimals
    std::cout << std::fixed << std::setprecision(2);

    ItemsRow itemsRow = _items.at(row);
    if (itemsRow.find(itemName) == itemsRow.end() ) {
        std::cout << "Item name "<< itemName <<" was not found in row #" << row << "!" << std::endl;
        throw;
    }

    _selectedItemPrice = itemsRow.at(itemName);

    std::cout << "Insert " << _selectedItemPrice << _currency << " to receive the item!" << std::endl;
}

/********************************************************************
Name:               addItemToRemainingMoney

Description:        Add the item price to the machine remaining money

Args:         

Returns:

Exception:

*********************************************************************/
void Distributech::addItemToRemainingMoney()
{
    float currentRemainingMoney;

    currentRemainingMoney = _getRemainingMoney();
    _setRemainingMoney(currentRemainingMoney + _selectedItemPrice);
}

/********************************************************************
Name:               returnChange

Description:        Return overpaid change for the item

Args:         

Returns:

Exception:

*********************************************************************/
float Distributech::returnChange(float change)
{
    return change - _selectedItemPrice;
}

/********************************************************************
Name:               resetMachine

Description:        Reset the machine change

Args:         

Returns:

Exception:

*********************************************************************/
void Distributech::resetMachine()
{
    _setRemainingMoney(100.00);
}

/********************************************************************
Name:               setVendorEnable

Description:        Enable/disable the vendor machine

Args:         

Returns:

Exception:

*********************************************************************/
void Distributech::setVendorEnable(bool enable)
{
    ofstream outputFile;
    json status;

    // Set price value display at 2 decimals
    std::cout << std::fixed << std::setprecision(2);

    outputFile.open(_statusFilePath);

    status["vendorEnabled"] = enable;
    outputFile << status;

    outputFile.close();
}

/********************************************************************
Name:               getVendorEnable

Description:        Get the machine enabling status

Args:         

Returns:

Exception:

*********************************************************************/
bool Distributech::getVendorEnable()
{
    ifstream inputFile;
    inputFile.open(_statusFilePath);

    if (!inputFile.is_open()){
        throw;
    }

    json inputJsonData;
    inputFile >> inputJsonData;

    inputFile.close();

    return inputJsonData["vendorEnabled"];
}

/********************************************************************
Name:               _setRemainingMoney

Description:        Set the machine remaining money

Args:         

Returns:

Exception:

*********************************************************************/
void Distributech::_setRemainingMoney(float money)
{
    ofstream outputFile;
    json status;

    // Set price value display at 2 decimals
    std::cout << std::fixed << std::setprecision(2);

    outputFile.open(_moneyFilePath);

    status["remainingMoney"] = money;
    outputFile << status;

    outputFile.close();
}

/********************************************************************
Name:               _getRemainingMoney

Description:        Get the machine remaining money

Args:         

Returns:

Exception:

*********************************************************************/
float Distributech::_getRemainingMoney()
{
    ifstream inputFile;
    inputFile.open(_moneyFilePath);

    if (!inputFile.is_open()){
        throw;
    }

    json inputJsonData;
    inputFile >> inputJsonData;

    inputFile.close();

    return inputJsonData["remainingMoney"];
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