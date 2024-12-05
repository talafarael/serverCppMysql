#pragma once
#include <string>
#include "IPasswordManager.h"
class PasswordManager:public IPasswordManager
{
public:
	std::string hashPassword(const std::string& email, const std::string& password);
	bool verifyPassword(const std::string& hashedPassword, const std::string& email, const std::string& password);
};

