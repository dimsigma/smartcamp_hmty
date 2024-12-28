#pragma once

#ifdef OS_WINDOWS
#include <mysql.h>
#elif OS_MACOS
#include <mysql/mysql.h>
#elif OS_LINUX
#include <mysql/mysql.h>
#endif

#include <errors.hpp>

#define DB_NAME "smartcamp"

namespace Foundation {
    class db
    {
    private:
        inline static db* instance = nullptr;
        ErrorCode err;
        MYSQL *conn;

        db(/* args */);

        bool isValidConfig(void) const;
        bool sslConfigExists(void) const;
    public:
        db(const db& obj) = delete;

        inline static db* getInstance(){
            if(instance == nullptr) instance = new db();
            return instance;
        }

        ErrorCode executeSQL(const char* const query, MYSQL_RES** result) const;
        void freeResult(MYSQL_RES* result) const;

        inline MYSQL* const getMYSQLcon(void) const {
            return this->conn;
        };

        ~db();
    };

}