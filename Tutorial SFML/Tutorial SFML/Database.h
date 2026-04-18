#pragma once

#include <string>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#define SERVER "127.0.0.1:3306"
#define USERNAME "root"
#define PASSWORD "enti"
#define DATABASE "tres_en_raya_online"

class Database
{
public:
    Database();
    ~Database();

    bool Connect();
    void Disconnect();

    bool RegisterUser(const std::string& nickname, const std::string& password);
    bool LoginUser(const std::string& nickname, const std::string& password, int& userId);

private:
    sql::Driver* driver;
    sql::Connection* con;

private:
    bool UserExists(const std::string& nickname);
};