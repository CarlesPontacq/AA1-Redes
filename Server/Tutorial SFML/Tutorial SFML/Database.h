#pragma once

#include <string>

#include "mysqlConnector/include/jdbc/mysql_connection.h"
#include "mysqlConnector/include/jdbc/cppconn/driver.h"
#include "mysqlConnector/include/jdbc/cppconn/connection.h"

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