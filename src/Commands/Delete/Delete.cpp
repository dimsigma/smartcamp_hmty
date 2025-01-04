#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Delete.hpp>

using namespace Commands;

Delete::Delete(const int argc, const char* const argv[])
{
    if(argc < 1){
        this->err = ErrorCode::MISSING_PARAMS;
        printError(err);
        return;
    }

    if(!strcmp(argv[0], "reservation")){
        this->err = this->delReservation(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
    }

    if(!strcmp(argv[0], "customer")){
        this->err = this->delCustomer(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
    }

    if(!strcmp(argv[0], "service")){
        this->err = this->delService(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
    }
}

Delete::~Delete() {}