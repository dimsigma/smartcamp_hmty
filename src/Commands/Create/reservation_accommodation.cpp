#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Create/reservation_accommodation.h>

ErrorCode getAccommodationGroupId(Commands::ReservationData *rd, const char* const tmpl, int *suid, int *defaultCost){
    char *sql;
    sql = (char*) malloc((strlen(tmpl) + 6*strlen(rd->checkinData) + 6*strlen(rd->checkinData) + 2*(strlen(std::to_string(rd->spots).c_str()))) * sizeof(char));

    sprintf(sql, tmpl,
                rd->checkoutData,
                rd->checkinData,
                rd->checkinData,
                rd->checkoutData,
                rd->checkinData,
                rd->checkoutData,
                rd->checkinData,
                rd->checkoutData,
                rd->checkinData,
                rd->checkinData,
                rd->checkoutData,
                rd->checkoutData,
                rd->spots,
                rd->spots);

    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    ErrorCode sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    db->printResult(res);
    db->freeResult(res);

    sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS) return sqlerr;

    int groupid;
    std::string inputGroupId;
    std::cout << "Please enter the desired group_id: ";
    std::getline(std::cin, inputGroupId);
    try {groupid = std::stoi(inputGroupId); } catch (...) {
        return ErrorCode::UNKNOWN_ERROR;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
#ifdef DEBUG
        std::cout << groupid << "\t" << atoi(row[0]) << "\t" << (groupid == atoi(row[0])) << std::endl;
#endif
        if(groupid == atoi(row[0])) {
            *suid = atoi(row[6]);
            *defaultCost = atoi(row[4]);
            db->freeResult(res);
            free(sql);
            return ErrorCode::SUCCESS;
        }
    }

    db->freeResult(res);
    free(sql);
    return ErrorCode::GROUPID_NOT_FOUND;
}