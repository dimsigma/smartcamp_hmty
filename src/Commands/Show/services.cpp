#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

#define showSERVICES "SELECT * FROM SERVICE"

ErrorCode Show::services(const int argc, const char* const argv[]){
    
    char *sql = nullptr;

    if(argc == 0) {
        sql = (char*) malloc(strlen(showSERVICES) * sizeof(char) + 1);
        strcpy(sql, showSERVICES);
        goto servicesSQLExec;
    }

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        char* where_part = "RESERVATION.ruid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showServicesSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showServicesSQL, where);
        free(where);
        goto servicesSQLExec;
    }

    if((!strcmp(argv[0], "--bycuid")) && argc == 2){
        char* where_part = "RESERVATION.main_cuid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showServicesSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showServicesSQL, where);
        free(where);
        goto servicesSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

servicesSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    free(sql);
    
    return ErrorCode::SUCCESS;
}