#include <iostream>
//#include <mysqlx/xdevapi.h>
#include "Header.h"
#include "httplib.h"
#include "Token.h"
#include <Windows.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "User.h"
#include "PostDatabase.h"
#include "CreatePost.h"
#include "AuthUser.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>

#include <cppconn/prepared_statement.h>
#include "PasswordManager.h"


using namespace std;



int main() {
    try {
    consOl();
   

       using namespace httplib;
     
    Server svr;

    svr.Get("/hi", [](const Request& req, Response& res) {
      res.set_content("Hello World!", "text/plain");
    });
    svr.Post("/register", [](const Request& req, Response& res) {

        nlohmann::json data = nlohmann::json::parse(req.body);

        if (data["name"].is_null() && data["password"].is_null()) {
            res.status = 400;
            res.set_content("Error: 'name' cannot be null.", "text/plain");
            return;
        }

        User existingUser(data["name"], data["password"]);
        Token token;
        PasswordManager password;
        AuthUser authUser(existingUser, token,password);
        std::string jwt= authUser.Register();
        nlohmann::json j = { {"token", jwt}};
          
                res.set_content(j.dump(), "text/plain");
           
        });
    svr.Post("/login", [](const Request& req, Response& res) {

        nlohmann::json data = nlohmann::json::parse(req.body);

        if (data["name"].is_null() && data["password"].is_null()) {
            res.status = 400;
            res.set_content("Error: 'name' cannot be null.", "text/plain");
            return;
        }


        User existingUser(data["name"], data["password"]);
        Token token;
        PasswordManager password;
        AuthUser authUser(existingUser, token, password);
        std::string jwt = authUser.Login();
        nlohmann::json j = { {"token", jwt} };
        std::cout << j;
        res.set_content(j.dump(), "text/plain");

        });

    svr.Post("/create", [](const Request& req, Response& res) {

        nlohmann::json data = nlohmann::json::parse(req.body);

        User existingUser("", "");
        Token token;
        PasswordManager password;
        PostDatabase postDatabase(existingUser);
        CreatePost createPost(existingUser,token,password,postDatabase);
        if (data["text"].is_null() && data["title"].is_null()&& data["token"].is_null()) {
            res.status = 400;
            res.set_content("Error: 'name' cannot be null.", "text/plain");
            return;
        }
        createPost.PostCreate(data["token"],data["title"], data["text"]);
      
        res.set_content("all good", "text/plain");
        });

    svr.Get("/stop", [&](const Request& req, Response& res) {
      svr.stop();
    });

    svr.listen("localhost", 1234);
        //std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO users (username, email) VALUES (?, ?)"));

        
        //std::string username = "newUserName";
        //std::string email = "newUserEmail@example.com";

        //// Bind the parameters to the query
        //pstmt->setString(1, username);
        //pstmt->setString(2, email);

        //// Execute the query
        //pstmt->executeUpdate();
        //std::cout << "User successfully added to the database!" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQL state: " << e.getSQLState() << std::endl;
    }
   
    return 0;
}
