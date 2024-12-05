#pragma once
#include <string>

class IToken {
public:
	virtual ~IToken() = default;
	virtual std::string generateToken(std::string id)=0;
	virtual std::string decodeToken(std::string& token)=0;
};