#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Describe.hpp>

using namespace Commands;

ErrorCode Describe::reservationGeneral(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationGeneral_byruid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationGeneral_byruid, argv[1]);
        goto generalSQLExec;
    }

    if((!strcmp(argv[0], "--bysuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationGeneral_bysuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationGeneral_bysuid, argv[1]);
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

ErrorCode Describe::reservationAccomodation(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    const char* const l1 = "6";
    const char* const l2 = "8";
    const char* const s1 = "LOW";
    const char* const s2 = "HIGH";

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationAccomodation_byruid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(l1) * sizeof(char)) + (strlen(l2) * sizeof(char)) + (strlen(s1) * sizeof(char)) + (strlen(s2) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationAccomodation_byruid, argv[1], l1, l2, s1, s2);
        goto accomodationSQLExec;
    }

    if((!strcmp(argv[0], "--bysuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationAccomodation_bysuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(l1) * sizeof(char)) + (strlen(l2) * sizeof(char)) + (strlen(s1) * sizeof(char)) + (strlen(s2) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationAccomodation_bysuid, argv[1], l1, l2, s1, s2);
        goto accomodationSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

accomodationSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--RESERVED ACCOMODATION SPOTS--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Describe::reservationServices(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationServices_byruid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationServices_byruid, argv[1]);
        goto servicesSQLExec;
    }

    if((!strcmp(argv[0], "--bysuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationServices_bysuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationServices_bysuid, argv[1]);
        goto servicesSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

servicesSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--PROVIDED SERVICES--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Describe::reservationParking(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationParking_byruid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationParking_byruid, argv[1]);
        goto parkingSQLExec;
    }

    if((!strcmp(argv[0], "--bysuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationParking_bysuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationParking_bysuid, argv[1]);
        goto parkingSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

parkingSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--RESERVED PARKING SPOTS--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}

ErrorCode Describe::reservationPayment(const int argc, const char* const argv[])
{

    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationPayment_byruid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationPayment_byruid, argv[1]);
        goto paymentSQLExec;
    }

    if((!strcmp(argv[0], "--bysuid")) && argc == 2){
        sql = (char *) malloc((strlen(this->ReservationPayment_bysuid) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->ReservationPayment_bysuid, argv[1]);
        goto paymentSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

paymentSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--PAYMENT INFORMATION--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}