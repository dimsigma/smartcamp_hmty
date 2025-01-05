#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <regex>

#include <errors.hpp>

#include <Foundation/Injector.hpp>

using namespace Foundation;

Injector::Injector(const int argc, const char* const argv[]){
    std::regex re(InjectorPatern);
    for(int i = 0; i < argc; i++){
#ifdef DEBUG
        std::cout << argv[i] << std::endl;
#endif
        this->err = this->match(re, argv[i]);
        if(this->err != ErrorCode::SUCCESS) printError(this->err);
    }
}

Injector::~Injector(){}

ErrorCode Injector::match(std::regex re, const char* const arg) const {
    std::cmatch match;
    bool regexResult = std::regex_match(arg, match, re);
#ifdef DEBUG
        std::cout << regexResult << std::endl;
#endif
    if(regexResult) return ErrorCode::REGEX_ARGV_MATCH;
    else return ErrorCode::SUCCESS;
}