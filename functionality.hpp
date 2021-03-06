#pragma once
#pragma warning(disable : 4996)
#include "sha256.hpp"
#include "sql.hpp"

class function
{
private:
    query* q;
    string hashfunc(string a);

public:
    function(query* q);
    ~function();
    int sign_up(string username, string email, string phone, string password);
    int sign_in(string username, string password);
    string get_user_role(int id);
    string get_user_name(int id);
    void set_role(int id);
    void changing_role(int id, string new_role);
    void changing_status(int id, string new_status);
    void user_orders(int id);
    void select_user_by_id(int id, userdata& user);
    void select_soap_by_id(int id, soap_by_id& s);
    void get_user_table();
    void get_soap_table();
    void get_order_table();
    int add_soap(string sn, int app, string c, double p, int s, int ti);
    int add_order(int user_id, soap_ordered so);
    void delete_user(int id);
    void changing_amount(int id, int amount);
    int getting_quantity(int id);
};

function::function(query* q)
{
    this->q = q;
}

function::~function()
{
    delete this->q;
}

int function::sign_up(string username, string email, string phone, string password)
{
    return this->q->add_user({0, username, email, phone, hashfunc(password) });
}

int function::sign_in(string username, string password)
{
    return this->q->check_user(username, hashfunc(password));
}

string function::get_user_role(int id)
{
    if (id == 0)
        cout << "There is no user with such id";
    return this->q->get_role(id);
}

void function::set_role(int id)
{
    this->q->set_role(id);
    if (id == 0)
        cout << "There is no user with such id";
}

string function::get_user_name(int id)
{
    if (id == 0)
        cout << "There is no user with such id";
    return this->q->get_user_name_by_id(id);
}

void function::changing_role(int id, string new_role)
{
    this->q->change_role(id, new_role);
    if (id == 0)
        cout << "There is no user with such id";
}

void function::changing_amount(int id, int amount)
{
    this->q->change_amount(id, amount);
    if (id == 0)
        cout << "There is no soap with such id";
}

int function::getting_quantity(int id)
{
    if (id == 0)
        cout << "There is no order with such id";
    return this->q->get_quantity(id);
}

void function::changing_status(int id, string new_status)
{
    this->q->change_status(id, new_status);
    if (id == 0)
        cout << "There is no order with such id";
}

void function::delete_user(int id)
{
    this->q->delete_user(id);
    if (id == 0)
        cout << "There is no user with such id";
}

void function::user_orders(int id)
{
    this->q->get_user_order_by_id(id);
    if (id == 0)
        cout << "There is no user with such id";
}

void function::select_user_by_id(int id, userdata& user)
{
    user = this->q->get_user_by_id(id);
    if (user.id == 0)
        cout << "There is no user with such id";
}

void function::select_soap_by_id(int id, soap_by_id& s)
{
    s = this->q->get_soap_by_id(id);
    if (s.id == 0)
        cout << "There is no user with such id";
}

void function::get_user_table()
{
    this->q->get_all_users();
}

void function::get_soap_table()
{
    this->q->get_all_soap();
}

void function::get_order_table()
{
    this->q->get_all_orders();
}

int function::add_soap(string sn, int app, string c, double p, int s, int ti)
{
    return this->q->add_soap({0, sn, app, c, p, s, ti });
}

int function::add_order(int user_id, soap_ordered so)
{
    return this->q->add_order(user_id, so);
}

string function::hashfunc(string a)
{
    string out;
    SHA256 sha;
    sha.update(a);
    uint8_t* digest = sha.digest();
    out = SHA256::toString(digest);
    delete[] digest;
    return out;
}



