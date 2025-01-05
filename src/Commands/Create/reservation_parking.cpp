#include <cstdlib>
#include <iostream>
#include <sstream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Create/reservation_parking.h>

ErrorCode getAvailParking(Commands::ReservationData *rd, Commands::PARKING_SPOT *spots, const char* const tmpl, int *actualParking){
    char *sql;
    sql = (char*) malloc((strlen(tmpl) + 5*strlen(rd->checkinData) + 5*strlen(rd->checkoutData) + strlen(std::to_string(rd->parking).c_str())) * sizeof(char));
    sprintf(sql, tmpl, rd->checkinData, rd->checkoutData, rd->checkinData, rd->checkoutData, rd->checkinData, rd->checkoutData, rd->checkinData, rd->checkinData, rd->checkoutData, rd->checkoutData, rd->parking);

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;
    std::cout << "Found Parking spots: " << std::endl;
    db->printResult(res);
    db->freeResult(res);

    sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    MYSQL_ROW row;
    int i = 0;
    while (row = mysql_fetch_row(res)) {
        spots[i].letters = (char*) malloc(strlen(row[0]) * sizeof(char));
        strcpy(spots[i].letters, row[0]);
        spots[i].number = atoi(row[1]);
#ifdef DEBUG
        std::cout << spots[i].letters << spots[i].number << std::endl;
#endif
        i++;
    }

    *actualParking = i;

    free(sql);
    std::cout << std::endl;
    return ErrorCode::SUCCESS;
}