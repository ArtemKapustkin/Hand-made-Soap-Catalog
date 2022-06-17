#pragma once
#include "functionality.hpp"
#include <string>

class interface
{
private:
    userdata u;
    function* func;
    int input_correction();
public:
    interface(function * func);
    ~interface();
    void main_menu();
    void role_menu(string role);
    void admin_menu();
    void manager_menu();
    void client_menu();
    void start_programm();
    void sign_up_form();
    void sign_in_form();
    void adding_soap();
    void adding_order(userdata u);
    void user_list_menu();
    void order_menu();
    void change_role();
    void change_status();
    void delete_user();
};

int interface::input_correction()
{
    string input;
    int key = -1;
    cout << "> ";
    cin >> input;
    try {
        key = stoi(input);
    }
    catch (const exception& e) {
        cout << "Invalid input" << endl;
        system("pause");
    }
    return key;
}

interface::interface(function* func) 
{
    this->func = func;
}

interface::~interface() 
{
    delete this->func;
}

void interface::start_programm() 
{
    while (true) 
    { 
        main_menu(); 
    }
};

void interface::adding_soap()
{
    system("cls");
    cout << "Soap Form" << endl;
    string sn, c;
    int app, s, ti;
    double p;
    cout << "Enter soap name in brackets" << endl << "< ";
    getchar();
    getline(cin, sn);
    cout << endl << "Enter how much soap pieces in set (amount per pack)" << endl ;
    app = input_correction();
    cout << endl << "Enter collection" << endl << "< ";
    getchar();
    getline(cin, c);
    cout << endl << "Enter price" << endl << "< ";
    cin >> p;
    cout << endl << "Enter how many of these sets are in stock" << endl;
    s = input_correction();;
    cout << endl << "Select type id:" << endl;
    cout << "(1) Soap Floristy" << endl;
    cout << "(2) Care Product" << endl;
    cout << "(3) Gift Set" << endl;
    cout << "(4) Thematic Set" << endl;
    cout << "(5) Single" << endl;
    ti = input_correction();
    
    int soap_id = func->add_soap(sn, app, c, p, s, ti);
}

void interface::adding_order(userdata u)
{
    soap_ordered so;
    soap_by_id s;
    int quan;
    int user_id = u.id;
    cout << "Order Form" << endl;
    cout << "Enter ID of soap, you want to order " << endl;
    cout << "< ";
    cin >> so.soap_id;
    func->select_soap_by_id(so.soap_id, s);
    so.soap_price = s.price;
    if (s.quantity != 0)
    {
        cout << "Enter quantity you want to order : " << endl;
        cout << "< ";
        cin >> quan;
        if (quan > s.quantity)
            cout << "Sorry, we have not so much of this one in stock, try to order less units or wait for replenishment.";
        else
        {
            so.quantity = quan;
            if (so.quantity >= 5)
                so.discount = 5;
            else
                so.discount = 0;
            cout << "Your order have this info:" << endl;
            cout << "Soap: " << s.soap_name << ", price: " << so.soap_price << ", quantity: " << so.quantity << ", discount(5% if you order more than five units): " << so.discount << endl;
            int i = func->add_order(u.id, so);
            cout << "Order succesfully added!";
        }
            
    }
    else
    {
        cout << "Sorry, we have not this one in stock, try something else or wait for replenishment.";
    }
}

void interface::change_status()
{
    int id;
    string new_status;
    cout << "Enter id of order, which status you want to change:" << endl;
    id = input_correction();
    cout << "Enter new status (accepted/rejected/completed):" << endl << "< ";
    cin >> new_status;
    func->changing_status(id, new_status);
    cout << "This order status successfully changed, now it is - " << new_status << endl;
}

void interface::change_role()
{
    string new_role;
    int id;
    cout << "Enter id of user, whose role you want to change:" << endl;
    id = input_correction();
    string username_by_id = func->get_user_name(id);
    cout << "Enter new role (client/manager/admin):" << endl << "< ";
    cin >> new_role;
    func->changing_role(id, new_role);
    cout << "Role of user " << username_by_id << " successfully changed, now user role is - " << new_role << endl;
}

void interface::delete_user()
{
    int id;
    cout << "Enter id of user, you want to delete:" << endl;
    id = input_correction();
    string username_by_id = func->get_user_name(id);
    func->delete_user(id);
    cout << "User " << username_by_id << " is successfully deleted!" <<  endl;
}

void interface::order_menu()
{
    cout << "> Change role (1)" << endl;
    cout << "> Exit (2)" << endl;
    int var = input_correction();
    switch (var)
    {
    case 1:
        change_status();
        return;
    case 2:
        return;
    default:
        return;
    }
}

