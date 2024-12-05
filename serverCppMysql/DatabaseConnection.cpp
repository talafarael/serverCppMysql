#include "DatabaseConnection.h"

sql::Connection* DatabaseConnection::startConnection() {
    if (!con) {
        try {
            sql::Driver* driver = get_driver_instance();
            con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3306", "root", "azri3FaraElar"));
            con->setSchema("fara");
        }
        catch (sql::SQLException& e) {
            std::cerr << "Ошибка при подключении к базе данных: " << e.what() << std::endl;
            return nullptr;
        }
    }
    return con.get();
}