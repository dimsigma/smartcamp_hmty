#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

ErrorCode Show::customers(const int argc, const char* const argv[]){

    char *sql = nullptr;

    if(argc == 0) {
        sql = (char*) malloc(strlen(this->showCustomersSQL) * sizeof(char) + 1 + 1);
        sprintf(sql, this->showCustomersSQL, "1");
        goto customersSQLExec;
    }

    // --returning
    if(!strcmp(argv[0], "--returning")){
        sql = (char*) malloc((strlen(this->showCustomersSQL) * sizeof(char)) + (strlen(customersRETURNING) * sizeof(char)) + 1);
        sprintf(sql, this->showCustomersSQL, customersRETURNING);
        goto customersSQLExec;
    }

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    //--byname
    if((!strcmp(argv[0], "--byname")) && argc == 2){
        char* where_part = "CUSTOMER.first_name REGEXP '%s' OR CUSTOMER.middle_name REGEXP '%s' OR CUSTOMER.last_name REGEXP '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + 3*(strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1], argv[1], argv[1]);
        sql = (char*) malloc((strlen(this->showCustomersSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showCustomersSQL, where);
        free(where);
        goto customersSQLExec;
    }

    //--bycuid
    if((!strcmp(argv[0], "--bycuid")) && argc == 2){
        char* where_part = "CUSTOMER.cuid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showCustomersSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showCustomersSQL, where);
        free(where);
        goto customersSQLExec;
    }

    //--byruid
    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        char* where_part = "RESERVATION.ruid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showCustomersWithoutTotalReservationsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showCustomersWithoutTotalReservationsSQL, where);
        free(where);
        goto customersSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

customersSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    free(sql);
    
    return ErrorCode::SUCCESS;
}