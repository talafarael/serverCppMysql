#include "PostDatabase.h"
#include "User.h"


PostDatabase::PostDatabase(User& user) : user(user) {};

bool PostDatabase::createPost(const std::string& title, const std::string& text, const int id) {
    try{     std::cout << "suka";
    sql::Connection* con = user.getConnection();
    if (!con) {
        std::cerr << "Failed to get database connection." << std::endl;
       return true;
 }
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("INSERT INTO posts (title, text, user_id) VALUES (?, ?, ?)")
    );
  
    pstmt->setString(1, title);
    pstmt->setString(2, text);
    pstmt->setInt(3, id);

    pstmt->executeUpdate();
    return true;
}
catch (sql::SQLException& e) {
    std::cerr << "SQL Error: " << e.what() << std::endl;
    return true;
}
}


