#include <cstdlib>
#include <iostream>

#ifdef OS_WINDOWS
#include <mysql.h>
#elif OS_MACOS
#include <mysql/mysql.h>
#elif OS_LINUX
#include <mysql/mysql.h>
#endif

#include <Foundation/db.hpp>

#include <Commands/TestConnection.hpp>

using namespace Commands;

TestConnection::TestConnection(const int argc, const char* const argv[]) {
    if (argc != 0){
        this->err=ErrorCode::MISSING_PARAMS;
        printError(err);
        return;
    }

    const char* const cipher = mysql_get_ssl_cipher(Foundation::db::getInstance()->getMYSQLcon());

    std::cout << "Client Version: " << mysql_get_client_info() << std::endl;
    std::cout << "Host Version: " << mysql_get_server_info(Foundation::db::getInstance()->getMYSQLcon()) << std::endl;
    std::cout << "Host Info: " << mysql_get_host_info(Foundation::db::getInstance()->getMYSQLcon()) << std::endl;
    if(cipher) std::cout << "SSL cipher: " << cipher << std::endl;
}

TestConnection::~TestConnection() {

}