/*
Name:               cli.h
Description:        Cli interface for distributech
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#ifndef DISTRIBUTECH_CLI_H
#define DISTRIBUTECH_CLI_H

#include "include\distributech\abstract.h"

class DistributechCli: DistributechCli
{
    public:

        DistributechCli();
        ~DistributechCli();
        DistributechCli(const DistributechCli &ref);

        void run();

    private:

        void _askForUserType();
        void _askForRegion();

        // Customer specific
        void _displayItemSelection();

        // Employee with access card specific

        // Technician with access card specific
        void _enableDistribution(bool enable);
        void _resetDistribution(float change);
        void _displayItemSelection();

};

#endif