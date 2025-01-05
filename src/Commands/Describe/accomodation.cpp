#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Describe.hpp>

using namespace Commands;

ErrorCode Describe::accomodationGeneral(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->AccomodationGeneral) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->AccomodationGeneral, argv[1]);
        goto generalSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

generalSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--GENERAL INFORMATION--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Describe::accomodationReservation(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->AccomodationReservation) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->AccomodationReservation, argv[1]);
        goto reservationSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

reservationSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--RESERVATION LIST--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}