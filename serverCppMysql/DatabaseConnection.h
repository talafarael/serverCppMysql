#pragma once
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include "IDatabaseConnection.h"
class DatabaseConnection:public IDatabaseConnection
{
public:
	sql::Connection* startConnection();
	std::unique_ptr<sql::Connection> con;
};

