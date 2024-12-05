#pragma once
#include <string>


class IPostDatabase {
public:
	virtual ~IPostDatabase() = default;
	virtual bool createPost(const std::string& title, const std::string& text, const int id) = 0;
};