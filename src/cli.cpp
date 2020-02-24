/*
Name:               cli.cpp
Description:        Cli interface
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#include <iostream>
#include <string>
#include <exception>

#include "include\cli.h"

using std::string;
using std::stoul;

const string Cli::_europeItemsFilePath = "..\\doc\\europe_items.json";
const string Cli::_northAmericaItemsFilePath = "..\\doc\\north_america_items.json";

/********************************************************************

Description:        Constructor

*********************************************************************/
Cli::Cli():
    _userType("UNKNOWN"),
    _regionType("UNKNOWN"),
    _specialUsers()
{
    _acceptedUserTypes.push_front("customer");
    _acceptedUserTypes.push_front("employee");
    _acceptedUserTypes.push_front("technician");

    _acceptedRegionTypes.push_front("eu");
    _acceptedRegionTypes.push_front("can");
    _acceptedRegionTypes.push_front("us");
}

/********************************************************************

Description:        Constructor

*********************************************************************/
Cli::~Cli()
{
}

/********************************************************************

Description:        Copy Constructor

*********************************************************************/
Cli::Cli(const Cli &ref)
{
}

/********************************************************************
Name:               run

Description:        Run the command line interface

*********************************************************************/
void Cli::run() {

    std::cout << std::endl;
    std::cout << "Welcome to the Distributech machine interface!" << std::endl;
    std::cout << std::endl;

    _askForUserType();

    if(_userType == "technician") {
        _askForUserName();
        _askToEnableDistribution();
        _askToResetMachine();
    }
    else if (_distributech.getVendorEnable()) {
        _askForUserName();
        _askForRegion();
        _displayItems();
        _askForUserSelection();
        _payForItem();
    }
    else {
       std::cout << "Machine is under maintenance. Come back again later!" << std::endl; 
    }
}

/********************************************************************
Name:               _askForUserType

Description:        Determine the user type

*********************************************************************/
void Cli::_askForUserType() {

    string userType;
    std::list<string>::iterator it;

    std::cout << "Which kind of user are you?"  << std::endl;
    std::cout << "For a customer user, type customer"  << std::endl;
    std::cout << "For an employee user with a NFC badge, type employee"  << std::endl;
    std::cout << "For an technician user with a NFC badge, type technician"  << std::endl;
    std::cout << std::endl;

    // Capture user input and validate it is a known user
    std::cin >> userType;
    for (it = _acceptedUserTypes.begin(); it != _acceptedUserTypes.end(); ++it){
        if (*it == userType) {
            _userType = userType;
            break;
        }
    }

    if (_userType == "UNKNOWN"){
        std::cout << "Unknown user type, exiting program..."  << std::endl;
        throw;
    }
    std::cout << std::endl;
}

/********************************************************************
Name:               _askForUserName

Description:       Validate the user name matches the names for
                    special permissions

*********************************************************************/
void Cli::_askForUserName() {

     string userName;

    // Skip if customer user
    if (_userType != "customer") {

        std::cout << "Use your keypass (aka what is your username)?"  << std::endl;
        std::cout << std::endl;

        // Capture user input and validate it is a known user
        std::cin >> userName;
        _specialUsers.init(_userType, userName);
        // Validates is a special user of any type, otherwise fallback to customer
        if(_specialUsers.isUserNameValid()){
            std::cout << "Successfully logged as special user " << _userType << "!" << std::endl;
        }
        else {
            std::cout << "Username not accepted as a special user, switching to customer user!"  << std::endl;
            _userType = "customer";            
        }

        if (userName == "UNKNOWN"){
            std::cout << "Unknown user name, exiting program..."  << std::endl;
            throw;
        }

        std::cout << std::endl;
    }
}

/********************************************************************
Name:               _askForRegion

Description:        Determine the region type

*********************************************************************/
void Cli::_askForRegion() {

    string regionType;
    std::list<string>::iterator it;

    std::cout << "Which region is the Distributech machine from?"  << std::endl;
    std::cout << "Type either eu (for Europe), can (for Canada) or us (for United-States)"  << std::endl;
    std::cout << std::endl;

    // Capture user input and validate it is a known user
    std::cin >> regionType;
    for (it = _acceptedRegionTypes.begin(); it != _acceptedRegionTypes.end(); ++it){
        if (*it == regionType) {
            _regionType = regionType;
            break;
        }
    }

    if (_regionType == "UNKNOWN"){
        std::cout << "Unknown region type..."  << std::endl;
        throw;
    }

    std::cout << std::endl;
}

