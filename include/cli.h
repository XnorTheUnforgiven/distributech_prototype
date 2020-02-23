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

using std::string;
using std::list;

class DistributechCli
{
    public:

        DistributechCli();
        ~DistributechCli();
        DistributechCli(const DistributechCli &ref);

        void run();

    private:

        void _askForUserType();
        void _askForUserName();
        void _askForRegion();
        void _showItems();

        list<string> _acceptedUserTypes;
        list<string> _acceptedRegionTypes;
        string _userType;
        string _regionType;

        DistributechSpecialUsers _specialUsers;

        // Customer specific
        void _displayItemSelection();

        // Employee with access card specific

        // Technician with access card specific
        void _enableDistribution(bool enable);
        void _resetDistribution(float change);

};

#endif