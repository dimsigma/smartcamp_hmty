#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Create.hpp>

using namespace Commands;

Create::Create(const int argc, const char* const argv[]){
    if(argc < 1) {
        this->err=ErrorCode::MISSING_PARAMS;
        printError(err);
        return;
    }

    if(!strcmp(argv[0], "reservation")){
        this->err = this->reservation(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "payment")){
        this->err = this->payment(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "service")){
        this->err = this->service(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }
}

Create::~Create(){}