/********************************************************************
Name:               _displayItems

Description:        Show the displayed items of the region specific
                    distributech machine

*********************************************************************/
void Cli::_displayItems() {

    std::cout << "Displaying the machine's items!"  << std::endl;
    std::cout << std::endl;

    if (_regionType == "eu") {
        _distributech.loadData(_europeItemsFilePath, _regionType);
    }
    else if (_regionType == "can" || _regionType == "us") {
        _distributech.loadData(_northAmericaItemsFilePath, _regionType);
    }
    else {
        throw;
    }

    _distributech.displayItems();
}

/********************************************************************
Name:               _askForUserSelection

Description:        Show the displayed items of the region specific
                    distributech machine

*********************************************************************/
void Cli::_askForUserSelection() {

    string selection;
    string price;
    string delimiter = "-";

    std::cout << std::endl;
    std::cout << "Which item will you be selecting?"  << std::endl;
    std::cout << "Select it using row number and item name"  << std::endl;
    std::cout << "Example: 1-chaiLatte"  << std::endl;
    std::cout << std::endl;

    std::cin >> selection;

    std::cout << std::endl;

    _selectedRow = selection.substr(0, selection.find(delimiter));
    _selectedItemInRow = selection.erase(0, selection.find(delimiter) + delimiter.length());
}

/********************************************************************
Name:               _payForItem

Description:        User payment input for the item

*********************************************************************/
void Cli::_payForItem() {

    string givenChangeStr;
    float givenChange;
    float changeDifference = 0.0;
    float currentlyPaidChange = 0.0;

    // skip payment if employee and item is coffee
    if (!(_userType == "employee" && _selectedItemInRow == "coffee")) {

        _distributech.displayItemPrice(stoul(_selectedRow) - 1, _selectedItemInRow);
        std::cout << "Enter your change:"  << std::endl;
        std::cout << "Example: 3.00 for a 2.55USD item"  << std::endl;
        std::cout << std::endl;

        //Loop until customer has given at least the item amount of change
        while(1) {
            std::cin >> givenChangeStr;

            std::cout << std::endl;

            givenChange = stof(givenChangeStr);
            changeDifference = _distributech.returnChange(givenChange) + currentlyPaidChange;

            if(changeDifference >= 0.0) {
                _distributech.addItemToRemainingMoney();
                break;
            }
            else{
                currentlyPaidChange = currentlyPaidChange + givenChange;
                std::cout << "Missing " << -1.0 * changeDifference << " to buy the item!" << std::endl;
                std::cout << "Enter the remaining change:"  << std::endl;
                std::cout << std::endl;
            }
        }

        if(changeDifference > 0.0) {
            std::cout << "Returning " << changeDifference << " spare change!" << std::endl;
            std::cout << std::endl;
        }
    }
    std::cout << "Enjoy your " << _selectedItemInRow << "!" << std::endl;
    std::cout << std::endl;

}

/********************************************************************
Name:               _askToEnableDistribution

Description:        Ask the technician to disable/enable the machine

*********************************************************************/
void Cli::_askToEnableDistribution() {

    string enable;

    std::cout << "Do you wish to enable/disable the vendor machine for tests?"  << std::endl;
    std::cout << "Type enable or disable:"  << std::endl;
    std::cout << std::endl;

    // Capture technician input and enable/disable the machine accordingly
    std::cin >> enable;
    std::cout << std::endl;

    if (!(enable == "enable" || enable == "disable")) {
        std::cout << "Wrong user input!"  << std::endl;
        throw;
    }
    
    if(enable == "enable"){
        _distributech.setVendorEnable(true);
        std::cout << "Vendor sucessfully enabled!"  << std::endl;
    }
    else if (enable == "disable") {
        _distributech.setVendorEnable(false);
        std::cout << "Vendor sucessfully disabled!"  << std::endl;
    }

    std::cout << std::endl;
}

/********************************************************************
Name:               _askToResetMachine

Description:        Ask the technician to reset the machine

*********************************************************************/
void Cli::_askToResetMachine() {

    string reset;

    std::cout << "Do you wish to reset the vendor machine? (y/n)"  << std::endl;
    std::cout << std::endl;

    // Capture technician input and reset or not the machine accordingly
    std::cin >> reset;
    std::cout << std::endl;

    if (!(reset == "y" || reset == "n")) {
        std::cout << "Wrong user input!"  << std::endl;
        throw;
    }
    
    if(reset == "y"){
        _distributech.resetMachine();
        std::cout << "Machine sucessfully reset"  << std::endl;
    }

    std::cout << std::endl;
}