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

        void loadData(const string itemsFilePath, const string region);
        void displayItems();
        void displayItemPrice(const unsigned row, const string itemName);
        void addItemToRemainingMoney();
        float returnChange(const float change);

        void setVendorEnable(const bool enable);
        bool getVendorEnable();
        void resetMachine();

    private:
        const static string _moneyFilePath;
        const static string _statusFilePath;

        const static string _itemsFilePath;
        Items _items;
        string _currency;
        string _selectedItem;
        float _selectedItemPrice;

        void _setRemainingMoney(const float money);
        float _getRemainingMoney();
        string _regionToCurrency(const string region);
};

#endif