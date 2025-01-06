#include <cstdlib>
#include <iostream>
#include <sstream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Create.hpp>

using namespace Commands;

ErrorCode Create::service(const int argc, const char* const argv[])
{
    char *sql = nullptr;

    if(argc < 4) return ErrorCode::MISSING_PARAMS;

    if((!strcmp(argv[0], "--name")) && (!strcmp(argv[2], "--cost")) && argc == 4){
        sql = (char *) malloc((strlen(this->serviceCreation) * sizeof(char)) + (strlen(argv[1]) * sizeof(char)) + (strlen(argv[3]) * sizeof(char)) + 1);
        sprintf(sql, this->serviceCreation, argv[1], argv[3]);
        goto serviceSQLExec;
    }

    return ErrorCode::INVALID_PARAMS;

serviceSQLExec:

    Foundation::db *db = Foundation::db::getInstance();

    ErrorCode sqlerr = db->executeSQL(sql);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    std::cout << "Service created!" << std::endl;

    free(sql);
    
    return ErrorCode::SUCCESS;
}