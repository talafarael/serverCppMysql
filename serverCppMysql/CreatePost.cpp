#include "CreatePost.h"
#include "User.h"
#include "IToken.h"
#include "Token.h"
#include "PasswordManager.h"
#include "IPasswordManager.h"
#include "IPostDatabase.h"
#include <nlohmann/json.hpp>
CreatePost::CreatePost(User& user, IToken& token, IPasswordManager& password, IPostDatabase& post_database) : user(user), token(token), password(password), post_database(post_database){}
bool CreatePost::PostCreate(std::string jwt, std::string title, std::string text) {

	 std::string id =this->token.decodeToken(jwt);
	 if (id == "") {
		 return false;
	 }
	 
	 nlohmann::json jsonID= nlohmann::json::parse(id);
	 if (jsonID["id"].is_null() || !jsonID["id"].is_string()) {
		 return false;
	 }
	 int numericId = std::stoi(jsonID["id"].get<std::string>());
	 this->post_database.createPost(title, text, numericId);
	 return true;
}