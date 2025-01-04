#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Update.hpp>

using namespace Commands;

ErrorCode Update::reservationAccomodation(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--add")) && (!strcmp(argv[2], "--ruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ReservationAccomodation_add) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationAccomodation_add, argv[3], argv[1]);
        goto resAccomodationSQLExec;
    }

    if((!strcmp(argv[0], "--remove")) && (!strcmp(argv[2], "--ruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ReservationAccomodation_delete) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationAccomodation_delete, argv[3], argv[1]);
        goto resAccomodationSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resAccomodationSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL_nores(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Update::reservationAccomodationShow(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    const char* const l1 = "6";
    const char* const l2 = "8";
    const char* const s1 = "WINTER";
    const char* const s2 = "SUMMER";

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if(((!strcmp(argv[0], "--add")) || (!strcmp(argv[0], "--remove"))) && (!strcmp(argv[2], "--ruid")) && argc == 4){
        sql = (char *) malloc((strlen(this->ShowReservationAccomodationInfo) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(l1) * sizeof(char)) + (strlen(l2) * sizeof(char)) + (strlen(s1) * sizeof(char)) + (strlen(s2) * sizeof(char)) + 1);
        sprintf(sql, this->ShowReservationAccomodationInfo, argv[3], l1, l2, s1, s2);
        goto resAccomodationShowSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

resAccomodationShowSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--UPDATED RESERVATION ACCOMODATION SPOT LIST--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}