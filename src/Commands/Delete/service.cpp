#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Delete.hpp>

using namespace Commands;

ErrorCode Delete::delService(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 1) return ErrorCode::MISSING_PARAMS;

    if(argc == 1){
        sql = (char *) malloc((strlen(this->service) * sizeof(char)) + (strlen(argv[0]) * sizeof(char)) + 1);
        sprintf(sql, this->service, argv[0]);
        goto serviceSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

serviceSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL_nores(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    free(sql);
    
    return ErrorCode::SUCCESS;
}