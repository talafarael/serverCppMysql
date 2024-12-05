#pragma once
#include "User.h"
#include "IToken.h"
#include "PasswordManager.h"
#include "IPasswordManager.h"
#include <string>
class AuthUser
{

public:
    AuthUser(User& user, IToken& token,IPasswordManager& password);
std::string Register();
std::string Login();
private:
    IToken& token;
    User& user;
    IPasswordManager& password;
};

