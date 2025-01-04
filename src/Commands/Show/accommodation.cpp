#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

#define JTENT "NATURAL JOIN TENT_SPACE"
#define JRV "NATURAL JOIN RV_SPOT"
#define JBUNGALOW "NATURAL JOIN BUNGALOW"

#define accommodationRVselect "RV_SPOT.size,"
#define accommodationTENTselect "TENT_SPACE.size, TENT_SPACE.terrain_type,"
#define accommodationBUNGALOWselect "BUNGALOW.max_persons,"

#define accommodationAvailBetweenDates "SELECT ACCOMODATION_SPOT.*, %s SPOT_CLASS.cost, DATEDIFF('%s', '%s')*SPOT_CLASS.cost AS total_cost FROM ACCOMODATION_SPOT %s JOIN SPOT_CLASS ON ACCOMODATION_SPOT.class_name = SPOT_CLASS.class_name AND ACCOMODATION_SPOT.class_type = SPOT_CLASS.class_type AND ((SPOT_CLASS.start_date <= CONCAT('1970-', DATE_FORMAT('%s', '%%m-%%d')) AND SPOT_CLASS.end_date >= CONCAT('1970-', DATE_FORMAT('%s', '%%m-%%d'))) OR (SPOT_CLASS.start_date > SPOT_CLASS.end_date AND (CONCAT('1970-', DATE_FORMAT('%s', '%%m-%%d')) >= SPOT_CLASS.start_date OR CONCAT('1970-', DATE_FORMAT('%s', '%%m-%%d')) <= SPOT_CLASS.end_date))) WHERE NOT EXISTS ( SELECT * FROM RESERVED_SPOT NATURAL JOIN RESERVATION WHERE ((RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkout_date <= '%s') OR (RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s')) AND RESERVED_SPOT.suid = ACCOMODATION_SPOT.suid) ORDER BY  ACCOMODATION_SPOT.suid ASC;"

ErrorCode Show::accommodation(const int argc, const char* const argv[]){

    if(argc < 1) return ErrorCode::MISSING_PARAMS;

    char* select_statement;
    char* join_statement;


    //Handle [any | tent | bungalow | rv]
    if(!strcmp(argv[0], "any")){
        join_statement = (char*) malloc(sizeof(char) + 1);
        strcpy(join_statement, " ");
        select_statement = (char*) malloc(sizeof(char) + 1);
        strcpy(select_statement, " ");
    }

    if(!strcmp(argv[0], "tent")){
        join_statement = (char*) malloc((strlen(JTENT) * sizeof(char)) + 1);
        strcpy(join_statement, JTENT);
        select_statement = (char*) malloc((strlen(accommodationTENTselect) * sizeof(char)) + 1);
        strcpy(select_statement, accommodationTENTselect);
    }

    if(!strcmp(argv[0], "bungalow")){
        join_statement = (char*) malloc((strlen(JBUNGALOW) * sizeof(char)) + 1);
        strcpy(join_statement, JBUNGALOW);
        select_statement = (char*) malloc((strlen(accommodationBUNGALOWselect) * sizeof(char)) + 1);
        strcpy(select_statement, accommodationBUNGALOWselect);
    }

    if(!strcmp(argv[0], "rv")){
        join_statement = (char*) malloc((strlen(JRV) * sizeof(char)) + 1);
        strcpy(join_statement, JRV);
        select_statement = (char*) malloc((strlen(accommodationRVselect) * sizeof(char)) + 1);
        strcpy(select_statement, accommodationRVselect);
    }

    char *sql = nullptr;

    //Handle flags
    if(argc == 1){
        sql = (char*) malloc((strlen(this->showAllAccommodationSQL) * sizeof(char)) + (strlen(join_statement) * sizeof(char)) + 1 + 1);
        sprintf(sql, this->showAllAccommodationSQL, join_statement, "1");
        goto accSQLExec;
    }

    // --all
    if(!strcmp(argv[1], "--all")){ //Remember that argv[0] is [any | tent | bungalow | rv]
        sql = (char*) malloc((strlen(this->showAllAccommodationSQL) * sizeof(char)) + (strlen(join_statement) * sizeof(char)) + 1 + 1);
        sprintf(sql, this->showAllAccommodationSQL, join_statement, "1");
        goto accSQLExec;
    }

    // --today
    if(!strcmp(argv[1], "--today")){ //Remember that argv[0] is [any | tent | bungalow | rv]
        sql = (char*) malloc((strlen(this->showAccommodationSQL) * sizeof(char)) + (strlen(select_statement) * sizeof(char)) + (strlen(join_statement) * sizeof(char)) + (strlen(parkingTODAY) * sizeof(char)) + 1);
        sprintf(sql, this->showAccommodationSQL, select_statement, join_statement, parkingTODAY); //It is the same where clause. Ignore the parking in the name.
        goto accSQLExec;
    }

    if(argc < 3) return ErrorCode::MISSING_PARAMS;

    //--date
    if((!strcmp(argv[1], "--date")) && argc == 3){
        char* where_part = "RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + 2*(strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[2], argv[2]);
        sql = (char*) malloc((strlen(this->showAccommodationSQL) * sizeof(char)) + (strlen(select_statement) * sizeof(char)) + (strlen(join_statement) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showAccommodationSQL, select_statement, join_statement, where);
        free(where);
        goto accSQLExec;
    }

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[1], "--date")) && argc == 4){
        sql = (char*) malloc((strlen(accommodationAvailBetweenDates) * sizeof(char)) + (strlen(select_statement) * sizeof(char)) + (strlen(join_statement) * sizeof(char)) + (6+4)*(strlen(argv[2]) * sizeof(char)) + 6*(strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, accommodationAvailBetweenDates, select_statement, argv[3], argv[2], join_statement, argv[2], argv[2], argv[2], argv[2], argv[2], argv[3], argv[2], argv[3], argv[2], argv[3], argv[2], argv[2], argv[3], argv[3]);
        goto accSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

accSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    free(join_statement); //Important
    free(select_statement); //Important
    free(sql);
    
    return ErrorCode::SUCCESS;

}