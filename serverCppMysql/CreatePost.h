#pragma once
#include "User.h"
#include "IToken.h"
#include "PasswordManager.h"
#include "IPasswordManager.h"
#include "IPostDatabase.h"
class CreatePost
{
public:
	CreatePost(User& user, IToken& token, IPasswordManager& password, IPostDatabase& post_database);
	bool PostCreate(std::string jwt, std::string title, std::string text);
private:
	IToken& token;
	User& user;
	IPasswordManager& password;
	IPostDatabase& post_database;
};

