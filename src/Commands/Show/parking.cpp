#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

#define showPARKING "SELECT * FROM PARKING_SPOT"

#define showAvailableParking "SELECT PARKING_SPOT.letter, PARKING_SPOT.number FROM PARKING_SPOT WHERE (PARKING_SPOT.letter, PARKING_SPOT.number) NOT IN (SELECT PARKING_SPOT.letter, PARKING_SPOT.number FROM PARKING_SPOT JOIN RESERVED_PARKING ON PARKING_SPOT.letter = RESERVED_PARKING.pletter AND PARKING_SPOT.number = RESERVED_PARKING.pnumber JOIN RESERVATION ON RESERVATION.ruid = RESERVED_PARKING.ruid WHERE (RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkout_date <= '%s') OR (RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s'));"

ErrorCode Show::parking(const int argc, const char* const argv[]){

    char *sql = nullptr;

    if(argc == 0) {
        sql = (char*) malloc(strlen(showPARKING) * sizeof(char) + 1);
        strcpy(sql, showPARKING);
        goto parkingSQLExec;
    }

    //--today
    if(!strcmp(argv[0], "--today")){
        sql = (char*) malloc((strlen(this->showParkingSQL) * sizeof(char)) + (strlen(parkingTODAY) * sizeof(char)) + 1);
        sprintf(sql, this->showParkingSQL, parkingTODAY);
        goto parkingSQLExec;
    }

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        char* where_part = "RESERVATION.ruid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showParkingSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showParkingSQL, where);
        free(where);
        goto parkingSQLExec;
    }

    if((!strcmp(argv[0], "--bycuid")) && argc == 2){
        char* where_part = "RESERVATION.main_cuid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showParkingSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showParkingSQL, where);
        free(where);
        goto parkingSQLExec;
    }

    //--date
    if((!strcmp(argv[0], "--date")) && argc == 2){
        char* where_part = "RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + 2*(strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1], argv[1]);
        sql = (char*) malloc((strlen(this->showParkingSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showParkingSQL, where);
        free(where);
        goto parkingSQLExec;
    }

    if(argc < 3) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--date")) && argc == 3){
        sql = (char*) malloc((strlen(showAvailableParking) * sizeof(char)) + 5*(strlen(argv[1]) * sizeof(char)) + 5*(strlen(argv[2]) * sizeof(char)) + 1);
        sprintf(sql, showAvailableParking, argv[1], argv[2], argv[1], argv[2], argv[1], argv[2], argv[1], argv[1], argv[2], argv[2]);
        goto parkingSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

parkingSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    free(sql);
    
    return ErrorCode::SUCCESS;

}