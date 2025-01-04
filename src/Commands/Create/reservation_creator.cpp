#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Create/reservation_creator.h>

ErrorCode createReservationEntry(Commands::ReservationData *rd, int defaultCost, int *cuids, int *ruid){
    int defaultTotal = defaultCost * rd->spots;
    std::string input;
    int inputCost;
    std::cout   << "Default total cost is: " << defaultTotal << std::endl
                << "Press enter to accept, or enter a new value: ";
    //std::cin.clear(); std::cin.sync();
    std::getline(std::cin, input);
    try {inputCost = std::stoi(input); } catch (...) { inputCost = defaultTotal; }
    std::cout << inputCost << std::endl;

    std::ostringstream sql;
    sql << "INSERT INTO RESERVATION (total_cost, checkin_date, checkout_date, main_cuid) VALUES (" << inputCost << ", '" << rd->checkinData << "', '" << rd->checkoutData << "', " << cuids[0] << ");";
    
    Foundation::db *db = Foundation::db::getInstance();
    ErrorCode sqlerr = db->executeSQL(sql.str().c_str());
    if(sqlerr != ErrorCode::SUCCESS){
        return sqlerr;
    }


    MYSQL_RES *res;
    sqlerr = db->executeSQL(getLastIDQuery, &res);
    if(sqlerr != ErrorCode::SUCCESS){
        return sqlerr;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int id = atoi(row[0]);
    std::cout << id << std::endl;

    if(id == 0) {
        return ErrorCode::INSERT_FAILED;
    }

    db->freeResult(res);

    *ruid = id;
    return ErrorCode::SUCCESS;
}

ErrorCode createContainedCustomer(Commands::ReservationData *rd, int *cuids, int ruid){
    Foundation::db *db = Foundation::db::getInstance();
    for(int i = 1; i < rd->people; i++){
        std::ostringstream sql;
        sql << "INSERT INTO CONTAINED_CUSTOMER (cuid, ruid) VALUES (" << cuids[i] << ", " << ruid << ");";
        
        ErrorCode sqlerr = db->executeSQL(sql.str().c_str());
        if(sqlerr != ErrorCode::SUCCESS){
            return sqlerr;
        }
    }
    return ErrorCode::SUCCESS;
}

ErrorCode createReservedSpot(Commands::ReservationData *rd, int suid, int ruid){
    Foundation::db *db = Foundation::db::getInstance();
    for(int i = 0; i < rd->spots; i++){
        std::ostringstream sql;
        sql << "INSERT INTO RESERVED_SPOT (ruid, suid) VALUES (" << ruid << ", " << suid+i << ");";
        
        ErrorCode sqlerr = db->executeSQL(sql.str().c_str());
        if(sqlerr != ErrorCode::SUCCESS){
            return sqlerr;
        }
    }
    return ErrorCode::SUCCESS;
}

ErrorCode createReservedParking(int actualParkingSpots, Commands::PARKING_SPOT *spots, int ruid){
    Foundation::db *db = Foundation::db::getInstance();
    for(int i = 0; i < actualParkingSpots; i++){
        std::ostringstream sql;
        sql << "INSERT INTO RESERVED_PARKING (ruid, pletter, pnumber) VALUES (" << ruid << ", '" << spots[i].letters << "', " << spots[i].number << ");";
        
        ErrorCode sqlerr = db->executeSQL(sql.str().c_str());
        if(sqlerr != ErrorCode::SUCCESS){
            return sqlerr;
        }
    }
    return ErrorCode::SUCCESS;
}