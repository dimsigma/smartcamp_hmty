#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Show.hpp>

using namespace Commands;

Show::Show(const int argc, const char* const argv[]) {
    if(argc < 1) {
        this->err=ErrorCode::MISSING_PARAMS;
        printError(err);
        return;
    }

    if(!strcmp(argv[0], "reservations")){
        this->err = this->reservations(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "customers")){
        this->err = this->customers(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "payments")){
        this->err = this->payments(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "services")){
        this->err = this->services(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "parking")){
        this->err = this->parking(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "accommodation")){
        this->err = this->accommodation(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "spotclass")){
        this->err = this->spot_class(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "spotclasscount")){
        this->err = this->spot_class_count(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }
}

Show::~Show() {}

