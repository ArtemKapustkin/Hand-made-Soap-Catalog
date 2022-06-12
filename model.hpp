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