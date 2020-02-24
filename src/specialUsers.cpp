/*
Name:               specialUsers.cpp
Description:        Components managing special users
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#include <iostream>
#include <fstream>
#include <string>

#include <lib\nlohmann\json.hpp>

#include "include\specialUsers.h"

using std::string;
using std::ifstream;
using json = nlohmann::json;

const string SpecialUsers::_usersFilePath = "..\\doc\\special_users.json";

/********************************************************************
Description:        Constructor

*********************************************************************/
SpecialUsers::SpecialUsers()
{
}

/********************************************************************
Description:        Constructor

*********************************************************************/
SpecialUsers::~SpecialUsers()
{
}

/********************************************************************
Description:        Copy Constructor

*********************************************************************/
SpecialUsers::SpecialUsers(const SpecialUsers &ref)
{
}

/********************************************************************
Description:        Constructor

Args:               userType(const string):
                        Type of user trying to access to the machine
                    userName(const string):
                        UserName of the user trying to access to the
                         machine

*********************************************************************/
void SpecialUsers::init(const string userType, const string userName)
{
    _userType = userType;
    _userName = userName;
}

/********************************************************************
Name:               isUserNameValid

Description:        Validates the user name and user types given are
                     valid according to specialUsers config 

Returns:            (bool) whether the userName is valid according
                     to the userType selected

*********************************************************************/
const bool SpecialUsers::isUserNameValid()
{
    ifstream inputFile;
    inputFile.open(_usersFilePath);

    if (!inputFile.is_open()){
        throw;
    }

    json inputJsonData;
    inputFile >> inputJsonData;

    bool userNameIsValid = false;

    // Iterate through user types
    for (json::iterator userTypeIt = inputJsonData.begin(); userTypeIt != inputJsonData.end(); ++userTypeIt) {
        // If user type was found in config,
        //  iterate through user names to validate it is found in the config
        if(_userType == userTypeIt.key()) {
            for (json::iterator userNameIt = userTypeIt.value().begin(); userNameIt != userTypeIt.value().end(); ++userNameIt) {
                if(_userName == *userNameIt) {
                    userNameIsValid = true;
                }
            }
        }

    }

    inputFile.close();

    return userNameIsValid;

}