#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Update.hpp>

using namespace Commands;

ErrorCode Update::reservationCost(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 3) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[1], "--ruid")) && argc == 3){
        sql = (char *) malloc((strlen(this->ReservationCost) * sizeof(char)) + (strlen(argv[0]) * sizeof(char)) + (strlen(argv[2]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationCost, argv[0], argv[2]);
        goto resCostSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resCostSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL_nores(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Update::reservationCostShow(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 3) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[1], "--ruid")) && argc == 3){
        sql = (char *) malloc((strlen(this->ShowReservationCostInfo) * sizeof(char)) + (strlen(argv[2]) * sizeof(char)) + 1);
        sprintf(sql, this->ShowReservationCostInfo, argv[2]);
        goto resCostShowSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resCostShowSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--UPDATED RESERVATION INFORMATION--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}