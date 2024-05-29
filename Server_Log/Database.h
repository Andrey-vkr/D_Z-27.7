#pragma once
#include <iostream>
#include <mysql.h>
#include <string.h>
#include <vector>


constexpr auto db_host = "localhost";
constexpr auto db_user = "root";
constexpr auto db_password = "root";
constexpr auto db_name = "db";

class Database
{
public:
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;

    bool connectDatabase(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName);
    void disconnect();

    bool checkLogin(std::string login, std::string password);
    std::string getName(std::string login);

    std::string checkRegister(std::string login, std::string name, std::string password);
    bool registerUser(std::string login, std::string name, std::string password);

    bool addMessage(std::string from, std::string to, std::string message);
    std::vector<std::string> getAllMessages(std::string login);
    std::vector<std::string> getAllUsers();

private:
    std::vector<std::string> convertResToVector(MYSQL_RES* res);
};

