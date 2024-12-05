#pragma once
#include "User.h"
#include <string>
#include "IPostDatabase.h"
#include "IDatabaseConnection.h"
#include "Post.h"
class PostDatabase : public IPostDatabase
{
public:
	PostDatabase(IDatabaseConnection& database);
	bool createPost(const std::string& title,const std::string& text,const int id);
//std::vector<Post> 
private:
	IDatabaseConnection& database;

};