void interface::user_list_menu()
{
    cout << "> Change role (1)" << endl;
    cout << "> Delete user (2)" << endl;
    cout << "> Exit (3)" << endl;
    int var = input_correction();
    switch (var)
    {
    case 1:
        change_role();
        return;
    case 2:
        delete_user();
        return;
    case 3:
        exit(EXIT_SUCCESS);
        return;
    default:
        return;
    }
}

void interface::admin_menu()
{
    system("cls");
    cout << "> Open users list (1)" << endl;
    cout << "> Open soap list (2)" << endl;
    cout << "> Add new soap (3)" << endl;
    cout << "> Exit (4)" << endl;
    int var = input_correction();
    switch (var)
    {
    case 1:
        func->get_user_table();
        system("pause");
        user_list_menu();
        return;
    case 2:
        func->get_soap_table();
        system("pause");
        return;
    case 3:
        adding_soap();
        system("pause");
        return;
    case 4:
        system("cls");
        start_programm();
    default:
        system("pause");
        return;
    }
}

void interface::manager_menu()
{
    system("cls");
    cout << "> Open order list (1)" << endl;
    cout << "> Open soap list (2)" << endl;
    cout << "> Add new soap (3)" << endl;
    cout << "> Exit (4)" << endl;
    int var = input_correction();
    switch (var)
    {
    case 1:
        func->get_order_table();
        system("pause");
        order_menu();
        return;
    case 2:
        func->get_soap_table();
        system("pause");
        return;
    case 3:
        adding_soap();
        system("pause");
        return;
    case 4:
        system("cls");
        start_programm();
    default:
        system("pause");
        return;
    }
}

void interface::client_menu()
{
    system("cls");
    cout << "> Open soap list (1)" << endl;
    cout << "> Make an order (2)" << endl;
    cout << "> My orders (3)" << endl;
    cout << "> Exit (4)" << endl;
    int var = input_correction();
    switch (var)
    {
    case 1:
        func->get_soap_table();
        system("pause");
        return;
    case 2:
        adding_order(u);
        system("pause");
        return;
    case 3:
        func->user_orders(u.id);
        system("pause");
        return;
    case 4:
        system("cls");
        start_programm();
    default:
        system("pause");
        return;
    }
}

void interface::sign_up_form()
{
    sqluserdata a;
    system("cls");
    cout << "Enter your username(it cannot be longer than 15 symbols):" << endl;
    cin >> a.username;
    while (a.username.size() > 15)
    {
        cout << "You enter username, that longer than 15 symbols, please enter shorter one:" << endl;
        cin >> a.username;
    }

    cout << "Enter your email:" << endl;
    cin >> a.email;

    cout << "Enter your phone number:" << endl;
    cin >> a.phone;

    cout << "Enter your password: " << endl;
    cin >> a.password;

    int id = this->func->sign_up(a.username, a.email, a.phone, a.password);
    if (id != 0)
    {
        cout << "You're successfully sign up!" << endl;
        this->func->set_role(id);
    }
    system("pause");
}

void interface::sign_in_form()
{
    string n, p;
    system("cls");
    cout << "Enter your username: " << endl;
    cin >> n;
    cout << "Enter your password: " << endl;
    cin >> p;
    int id = this->func->sign_in(n, p);
    if (id != 0)
    {
        cout << "Success authorization into " << n << " account!" << endl;
        userdata user;
        this->func->select_user_by_id(id, user);
        this->u.id = id;
        this->u.username = user.username;
        this->u.email = user.email;
        this->u.phone = user.phone;
        this->u.role = this->func->get_user_role(id);
        cout << "Role" << u.role << endl;
        system("pause");
    }
    else
    {
        cout << "Please try one more time, you entered incorrect username or password.";
        system("pause");
    }
    role_menu(u.role);
}

void interface::main_menu()
{
    system("cls");
    cout << "> Sign up (1)" << endl;
    cout << "> Log in (2)" << endl;
    cout << "> Exit (3)" << endl;
    int var = input_correction();
    switch (var)
    {
    case 1:
        sign_up_form();
        break;
    case 2:
        sign_in_form();
        system("pause");
        break;
    case 3:
        exit(EXIT_SUCCESS);
        break;
    default:
        system("pause");
        return;
    }
}

void interface::role_menu(string role)
{
    int selector;
    system("cls");
    if (role == "admin")
        selector = 1;
    else if (role == "manager")
        selector = 2;
    else if (role == "client")
        selector = 3;
    switch (selector)
    {
    case 1:
        cout << "Success authorization as admin!" << endl;
        while (true)
        {
            admin_menu();
        }
        break;
    case 2:
        cout << "Success authorization as manager!" << endl;
        while (true)
        {
            manager_menu();
        }
        break;
    case 3:
        cout << "Success authorization as client!" << endl;
        while (true)
        {
            client_menu();
        }
        break;
    }
}


