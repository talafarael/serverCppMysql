

//#include <Windows.h> 
//#include "Bcrypt.h"?
#include "AuthUser.h"
#include <iostream>
//#include "bcrypt.h"
 #include <string>
AuthUser::AuthUser(User& user) : user(user) {}
//#pragma comment (lib, "bcrypt.lib")
bool AuthUser::Register() {
    try {
       
        sql::Connection* con = user.getConnection();
        if (!con) {
            std::cerr << "Failed to get database connection." << std::endl;
            return false;
        }

      
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO users (name, password) VALUES (?, ?)"));
        

        std::string username = user.name;
        std::string email = user.password;

      
        pstmt->setString(1, username);
        pstmt->setString(2, email);

       
        pstmt->executeUpdate();
        std::cout << "User successfully added to the database!" << std::endl;

        return true;  

    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;  
    }
}