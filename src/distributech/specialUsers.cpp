/*
Name:               cli.cpp
Description:        Cli interface for distributech
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#include <iostream>
#include <fstream>
#include <string>

#include <lib\nlohmann\json.hpp>

#include "include\distributech\specialUsers.h"

using std::string;
using std::ifstream;
using json = nlohmann::json;

const string DistributechSpecialUsers::_usersFilePath = "/doc/special_users.json";

/********************************************************************
Name:       

Description:        Constructor

Args:         

Returns:

Exception:

*********************************************************************/
DistributechSpecialUsers::DistributechSpecialUsers()
{
}

/********************************************************************
Name:       

Description:        Constructor

Args:         

Returns:

Exception:

*********************************************************************/
DistributechSpecialUsers::~DistributechSpecialUsers()
{
}

/********************************************************************
Name:       

Description:        Copy Constructor

Args:         

Returns:

Exception:

*********************************************************************/
DistributechSpecialUsers::DistributechSpecialUsers(const DistributechSpecialUsers &ref)
{
}

/********************************************************************
Name:               Initialise the class with known user type and name

Description:        Constructor

Args:         

Returns:

Exception:

*********************************************************************/
void DistributechSpecialUsers::init(string userType, string userName)
{
    _userType = userType;
    _userName = userName;
}

/********************************************************************
Name:               Validates the user name and user types given are
                     valid according to specialUsers config 

Description:        Constructor

Args:         

Returns:

Exception:

*********************************************************************/
const bool DistributechSpecialUsers::isUserNameValid()
{
    ifstream inputFile;
    inputFile.open(_usersFilePath);

    if (!inputFile.is_open()){
        throw;
    }

    json inputJsonData;
    inputFile >> inputJsonData;

    std::cout << inputJsonData << '\n';

    bool userNameIsValid = false;

    // Iterate through user types
    for (json::iterator userTypeIt = inputJsonData.begin(); userTypeIt != inputJsonData.end(); ++userTypeIt) {
        // If user type was found in config,
        //  iterate through user names to validate it is found in the config
        if(_userType == userTypeIt.key()) {
            for (json::iterator userNameIt = userTypeIt.value().begin(); userNameIt != userTypeIt.value().end(); ++userNameIt) {
                std::cout << *userNameIt << '\n';
                if(_userName == *userNameIt) {
                    userNameIsValid = true;
                }
            }
        }

    }

    return userNameIsValid;

}