#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Describe.hpp>

using namespace Commands;

ErrorCode Describe::customerGeneral(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--bycuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->CustomerGeneral_bycuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerGeneral_bycuid, argv[1]);
        goto generalSQLExec;
    }

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->CustomerGeneral_byruid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerGeneral_byruid, argv[1]);
        goto generalSQLExec;
    }

    if((!strcmp(argv[0], "--bysuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->CustomerGeneral_bysuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerGeneral_bysuid, argv[1]);
        goto generalSQLExec;
    }

    if((!strcmp(argv[0], "--byname")) && argc == 3){
        sql = (char *) malloc((strlen(this->CustomerGeneral_byname) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[2]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerGeneral_byname, argv[1], argv[2]);
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

ErrorCode Describe::customerReservation(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--bycuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->CustomerReservation_bycuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerReservation_bycuid, argv[1]);
        goto reservationSQLExec;
    }

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->CustomerReservation_byruid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerReservation_byruid, argv[1]);
        goto reservationSQLExec;
    }

    if((!strcmp(argv[0], "--bysuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->CustomerReservation_bysuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerReservation_bysuid, argv[1]);
        goto reservationSQLExec;
    }

    if((!strcmp(argv[0], "--byname")) && argc == 3){
        sql = (char *) malloc((strlen(this->CustomerReservation_byname) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[2]) * sizeof(char)) + 1);
        sprintf(sql, this->CustomerReservation_byname, argv[1], argv[2]);
        goto reservationSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

reservationSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--RESERVATION HISTORY--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}