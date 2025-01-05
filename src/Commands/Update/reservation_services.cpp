#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Update.hpp>

using namespace Commands;

ErrorCode Update::reservationServices(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--add")) && (!strcmp(argv[2], "--byruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ReservationServices_add) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationServices_add, argv[1], argv[3]);
        goto resServicesSQLExec;
    }

    if((!strcmp(argv[0], "--remove")) && (!strcmp(argv[2], "--byruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ReservationServices_delete) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationServices_delete, argv[1], argv[3]);
        goto resServicesSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resServicesSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Update::reservationServicesShow(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if(((!strcmp(argv[0], "--add")) || (!strcmp(argv[0], "--remove"))) && (!strcmp(argv[2], "--byruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ShowReservationServicesInfo) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->ShowReservationServicesInfo, argv[3]);
        goto resServicesShowSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resServicesShowSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--UPDATED RESERVATION SERVICES LIST--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Update::editCost(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--add")) && (!strcmp(argv[2], "--byruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->EditCost_add) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->EditCost_add, argv[1], argv[3]);
        goto editCostSQLExec;
    }

    if((!strcmp(argv[0], "--remove")) && (!strcmp(argv[2], "--byruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->EditCost_sub) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->EditCost_sub, argv[1], argv[3]);
        goto editCostSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

editCostSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}