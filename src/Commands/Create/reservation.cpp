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


ErrorCode Create::reservation(const int argc, const char* const argv[]){
    ErrorCode err;
    Foundation::db *db = Foundation::db::getInstance();
    MYSQL_RES *res;

    if(argc != 5) {
        return ErrorCode::MISSING_PARAMS;
    }

    ReservationData *data = (ReservationData*) malloc(sizeof(ReservationData));
    data->checkinData = argv[0];
    data->checkoutData = argv[1];
    data->people = atoi(argv[2]);
    data->spots = atoi(argv[3]);
    data->parking = atoi(argv[4]);

    if(data->people == 0 || data->spots == 0) return ErrorCode::INVALID_PARAMS;
    if(data->people < data->spots) return ErrorCode::INVALID_PARAMS;
    if(data->people < data->parking) return ErrorCode::INVALID_PARAMS;

    int* cuids = (int*) malloc(data->people * sizeof(int)); //Important

    db->executeSQL("START TRANSACTION;");

    std::cout << "Main Customer:" << std::endl;
    err = handleCustomer(&cuids[0]);
    if(err != ErrorCode::SUCCESS) {
        free(cuids);
        db->executeSQL("ROLLBACK;");
        return err;
    }

    for(int i = 1; i < data->people; i++){
        std::cout << "Next Customer:" << std::endl;
        err = handleCustomer(&cuids[i]);
        if(err != ErrorCode::SUCCESS) {
            free(cuids);
            db->executeSQL("ROLLBACK;");
            return err;
        }
    }

    int suid; //Important
    int defaultCost; //Important

    err = getAccommodationGroupId(data, this->neighbouringAccomodation, &suid, &defaultCost);
    if(err != ErrorCode::SUCCESS) {
        free(cuids);
        db->executeSQL("ROLLBACK;");
        return err;
    }

#ifdef DEBUG
    std::cout << "Selected first suid: " << suid << std::endl;
#endif

    PARKING_SPOT *spots = (PARKING_SPOT*)malloc(data->parking * sizeof(PARKING_SPOT));      //Important
    int actualParkingSpots;                                                                 //Important
    err = getAvailParking(data, spots, this->availableParking, &actualParkingSpots);
    if(err != ErrorCode::SUCCESS) {
        free(cuids);
        free(spots);
        db->executeSQL("ROLLBACK;");
        return err;
    }

#ifdef DEBUG
    std::cout << spots[0].letters << spots[0].number << std::endl;
#endif

    int ruid; //Important
    err = createReservationEntry(data, defaultCost, cuids, &ruid);
    if(err != ErrorCode::SUCCESS) {
        free(cuids);
        for(int i = 0; i < actualParkingSpots; i++) free(spots[i].letters);
        free(spots);
        db->executeSQL("ROLLBACK;");
        return err;
    }

    err = createContainedCustomer(data, cuids, ruid);
    if(err != ErrorCode::SUCCESS) {
        free(cuids);
        for(int i = 0; i < actualParkingSpots; i++) free(spots[i].letters);
        free(spots);
        db->executeSQL("ROLLBACK;");
        return err;
    }

    err = createReservedSpot(data, suid, ruid);
    if(err != ErrorCode::SUCCESS) {
        free(cuids);
        for(int i = 0; i < actualParkingSpots; i++) free(spots[i].letters);
        free(spots);
        db->executeSQL("ROLLBACK;");
        return err;
    }

    err = createReservedParking(actualParkingSpots, spots, ruid);

    db->executeSQL("COMMIT;");
    free(cuids);
    for(int i = 0; i < actualParkingSpots; i++) free(spots[i].letters);
    free(spots);
    return ErrorCode::SUCCESS;
}

