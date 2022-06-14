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


void interface::admin_menu()
{
    system("cls");
    cout << "> Open users list (1)" << endl;
    cout << "> Open soap list (2)" << endl;
    cout << "> Exit (3)" << endl;
    int var = input_correction();
    switch (var)
    {
    case 1:
        func->get_user_table();
        system("pause");
        break;
    case 2:
        func->get_soap_table();
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

void interface::manager_menu()
{
    system("cls");
    cout << "> Sign up (1)" << endl;
    cout << "> Log in (2)" << endl;
    cout << "> Exit (3)" << endl;

}

void interface::client_menu()
{
    system("cls");
    cout << "> Sign up (1)" << endl;
    cout << "> Log in (2)" << endl;
    cout << "> Exit (3)" << endl;

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
        admin_menu();
        system("pause");
        break;
    case 2:
        cout << "Success authorization as manager!" << endl;
        manager_menu();
        break;
    case 3:
        cout << "Success authorization as client!" << endl;
        client_menu();
        break;
    }
}


