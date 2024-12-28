#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

ErrorCode Show::payments(const int argc, const char* const argv[]){

    char *sql = nullptr;

    if(argc == 0) {
        sql = (char*) malloc(strlen(this->showPaymentsSQL) * sizeof(char) + 1 + 1);
        sprintf(sql, this->showPaymentsSQL, "1");
        goto paymentsSQLExec;
    }

    // --unpaid
    if(!strcmp(argv[0], "--unpaid")){
        sql = (char*) malloc(strlen(paymentsUNPAID) * sizeof(char) + 1);
        strcpy(sql, paymentsUNPAID);
        goto paymentsSQLExec;
    }

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    //--byruid
    if((!strcmp(argv[0], "--byruid")) && argc == 2){
        char* where_part = "PAYMENT.ruid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showPaymentsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showPaymentsSQL, where);
        free(where);
        goto paymentsSQLExec;
    }

    //--bycuid
    if((!strcmp(argv[0], "--bycuid")) && argc == 2){
        char* where_part = "CUSTOMER.cuid = '%s'";
        char* where = (char*) malloc((strlen(where_part) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(where, where_part, argv[1]);
        sql = (char*) malloc((strlen(this->showPaymentsSQL) * sizeof(char)) + (strlen(where) * sizeof(char)) + 1);
        sprintf(sql, this->showPaymentsSQL, where);
        free(where);
        goto paymentsSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

paymentsSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    free(sql);
    
    return ErrorCode::SUCCESS;
}