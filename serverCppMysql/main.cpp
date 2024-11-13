#include <iostream>

#include "Header.h"
#include "httplib.h"
#include <Windows.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "User.h"
#include "AuthUser.h"
int main() {
    consOl();
    try {
        // Initialize MySQL driver and create a connection
       

       using namespace httplib;
     
    Server svr;

    svr.Get("/hi", [](const Request& req, Response& res) {
      res.set_content("Hello World!", "text/plain");
    });
    svr.Post("/login", [](const Request& req, Response& res) {
      
        nlohmann::json data = nlohmann::json::parse(req.body);

        if (data["name"].is_null()&&data["password"].is_null()) {
            res.status = 400;  
            res.set_content("Error: 'name' cannot be null.", "text/plain");
            return;
        }
            
            User existingUser(data["name"], data["password"]);
            AuthUser authUser(existingUser);
            authUser.Register();
           
        
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
