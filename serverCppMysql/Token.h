#pragma once
#include <string>
#include "IToken.h"
class Token:public IToken
{
public:
	std::string generateToken(std::string id);
	std::string decodeToken(std::string& token);
};

