#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Update.hpp>

using namespace Commands;

Update::Update(const int argc, const char* const argv[])
{
    if(argc < 1){
        this->err = ErrorCode::MISSING_PARAMS;
        printError(err);
        return;
    }

    if(!strcmp(argv[0], "customer")){
        this->err = this->customer(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->customerShow(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if((!strcmp(argv[0], "reservation")) && (!strcmp(argv[1], "cost"))){
        this->err = this->reservationCost(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationCostShow(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if((!strcmp(argv[0], "reservation")) && (!strcmp(argv[1], "services"))){
        this->err = this->reservationServices(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationServicesShow(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if((!strcmp(argv[0], "reservation")) && (!strcmp(argv[1], "parking"))){
        this->err = this->reservationParking(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationParkingShow(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if((!strcmp(argv[0], "reservation")) && (!strcmp(argv[1], "accomodation"))){
        this->err = this->reservationAccomodation(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationAccomodationShow(argc-2, (char **) &argv[2]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }
}

Update::~Update() {}