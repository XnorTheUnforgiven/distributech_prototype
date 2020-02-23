/*
Name:               abstract.h
Description:        Distributech machine structures
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#ifndef DISTRIBUTECH_H
#define DISTRIBUTECH_H

#include <string>
#include <list>
#include <map>

using std::string;
using std::list;
using std::map;

typedef list<map<unsigned,float>> Items;
typedef map<unsigned,float> ItemsRow;

class DistributechAbstract
{
    public:

        DistributechAbstract(const string itemsFilePath);
        ~DistributechAbstract();
        DistributechAbstract(const DistributechAbstract &ref);

        void displayItems();

    protected:
        void _loadData(const string itemsFilePath);

        const static string _itemsFilePath;
        unsigned _rows;
        unsigned _itemsPerRows;

        Items _items;
};

#endif