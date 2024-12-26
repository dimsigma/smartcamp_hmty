#include <iostream>
#include <cstdlib>

#include <errors.hpp>

void printError(ErrorCode err){
    std::cerr << "Error: " << std::hex << (int) err << std::endl;
    exit((int) err);
}