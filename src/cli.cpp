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

const string Cli::_europeItemsFilePath = "..\\doc\\europe_items.json";
const string Cli::_northAmericaItemsFilePath = "..\\doc\\northAmerica_items.json";

/********************************************************************
Name:       

Description:        Constructor

Args:         

Returns:

Exception:

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
Name:       

Description:        Constructor

Args:         

Returns:

Exception:

*********************************************************************/
Cli::~Cli()
{
}

/********************************************************************
Name:       

Description:        Copy Constructor

Args:         

Returns:

Exception:

*********************************************************************/
Cli::Cli(const Cli &ref)
{
}

/********************************************************************
Name:               run

Description:        Run the command line interface

Args:         

Returns:

Exception:

*********************************************************************/
void Cli::run() {
    std::cout << std::endl;
    std::cout << "Welcome to the Distributech machine interface!" << std::endl;
    std::cout << std::endl;
    _askForUserType();
    _askForUserName();
    _askForRegion();
    _showItems();
}

/********************************************************************
Name:               _askForUserType

Description:        Determine the user type

Args:         

Returns:

Exception:

*********************************************************************/
void Cli::_askForUserType() {

    string userType;

    std::cout << "Which kind of user are you?"  << std::endl;
    std::cout << "For a customer user, type customer"  << std::endl;
    std::cout << "For an employee user with a key pass, type employee"  << std::endl;
    std::cout << "For an technician user with a key pass, type technician"  << std::endl;
    std::cout << std::endl;

    // Capture user input and validate it is a known user
    std::cin >> userType;
    for ( std::list<string>::iterator it = _acceptedUserTypes.begin(); it != _acceptedUserTypes.end(); ++it){
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

Args:         

Returns:

Exception:

*********************************************************************/
void Cli::_askForUserName() {

    string userName;

    std::cout << "Use your keypass (aka what is your username)?"  << std::endl;
    std::cout << std::endl;

    // Capture user input and validate it is a known user
    std::cin >> userName;
    _specialUsers.init(_userType, userName);
    // Validates is a special user of any type, otherwise fallback to customer
    if(!_specialUsers.isUserNameValid()){
        _userType = "customer";
    }

    if (userName == "UNKNOWN"){
        std::cout << "Unknown user type, exiting program..."  << std::endl;
        throw;
    }

    std::cout << std::endl;

}

/********************************************************************
Name:               _askForRegion

Description:        Determine the region type

Args:         

Returns:

Exception:

*********************************************************************/
void Cli::_askForRegion() {

    string regionType;

    std::cout << "Which region is the Distributech machine from?"  << std::endl;
    std::cout << "Type either eu (for Europe), can (for Canada) or us (for United-States)"  << std::endl;

    // Capture user input and validate it is a known user
    std::cin >> regionType;
    for ( std::list<string>::iterator it = _acceptedUserTypes.begin(); it != _acceptedUserTypes.end(); ++it){
        if (*it == regionType) {
            _regionType = regionType;
            break;
        }
    }

    if (_regionType == "UNKNOWN"){
        std::cout << "Unknown region type..."  << std::endl;
        throw;
    }

}

/********************************************************************
Name:               _showItems

Description:        Show the displayed items of the region specific
                    distributech machine

Args:         

Returns:

Exception:

*********************************************************************/
void Cli::_showItems() {
    std::cout << "Displaying the machine's items!"  << std::endl;
    std::cout << std::endl;

    if (_regionType == "eu") {
        _distributech.loadData(_europeItemsFilePath);
    }
    else if (_regionType == "can" || _regionType == "us") {
        _distributech.loadData(_northAmericaItemsFilePath);
    }
    else {
        throw;
    }

    _distributech.displayItems();

}