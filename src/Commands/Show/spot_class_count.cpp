#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

#define WTENT "SPOT_CLASS.class_type = 'TENT'"
#define WBUNGALOW "SPOT_CLASS.class_type = 'BUNGALOW'"
#define WRV "SPOT_CLASS.class_type = 'RV'"


ErrorCode Show::spot_class_count(const int argc, const char* const argv[]){

    if(argc != 1) return ErrorCode::MISSING_PARAMS;

    char* where_statement_part;

    //Handle [any | tent | bungalow | rv]
    if(!strcmp(argv[0], "any")){
        where_statement_part = (char*) malloc(sizeof(char) + 1);
        strcpy(where_statement_part, "1");
        goto spotclasscountSQLExec;
    }

    if(!strcmp(argv[0], "tent")){
        where_statement_part = (char*) malloc((strlen(WTENT) * sizeof(char)) + 1);
        strcpy(where_statement_part, WTENT);
        goto spotclasscountSQLExec;
    }

    if(!strcmp(argv[0], "bungalow")){
        where_statement_part = (char*) malloc((strlen(WBUNGALOW) * sizeof(char)) + 1);
        strcpy(where_statement_part, WBUNGALOW);
        goto spotclasscountSQLExec;
    }

    if(!strcmp(argv[0], "rv")){
        where_statement_part = (char*) malloc((strlen(WRV) * sizeof(char)) + 1);
        strcpy(where_statement_part, WRV);
        goto spotclasscountSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

spotclasscountSQLExec:

    char *sql = nullptr;

    sql = (char*) malloc((strlen(this->showSpotClassCountSQL) * sizeof(char)) + (strlen(where_statement_part) * sizeof(char)) + 1);
    sprintf(sql, this->showSpotClassCountSQL, where_statement_part);
    
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