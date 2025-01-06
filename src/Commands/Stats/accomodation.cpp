#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Stats.hpp>

using namespace Commands;

ErrorCode Stats::accomodation(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 2) return ErrorCode::MISSING_PARAMS;

    if(argc == 2){
        sql = (char *) malloc((strlen(this->Accomodation) * sizeof(char)) + 3*(strlen(argv[0]) * sizeof(char)) + 3*(strlen(argv[1]) * sizeof(char)) + 1);
        sprintf(sql, this->Accomodation, argv[1], argv[1], argv[0], argv[0], argv[1], argv[0]);
        goto accomodationSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

accomodationSQLExec:

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    std::cout << std::endl << "--ACCOMODATION SPOT POPULARITY--" << std::endl;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);
    std::cout << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}