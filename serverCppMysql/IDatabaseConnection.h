#pragma once
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <memory>
class IDatabaseConnection {
public: 
	virtual ~IDatabaseConnection() = default;
	virtual sql::Connection* startConnection() = 0;
};