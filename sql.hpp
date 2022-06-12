#pragma once
#include <stdlib.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "model.hpp"

using namespace std;
using namespace sql;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "sigma123";

class query
{
private:
    Driver* driver;
    Connection* con;
    PreparedStatement* pstmt;
    ResultSet* res;
    userdata u;
public:
    query()
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema("store");
    }
    //= default;
    ~query()
    {
        delete con;
    }

    void error(SQLException e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    int check_user(string username, string password)
    {
        try
        {
            string query = "SELECT id FROM user WHERE username = (?) AND passwordhash = (?)";
            pstmt = con->prepareStatement(query);
            pstmt->setString(1, username);
            pstmt->setString(2, password);
            res = pstmt->executeQuery();
            int id = 0;
            if (res->next())
            {
                id = res->getInt64("id");
            }
            delete res;
            delete pstmt;
            return id;
        }
        catch (SQLException& e)
        {
            error(e);
            return 0;
        }
    }

    string get_role(int id)
    {
        try
        {
            string query = "SELECT role_name FROM role WHERE user_id = (?)";
            pstmt = con->prepareStatement(query);
            pstmt->setString(1, to_string(id));
            res = pstmt->executeQuery();
            res->next();
            string userrole = res->getString("role_name");
            delete res;
            delete pstmt;
            return userrole;
        }
        catch (SQLException& e)
        {
            error(e);
            return "";
        }
    }

   int add_user(sqluserdata a)
   {
        try
        {
            string query = "INSERT INTO user (username, email, phone, passwordhash) VALUES(?,?,?,?)";
            pstmt = con->prepareStatement(query);
            pstmt->setString(1, a.username);
            pstmt->setString(2, a.email);
            pstmt->setString(3, a.phone);
            pstmt->setString(4, a.password);
            pstmt->execute();
            delete pstmt;

            query = "SELECT LAST_INSERT_ID() AS id";
            pstmt = con->prepareStatement(query);
            res = pstmt->executeQuery();
            res->next();
            int id = res->getInt64("id");
            delete res;
            delete pstmt;

            return id;
        }
        catch (SQLException& e) 
        {
            if (e.getErrorCode() == 1062) 
            {
                cout << "This username already exist." << endl;
                cout << "Please sign in or sign up with another username." << endl;
            }
            error(e);
        }
   }

   void set_role(int id)
   {
       try 
       {
           string query = "INSERT INTO role (user_id) VALUES(?)";
           pstmt = con->prepareStatement(query);
           pstmt->setString(1, to_string(id));
           pstmt->execute();
           delete pstmt;
       }
       catch(SQLException& e)
       {
           error(e);
       }
   }

    userdata get_user_by_id(int id)
    {
        try
        {
            string query = "SELECT id, username, email, phone FROM user WHERE id = (?)";
            pstmt = con->prepareStatement(query);
            pstmt->setString(1, to_string(id));
            res = pstmt->executeQuery();
            userdata user({ 0, "", "", "", ""});
            if (res->next()) {
                user = userdata({ res->getInt("id"),
                                res->getString("username"),
                                res->getString("email"),
                                res->getString("phone")});
            }
            delete res;
            delete pstmt;
            return user;
        }
        catch (SQLException& e)
        {
            error(e);
        }
    }

    /*void get_all_users()
    {
        try
        {
            string query = "select u.id, u.username, u.email, u.phone, r.role_name from user as u join role as r on r.user_id = u.id";
            pstmt = con->prepareStatement(query);
            res = pstmt->executeQuery();
            while (res->next())
            {
                cout << "id: " << res->getInt(tu.id) << " | ";
                cout << "username: " << res->getString(tu.username) << " | ";
                cout << "email " << res->getString(tu.email) << " | ";
                cout << "phone: " << res->getString(tu.phone) << " | ";
                cout << "role: " << res->getString(tu.role) << endl;
            }
            cout << endl;
            delete res;
            delete pstmt;
        }
        catch (SQLException& e)
        {
            error(e);
        }
    }*/

};