#pragma once
#include "User.h"
class AuthUser
{

public:
    AuthUser(User& user);
    bool Register();
private:
    User& user;
};

