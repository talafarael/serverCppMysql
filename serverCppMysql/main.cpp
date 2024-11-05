#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Header.h"
#include "httplib.h"
#include <Windows.h>
int main() {
    consOl();
//    try {
//        // Initialize MySQL driver and create a connection
//        sql::Driver* driver = get_driver_instance();
//        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "azri3FaraElar"));
//
//            
//        con->setSchema("fara");
//
       using namespace httplib;

    Server svr;

    svr.Get("/hi", [](const Request& req, Response& res) {
      res.set_content("Hello World!", "text/plain");
    });
    svr.Post("/login", [](const Request& req, Response& res) {
        
        });


    svr.Get("/stop", [&](const Request& req, Response& res) {
      svr.stop();
    });

    svr.listen("localhost", 1234);
        //std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO users (username, email) VALUES (?, ?)"));

        //// Replace these with actual user data
        //std::string username = "newUserName";
        //std::string email = "newUserEmail@example.com";

        //// Bind the parameters to the query
        //pstmt->setString(1, username);
        //pstmt->setString(2, email);

        //// Execute the query
        //pstmt->executeUpdate();
        //std::cout << "User successfully added to the database!" << std::endl;
    //}
    //catch (sql::SQLException& e) {
    //    std::cerr << "SQL Error: " << e.what() << std::endl;
    //    std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
    //    std::cerr << "SQL state: " << e.getSQLState() << std::endl;
    //}

    return 0;
}
