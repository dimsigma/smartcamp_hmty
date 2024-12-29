#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

ErrorCode Show::reservations(const int argc, const char* const argv[]){

    char *sql = nullptr;

    //no args
    if(argc == 0) {
        sql = (char*) malloc(strlen(this->showReservationsSQL) * sizeof(char) + 1 + 1);
        sprintf(sql, this->showReservationsSQL, "1");
        goto reservationsSQLExec;
    }

    // --all
    if(!strcmp(argv[0], "--all")){
        sql = (char*) malloc(strlen(this->showReservationsSQL) * sizeof(char) + 1 + 1);
        sprintf(sql, this->showReservationsSQL, "1");
        goto reservationsSQLExec;
    }

    //--today
    if(!strcmp(argv[0], "--today")){
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(reservationsTODAY) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, reservationsTODAY);
        goto reservationsSQLExec;
    }

    //--next30d
    if(!strcmp(argv[0], "--next30d")){
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(reservationsNEXT30D) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, reservationsNEXT30D);
        goto reservationsSQLExec;
    }

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    //--bycuid
    if((!strcmp(argv[0], "--bycuid")) && argc == 2){
        char* where_part = "RESERVATION.main_cuid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, where);
        free(where);
        goto reservationsSQLExec;
    }

    //--byruid
    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        char* where_part = "RESERVATION.ruid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, where);
        free(where);
        goto reservationsSQLExec;
    }

    //--byname
    if((!strcmp(argv[0], "--byname")) && argc == 2){
        char* where_part = "CUSTOMER.first_name REGEXP '%s' OR CUSTOMER.middle_name REGEXP '%s' OR CUSTOMER.last_name REGEXP '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + 3*(strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1], argv[1], argv[1]);
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, where);
        free(where);
        goto reservationsSQLExec;
    }

    //--date
    if((!strcmp(argv[0], "--date")) && argc == 2){
        char* where_part = "RESERVATION.checkin_date = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, where);
        free(where);
        goto reservationsSQLExec;
    }

    //--past
    //30d
    if((!strcmp(argv[0], "--past")) && (!strcmp(argv[1], "30d"))){
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(reservationsPAST30d) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, reservationsPAST30d);
        goto reservationsSQLExec;
    }

    //6m
    if((!strcmp(argv[0], "--past")) && (!strcmp(argv[1], "6m"))){
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(reservationsPAST6m) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, reservationsPAST6m);
        goto reservationsSQLExec;
    }

    //1y
    if((!strcmp(argv[0], "--past")) && (!strcmp(argv[1], "1y"))){
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(reservationsPAST1y) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, reservationsPAST1y);
        goto reservationsSQLExec;
    }

    if(argc < 3) return ErrorCode::MISSING_PARAMS;

    //--date
    if((!strcmp(argv[0], "--date")) && argc == 3){
        char* where_part = "(RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkout_date <= '%s') OR (RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s')";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + 5*(strlen(argv[1]) * sizeof(char)) + 5*(strlen(argv[2]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1], argv[2], argv[1], argv[2], argv[1], argv[2], argv[1], argv[1], argv[2], argv[2]);
        sql = (char*) malloc((strlen(this->showReservationsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showReservationsSQL, where);
        free(where);
        goto reservationsSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

reservationsSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    free(sql);
    
    return ErrorCode::SUCCESS;
}