#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Describe.hpp>

using namespace Commands;

Describe::Describe(const int argc, const char* const argv[])
{
    if(argc < 1){
        this->err = ErrorCode::MISSING_PARAMS;
        printError(err);
        return;
    }

    if(!strcmp(argv[0], "customer")){
        this->err = this->customerGeneral(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->customerReservation(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "reservation")){
        this->err = this->reservationGeneral(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationAccomodation(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationServices(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationParking(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }

        this->err = this->reservationPayment(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
        return;
    }

    if(!strcmp(argv[0], "accomodation")){
        this->err = this->accomodationGeneral(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
        
        this->err = this->accomodationReservation(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }
}

Describe::~Describe() {}