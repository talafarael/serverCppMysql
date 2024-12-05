#pragma once
#include "User.h"
#include <string>
#include "IPostDatabase.h"
class PostDatabase : public IPostDatabase
{
public:
	PostDatabase(User& user);
	bool createPost(const std::string& title,const std::string& text,const int id);
private:
	User& user;

};

