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

    if((!strcmp(argv[0], "--add")) && (!strcmp(argv[2], "--ruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ReservationServices_add) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationServices_add, argv[1], argv[3]);
        goto resServicesSQLExec;
    }

    if((!strcmp(argv[0], "--remove")) && (!strcmp(argv[2], "--ruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ReservationServices_delete) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationServices_delete, argv[1], argv[3]);
        goto resServicesSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resServicesSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL_nores(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Update::reservationServicesShow(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if(((!strcmp(argv[0], "--add")) || (!strcmp(argv[0], "--remove"))) && (!strcmp(argv[2], "--ruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ShowReservationServicesInfo) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
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