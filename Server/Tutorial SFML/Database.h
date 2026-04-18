#pragma once

#include <string>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "Bcrypt/bcrypt.h"

#define SERVER "127.0.0.1:3306"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "tres_en_raya_online"

#define DB Database::Instance()

class Database
{
public:
    static Database* Instance() {
        static Database db;

        return &db;
    }

    bool Connect();
    void Disconnect();

    bool RegisterUser(const std::string& nickname, const std::string& password);
    bool LoginUser(const std::string& nickname, const std::string& password, int& userId);

private:
    sql::Driver* driver;
    sql::Connection* con;

private:
    Database();
    ~Database();

    bool UserExists(const std::string& nickname);
};