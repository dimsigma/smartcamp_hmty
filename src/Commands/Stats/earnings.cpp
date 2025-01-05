#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Stats.hpp>

using namespace Commands;

ErrorCode Stats::earnings(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--permonth")) && argc == 2){
        sql = (char *) malloc((strlen(this->EarningsMonth) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->EarningsMonth, argv[1]);
        goto earningsMonthSQLExec;
    }

    if(argc == 2){
        sql = (char *) malloc((strlen(this->Earnings) * sizeof(char)) + (strlen(argv[0]) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->Earnings, argv[0], argv[1]);
        goto earningsMonthSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

earningsMonthSQLExec:

    Foundation::db *db1 = Foundation::db::getInstance();
    MYSQL_RES *res1;

    std::cout << std::endl << "--EARNINGS PER MONTH--" << std::endl;

    ErrorCode sqlerr1 = db1->executeSQL(sql, &res1);
    if(sqlerr1 != ErrorCode::SUCCESS) return sqlerr1;

    db1->printResult(res1);
    db1->freeResult(res1);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;

earningsSQLExec:

    Foundation::db *db2 = Foundation::db::getInstance();
    MYSQL_RES *res2;

    std::cout << std::endl << "--EARNINGS--" << std::endl;

    ErrorCode sqlerr2 = db2->executeSQL(sql, &res2);
    if(sqlerr2 != ErrorCode::SUCCESS) return sqlerr2;

    db2->printResult(res2);
    db2->freeResult(res2);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}