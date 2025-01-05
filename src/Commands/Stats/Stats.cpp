#include <cstdlib>
#include <iostream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Stats.hpp>

using namespace Commands;

Stats::Stats(const int argc, const char* const argv[])
{
    if(argc < 1){
        this->err = ErrorCode::MISSING_PARAMS;
        printError(err);
        return;
    }

    if(!strcmp(argv[0], "occupancy")){
        this->err = this->occupancy(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
    }

    if(!strcmp(argv[0], "earnings")){
        this->err = this->earnings(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
    }

    if(!strcmp(argv[0], "accomodation")){
        this->err = this->accomodation(argc-1, (char **) &argv[1]);
        if(err != ErrorCode::SUCCESS){
            printError(err);
            return;
        }
    }
}

Stats::~Stats() {}