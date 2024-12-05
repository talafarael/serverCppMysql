#pragma once
#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <memory>
class User
{
public:         
   User(std::string name,std::string password);


    std::string name;
    std::string password;
    
    
};

