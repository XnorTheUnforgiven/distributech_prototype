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
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

typedef map<string,float> ItemsRow;
typedef vector<ItemsRow> Items;


class Distributech
{
    public:

        Distributech();
        ~Distributech();
        Distributech(const Distributech &ref);

        void loadData(const string itemsFilePath, string region);
        void displayItems();
        void displayItemPrice(unsigned row, string itemName);

    private:
        const static string _itemsFilePath;
        Items _items;
        string _currency;

        string _regionToCurrency(string region);
};

#endif