#pragma once
#include <string>
class IPasswordManager
{
public:
	virtual ~IPasswordManager() = default;
	virtual std::string  hashPassword(const std::string& email, const std::string& password) = 0;
	virtual bool verifyPassword(const std::string& hashedPassword, const std::string& email, const std::string& password) = 0;
};

