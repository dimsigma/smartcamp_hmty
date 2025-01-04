#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Update.hpp>

using namespace Commands;

ErrorCode Update::customer(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--firstname")) && (!strcmp(argv[2], "--cuid")) && argc == 4){
        sql = (char *) malloc((strlen(this->CustomerFirstName) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerFirstName, argv[1], argv[3]);
        goto customerSQLExec;
    }

    if((!strcmp(argv[0], "--lastname")) && (!strcmp(argv[2], "--cuid")) && argc == 4){
        sql = (char *) malloc((strlen(this->CustomerLastName) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerLastName, argv[1], argv[3]);
        goto customerSQLExec;
    }

    if((!strcmp(argv[0], "--telcountry")) && (!strcmp(argv[2], "--cuid")) && argc == 4){
        sql = (char *) malloc((strlen(this->CustomerTelcountry) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerTelcountry, argv[1], argv[3]);
        goto customerSQLExec;
    }

    if((!strcmp(argv[0], "--telnumber")) && (!strcmp(argv[2], "--cuid"))  && argc == 4){
        sql = (char *) malloc((strlen(this->CustomerTelnumber) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerTelnumber, argv[1], argv[3]);
        goto customerSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

customerSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL_nores(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Update::customerShow(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if(((!strcmp(argv[0], "--firstname")) || (!strcmp(argv[0], "--lastname")) || (!strcmp(argv[0], "--telcountry")) || (!strcmp(argv[0], "--telnumber"))) && (!strcmp(argv[2], "--cuid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ShowCustomerInfo) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ShowCustomerInfo, argv[3]);
        goto customerShowSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

customerShowSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--UPDATED CUSTOMER INFORMATION--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}