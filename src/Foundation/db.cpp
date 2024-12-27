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

    if (!mysql_real_connect(this->conn, context->config->ip, context->config->username, (context->config->hasPassword)?(context->config->passwd):(nullptr), "smarty", context->config->port, nullptr, (this->sslConfigExists())?(CLIENT_SSL):(NULL))) {
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