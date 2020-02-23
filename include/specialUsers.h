/*
Name:               specialUsers.h
Description:        Components managing special users
Author:             Xavier Mercure-Gagnon
Date of creation:   22-02-2020
Last edit:          22-02-2020
*/

#ifndef SPECIAL_USERS_H
#define SPECIAL_USERS_H

#include <string>

using std::string;

class SpecialUsers
{
    public:

        SpecialUsers();
        ~SpecialUsers();
        SpecialUsers(const SpecialUsers &ref);

        bool isEmployee(string user);
        bool isTechnician(string user);

        void init(string userType, string userName);
        const bool isUserNameValid();

    private:
        const static string _usersFilePath;

        string _userName;
        string _userType;
};

#endif