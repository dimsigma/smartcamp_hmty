#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

#define WTENT "SPOT_CLASS.class_type = 'ΤΕΝΤ'"
#define WBUNGALOW "SPOT_CLASS.class_type = 'BUNGALOW'"
#define WRV "SPOT_CLASS.class_type = 'RV'"

#define activeSpotClass " AND ((SPOT_CLASS.start_date <= CURDATE() AND SPOT_CLASS.end_date >= CURDATE()) OR (SPOT_CLASS.start_date > SPOT_CLASS.end_date AND (CURDATE() >= SPOT_CLASS.start_date OR CURDATE() <= SPOT_CLASS.end_date)))"
#define dateSpotClass " AND ((SPOT_CLASS.start_date <= '%s' AND SPOT_CLASS.end_date >= '%s') OR (SPOT_CLASS.start_date > SPOT_CLASS.end_date AND ('%s' >= SPOT_CLASS.start_date OR '%s' <= SPOT_CLASS.end_date)))"

ErrorCode Show::spot_class(const int argc, const char* const argv[]){

    if(argc < 1) return ErrorCode::MISSING_PARAMS;

    char* where_statement_part;

    //Handle [any | tent | bungalow | rv]
    if(!strcmp(argv[0], "any")){
        where_statement_part = (char*) malloc(sizeof(char) + 1);
        strcpy(where_statement_part, "1");
        goto spotclassArg1;
    }

    if(!strcmp(argv[0], "tent")){
        where_statement_part = (char*) malloc((strlen(WTENT) * sizeof(char)) + 1);
        strcpy(where_statement_part, WTENT);
        goto spotclassArg1;
    }

    if(!strcmp(argv[0], "bungalow")){
        where_statement_part = (char*) malloc((strlen(WBUNGALOW) * sizeof(char)) + 1);
        strcpy(where_statement_part, WBUNGALOW);
        goto spotclassArg1;
    }

    if(!strcmp(argv[0], "rv")){
        where_statement_part = (char*) malloc((strlen(WRV) * sizeof(char)) + 1);
        strcpy(where_statement_part, WRV);
        goto spotclassArg1;
    }

    return ErrorCode::INVALID_PARAMS;

spotclassArg1:

    char *sql = nullptr;

    //Handle flags
    if(argc == 1){
        sql = (char*) malloc((strlen(this->showSpotClassSQL) * sizeof(char)) + (strlen(where_statement_part) * sizeof(char)) + 1);
        sprintf(sql, this->showSpotClassSQL, where_statement_part);
        goto spotclassSQLExec;
    }

    // --all
    if(!strcmp(argv[1], "--all")){ //Remember that argv[0] is [any | tent | bungalow | rv]
        sql = (char*) malloc((strlen(this->showSpotClassSQL) * sizeof(char)) + (strlen(where_statement_part) * sizeof(char)) + 1);
        sprintf(sql, this->showSpotClassSQL, where_statement_part);
        goto spotclassSQLExec;
    }

    //--active
    if(!strcmp(argv[1], "--active")){ //Remember that argv[0] is [any | tent | bungalow | rv]
        where_statement_part = (char*) realloc(where_statement_part, (strlen(where_statement_part) * sizeof(char)) + (strlen(activeSpotClass) * sizeof(char)) + 1);
        strcat(where_statement_part, activeSpotClass);
        sql = (char*) malloc((strlen(this->showSpotClassSQL) * sizeof(char)) + (strlen(where_statement_part) * sizeof(char)) + 1);
        sprintf(sql, this->showSpotClassSQL, where_statement_part);
        goto spotclassSQLExec;
    }

    if(argc < 3) return ErrorCode::MISSING_PARAMS;

    //--date
    if(!strcmp(argv[1], "--date")){ //Remember that argv[0] is [any | tent | bungalow | rv]
        char* datestr = (char*) malloc((5 + strlen(argv[2])) * sizeof(char) + 1);
        strcpy(datestr, "1970-");
        strcat(datestr, argv[2]);
        where_statement_part = (char*) realloc(where_statement_part, (strlen(where_statement_part) * sizeof(char)) + (strlen(dateSpotClass) * sizeof(char)) + 4 * (strlen(datestr) * sizeof(char)) + 1);
        strcat(where_statement_part, dateSpotClass);
        char* where_statement;
        sprintf(where_statement, where_statement_part, datestr, datestr, datestr, datestr);
        sql = (char*) malloc((strlen(this->showSpotClassSQL) * sizeof(char)) + (strlen(where_statement) * sizeof(char)) + 1);
        sprintf(sql, this->showSpotClassSQL, where_statement);
        free(datestr);
        goto spotclassSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

spotclassSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    free(where_statement_part); //Important
    free(sql);
    
    return ErrorCode::SUCCESS;
}