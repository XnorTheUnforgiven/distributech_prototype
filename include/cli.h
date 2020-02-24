/*
Name:               cli.h
Description:        Cli interface manager
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#ifndef CLI_H
#define CLI_H

#include <string>
#include <list>

#include "include\specialUsers.h"
#include "include\distributech.h"

using std::string;
using std::list;

class Cli
{
    public:

        Cli();
        ~Cli();
        Cli(const Cli &ref);

        void run();

    private:
        const static string _europeItemsFilePath;
        const static string _northAmericaItemsFilePath;

        void _askForUserType();
        void _askForUserName();
        void _askForRegion();
        void _displayItems();
        void _askForUserSelection();
        void _payForItem();

        // Technician with access card specific
        void _askToEnableDistribution();
        void _askToResetMachine();

        list<string> _acceptedUserTypes;
        list<string> _acceptedRegionTypes;
        string _userType;
        string _regionType;
        string _selectedRow;
        string _selectedItemInRow;

        SpecialUsers _specialUsers;
        Distributech _distributech;

};

#endif