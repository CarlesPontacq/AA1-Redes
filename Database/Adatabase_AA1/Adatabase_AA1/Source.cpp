#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#define SERVER "127.0.0.1:3306"
#define USERNAME "root"
#define PASSWORD "enti"
#define DATABASE "Videogame"


void ConnectDatabase(sql::Driver*& driver, sql::Connection*& con) {
    try {
        driver = get_driver_instance();
        con = driver->connect(SERVER, USERNAME, PASSWORD);
        std::cout << "Connection done." << std::endl;
    }
    catch (sql::SQLException e) {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
    }
}

void DisconnectDatabase(sql::Connection* con) {
    con->close();

    if (con->isClosed()) {
        std::cout << "Connection close." << std::endl;
        delete con;
    }
}

void GetAllUsers(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT username FROM users");

        std::cout << "Users in the database:" << std::endl;

        while (res->next()) {
            std::cout << res->getString("username") << std::endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error while fetching users: " << e.what() << std::endl;
    }
}

void UpdatePassword(sql::Connection* con, std::string user, std::string newPassword) {
    try {
        sql::Statement* stmt = con->createStatement();
        std::string query = "UPDATE users SET password = '" + newPassword + "' WHERE username = '" + user + "'";

        int affected_rows = stmt->executeUpdate(query);
        std::cout << "Number of rows affected: " << affected_rows << std::endl;

        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error while updating password: " << e.what() << std::endl;
    }
}

void main()
{
    sql::Driver* driver;
    sql::Connection* con;

    ConnectDatabase(driver, con);

    con->setSchema(DATABASE);
    GetAllUsers(con);
    UpdatePassword(con, "Radev", "salvarAlumnos");
    DisconnectDatabase(con);

    system("pause");
}