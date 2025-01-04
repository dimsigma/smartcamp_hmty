#include <cstdlib>
#include <iostream>
#include <iomanip>

#ifdef OS_WINDOWS
#include <mysql.h>
#elif OS_MACOS
#include <mysql/mysql.h>
#elif OS_LINUX
#include <mysql/mysql.h>
#endif

#include <Foundation/db.hpp>

#include <Foundation/Context.hpp>
#include <Foundation/Config.hpp>
#include <errors.hpp>

using namespace Foundation;

db::db(){
    Context *context = Context::getInstance();

    if(!(this->isValidConfig())){
        this->err = ErrorCode::INVALID_DB_CONFIG;
        printError(this->err);
        return;
    }

    if (mysql_library_init(0, NULL, NULL)) {
        this->err = ErrorCode::MYSQL_LIBRARY_INIT_ERROR;
        printError(this->err);
        return;
    }

    this->conn = mysql_init(NULL);
    if (conn == nullptr) {
        this->err = ErrorCode::MYSQL_INIT_ERROR;
        printError(this->err);
        return;
    }

    if(this->sslConfigExists()) {
        if (mysql_ssl_set(conn, context->config->sslKEY, context->config->sslCRT, context->config->sslCA, nullptr, nullptr)) {
            mysql_close(conn);
            this->err = ErrorCode::MYSQL_SSL_SET_ERROR;
            printError(this->err);
            return;
        }
    }

    if (!mysql_real_connect(this->conn, context->config->ip, context->config->username, (context->config->hasPassword)?(context->config->passwd):(nullptr), DB_NAME, context->config->port, nullptr, (this->sslConfigExists())?(CLIENT_SSL):(NULL))) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        this->err = ErrorCode::MYSQL_REAL_CONNECTION_ERROR;
        printError(this->err);
        return;
    }
}

db::~db(){
    mysql_close(this->conn);
    mysql_library_end();
}

bool db::isValidConfig(void) const {
    Context *context = Context::getInstance();
    return (
        strlen(context->config->ip) > 0 &&
        context->config->port > 0 &&
        strlen(context->config->username) > 0 &&
        (context->config->hasPassword)?(strlen(context->config->passwd) > 0):(1)
    );
}

bool db::sslConfigExists(void) const {
    Context *context = Context::getInstance();
    return (
        strlen(context->config->sslCA) > 0 &&
        strlen(context->config->sslCRT) > 0 &&
        strlen(context->config->sslKEY) > 0
    );
}

ErrorCode db::executeSQL(const char* const query, MYSQL_RES** result) const {
    
#ifdef DEBUG
    std::cout << query << std::endl;
#endif

    if (mysql_query(this->conn, query)) {
        std::cerr << "Query failed: " << mysql_error(this->conn) << std::endl;
        return ErrorCode::MYSQL_QUERY_ERROR;
    }
    
    MYSQL_RES *r = mysql_store_result(this->conn);
    
    if (r == nullptr) {
        std::cerr << "Failed to retrieve result set: " << mysql_error(this->conn) << std::endl;
        return ErrorCode::MYSQL_STORE_RESULT_ERROR;
    }
    
    *result = r;
    
    return ErrorCode::SUCCESS;
}

ErrorCode db::executeSQL(const char* const query) const {
    
#ifdef DEBUG
    std::cout << query << std::endl;
#endif

    if (mysql_query(this->conn, query)) {
        std::cerr << "Query failed: " << mysql_error(this->conn) << std::endl;
        return ErrorCode::MYSQL_QUERY_ERROR;
    }
    
    return ErrorCode::SUCCESS;
}

void db::freeResult(MYSQL_RES* result) const {
    mysql_free_result(result);
}

void db::printResult(MYSQL_RES* res) const {
    std::cout << "Query Results:" << std::endl;
    MYSQL_FIELD *fields = mysql_fetch_fields(res);
    for (unsigned int i = 0; i < mysql_num_fields(res); ++i) {
        std::cout << std::setw(20) << fields[i].name;
    }
    std::cout << std::endl;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        for (unsigned int i = 0; i < mysql_num_fields(res); ++i) {
            if (row[i]) {
                std::cout << std::setw(20) << row[i];
            } else {
                std::cout << std::setw(20) << "NULL"; 
            }
        }
        std::cout << std::endl;
    }
}