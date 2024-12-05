

#include <Windows.h> 
//#include "bcrypt.h"
#include "AuthUser.h"

#include <iostream>
//#include "bcrypt.h"
#include "openssl/sha.h"
#include <iomanip>
#include <sstream>
#include "IPasswordManager.h"

#include "qtbcrypt.h"
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sodium.h>
 #include <string>
#include "IToken.h"
AuthUser::AuthUser(User& user,IToken& token, IPasswordManager& password) : user(user),token(token), password(password) {}


std::string AuthUser::Register() {
    try {

        std::string password = "top_secret";

        sql::Connection* con = user.getConnection();
        if (!con) {
            std::cerr << "Failed to get database connection." << std::endl;
            return "error";
        }

      
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO users (name, password) VALUES (?, ?)"));
        

        std::string username = user.name;
        std::string email = user.password;
        std::string hashed_password =this->password.hashPassword(email, password);
        std::cout << hashed_password;
        pstmt->setString(1, username);
        pstmt->setString(2, hashed_password);

       
        pstmt->executeUpdate();



        std::unique_ptr<sql::PreparedStatement> idStmt(con->prepareStatement("SELECT LAST_INSERT_ID()"));
        std::unique_ptr<sql::ResultSet> res(idStmt->executeQuery());

        if (res->next()) {
            int lastInsertId = res->getInt(1); 
           
       
          std::string jwt= token.generateToken(std::to_string(lastInsertId));
         
          return jwt;
         }
        return "";
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return "error";
    }
}
std::string AuthUser::Login() {
    std::string secret = "top_secret";

    sql::Connection* con = user.getConnection();
    //std::string name = this->token
    if (!con) {
        std::cerr << "Failed to get database connection." << std::endl;
        return "error";
    }
   
    
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("SELECT id,name, password FROM users WHERE name= ?"));

   
    pstmt->setString(1,user.name);

  
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

   
    if (res->next()) {
        std::cout << "Name: " << res->getString("name")
            << res->getString("password") << std::endl;
        bool checkPassword = password.verifyPassword(res->getString("password"), user.password, secret);
        std::cout << checkPassword;
        if (checkPassword) {
            std::cout << "aa";
            std::cout << res->getInt("id");
            std::string jwt = token.generateToken(res->getString("id"));
            std::cout << jwt;

            return jwt;
        }
        return "";
    }
    else {
        //std::cout << "User with id " << id << " not found." << std::endl;
        return "";
    }

}