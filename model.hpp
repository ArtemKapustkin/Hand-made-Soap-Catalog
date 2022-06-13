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

struct soap
{
    int soap_id;
    string soap_name;
    int amount_per_pack;
    string collection;
    float price;
    int stock;
    string type_name;
};
