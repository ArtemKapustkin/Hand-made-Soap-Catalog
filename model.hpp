#pragma once
#include <iostream>

using namespace std;

enum class role_name
{
    guest, client, manager, admin
};

struct sqluserdata
{
    int id;
    string username;
    string email;
    string phone;
    string password;
};

struct userdata
{
    int id;
    string username;
    string email;
    string phone;
    string role;
};

struct soapdata
{
    int soap_id;
    string soap_name;
    int amount_per_pack;
    string collection;
    double price;
    int stock;
    int type_id;
};

enum status
{
    registered = 1, 
    accepted = 2, 
    rejected = 3, 
    completed = 4
};

struct soap_ordered
{
    int soap_id;
    double soap_price;
    int quantity;
    int discount;
};

struct soap_by_id
{
    int id;
    string soap_name;
    double price;
    int quantity;
    soap_by_id()
    {
        id = 0;
        soap_name = "";
        price = 0.00;
        quantity = 0;
    }
    soap_by_id(int id, string name, double price, int q)
    {
        this->id = id;
        this->soap_name = name;
        this->price = price;
        this->quantity = q;
    }
};