#pragma once
#include "User.h"
#include "IToken.h"
#include "PasswordManager.h"
#include "IPasswordManager.h"
#include <string>
#include "IDatabaseConnection.h"
class AuthUser
{

public:
    AuthUser(User& user, IToken& token,IPasswordManager& password, IDatabaseConnection& database);
std::string Register();
std::string Login();
private:
    IToken& token;
    User& user;
    IPasswordManager& password;
    IDatabaseConnection& database;
};

