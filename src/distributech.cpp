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
Description:        Constructor

*********************************************************************/
Distributech::Distributech()
{
}

/********************************************************************
Description:        Destructor

*********************************************************************/
Distributech::~Distributech()
{
}

/********************************************************************
Description:        Copy Constructor

*********************************************************************/
Distributech::Distributech(const Distributech &ref)
{
}

/********************************************************************
Name:               loadData

Description:        Loads the machine data into usable structures

Args:               itemsFilePath (const str):
                        Path of the file containing items
                        displayed in the machine
                    
                    region (const str):
                        Region in which the distributech machine
                        is being deployed

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

Args:               row (unsigned):
                        Row number onto which the item is displayed

                    itemName (string):
                        Name of the item that has been selected

*********************************************************************/
void Distributech::displayItemPrice(const unsigned row, const string itemName)
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

*********************************************************************/
void Distributech::addItemToRemainingMoney()
{
    _setRemainingMoney(_getRemainingMoney() + _selectedItemPrice);
}

/********************************************************************
Name:               returnChange

Description:        Return surplus change difference for the item

Args:               Change (float):
                        Change the user gave to the machine to pay
                        for the item

Returns:            (float): Surplus change difference 

*********************************************************************/
float Distributech::returnChange(const float change)
{
    return change - _selectedItemPrice;
}

/********************************************************************
Name:               resetMachine

Description:        Reset the machine change value to 100.0

*********************************************************************/
void Distributech::resetMachine()
{
    _setRemainingMoney(100.00);
}

/********************************************************************
Name:               setVendorEnable

Description:        Enable/disable the vendor machine

Args:               enable(bool):
                        Status to enable/disable the vendor machine

*********************************************************************/
void Distributech::setVendorEnable(const bool enable)
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

Returns:            (bool): machine enabling status

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

Args:               money (float):
                        Vendor machine remaining money to be set to

*********************************************************************/
void Distributech::_setRemainingMoney(const float money)
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

Returns:            (float): vendor machine remaining money

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

Args:               region (const str):
                        Region in which the distributech machine
                        is being deployed 

Returns:

Exception:

*********************************************************************/
string Distributech::_regionToCurrency(const string region)
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