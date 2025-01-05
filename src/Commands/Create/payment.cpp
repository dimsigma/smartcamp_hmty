#include <cstdlib>
#include <iostream>
#include <sstream>

#include <errors.hpp>
#include <Commands/Create/reservation_customer.h>
#include <Commands/Create/reservation_accommodation.h>
#include <Commands/Create/reservation_parking.h>
#include <Commands/Create/reservation_creator.h>

#include <Foundation/db.hpp>

#include <Commands/Create.hpp>

using namespace Commands;

ErrorCode Create::payment(const int argc, const char* const argv[]){

    if(argc != 3) return ErrorCode::MISSING_PARAMS;

    int ruid = atoi(argv[0]);
    int amount = atoi(argv[2]);

    if(ruid == 0 && amount == 0) return ErrorCode::INVALID_PARAMS;

    std::ostringstream sql;
    sql << "INSERT INTO PAYMENT (method, amount, date, ruid) VALUES ('" << argv[1] << "', " << amount << ", NOW(), " << ruid << ");";

    Foundation::db *db = Foundation::db::getInstance();
    ErrorCode sqlerr = db->executeSQL(sql.str().c_str());
    if(sqlerr != ErrorCode::SUCCESS){
        return sqlerr;
    }
    return ErrorCode::SUCCESS;
}