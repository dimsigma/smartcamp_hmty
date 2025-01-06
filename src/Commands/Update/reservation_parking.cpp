#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Update.hpp>

using namespace Commands;

ErrorCode Update::reservationParking(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 5) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--add")) && (!strcmp(argv[3], "--byruid")) && argc == 5){
        sql = (char *) malloc((strlen(this->ReservationParking_add) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[2]) * sizeof(char)) + (strlen(argv[4]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationParking_add, argv[4], argv[1], argv[2]);
        goto resParkingSQLExec;
    }

    if((!strcmp(argv[0], "--remove")) && (!strcmp(argv[3], "--byruid")) && argc == 5){
        sql = (char *) malloc((strlen(this->ReservationParking_delete) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[2]) * sizeof(char)) + (strlen(argv[4]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationParking_delete, argv[4], argv[1], argv[2]);
        goto resParkingSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resParkingSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Update::reservationParkingShow(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 5) return ErrorCode::MISSING_PARAMS;

    if(((!strcmp(argv[0], "--add")) || (!strcmp(argv[0], "--remove"))) && (!strcmp(argv[3], "--byruid")) && argc == 5){
        sql = (char *) malloc((strlen(this->ShowReservationParkingInfo) * sizeof(char)) + (strlen(argv[4]) * sizeof(char)) + 1);
        sprintf(sql, this->ShowReservationParkingInfo, argv[4]);
        goto resParkingShowSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resParkingShowSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--UPDATED RESERVATION PARKING LIST--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}