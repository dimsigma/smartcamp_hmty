#include <cstdlib>
#include <iostream>
#include <regex>
#include <string.h>
#if OS_WINDOWS
#include <process.h>
#else
#include <unistd.h>
#endif

#include <toml++/toml.hpp>
#include <errors.hpp>

#include <Commands/Config.hpp>
#include <Foundation/Context.hpp>

Commands::Config::Config(const int argc, const char* const argv[]){
    if(argc==0) {
        this->err=ErrorCode::MISSING_PARAMS;
#ifdef DEBUG
        std::cout << "Config: Missing Parameters" << std::endl;
#endif
        return;
    }

    if(!strcmp(argv[0], "setserver")){
        if(argc!=2) {
            this->err=ErrorCode::MISSING_PARAMS;
            return;
        }

        this->err = this->setServer(argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "setCA")){
        if(argc!=2) {
            this->err=ErrorCode::MISSING_PARAMS;
            return;
        }

        this->err = this->setCA(argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "setCRT")){
        if(argc!=2) {
            this->err=ErrorCode::MISSING_PARAMS;
            return;
        }

        this->err = this->setCRT(argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "setKEY")){
        if(argc!=2) {
            this->err=ErrorCode::MISSING_PARAMS;
            return;
        }

        this->err = this->setKEY(argv[1]);
        if(err != ErrorCode::SUCCESS) printError(err);
        return;
    }

    if(!strcmp(argv[0], "-e")){
        Foundation::Context *context = Foundation::Context::getInstance();
#if OS_WINDOWS
        const char* _spawnvpargs[] = {"vim", context->getConfigFilePath(), NULL};
        _spawnvp(_P_WAIT, "vim", _spawnvpargs);
#else
        execlp("vim", "vim", context->getConfigFilePath(), NULL);
#endif
    }
}

Commands::Config::~Config(){
    
}

ErrorCode Commands::Config::setServer(const char* const arg){
    if(!strlen(arg)>0) {
#ifdef DEBUG
        std::cout << "Commands::Config::setServer: Invalid Input" << std::endl;
#endif
        return ErrorCode::INVALID_CONNECTION_STRING;
    }

    std::regex re("^(\\w+):?(\\w*)@([\\d.]+):(\\d+)$");
    std::cmatch match;
    std::regex_match(arg, match, re);

#ifdef DEBUG
    std::cout << match[1] << "\t" << match[2] << "\t" << match[3] << "\t" << match[4] << std::endl;
    std::cout << strcmp(match[2].str().c_str(),"") << std::endl;
#endif

    int hasPasswd = strcmp(match[2].str().c_str(),"") ? 1 : 0;

    std::cout << "Username: " << match[1] << std::endl;
    std::cout << "Has passwd: " << hasPasswd << std::endl;
    std::cout << "Password: " << match[2] << std::endl;
    std::cout << "IP: " << match[3] << std::endl;
    std::cout << "Port: " << match[4] << std::endl;

    toml::table tbl;
    if(hasPasswd) tbl = createTomlWithPass(match);
    else tbl = createTomlNoPass(match);

#ifdef DEBUG
    std::cout << "###### TOML ######" << "\n\n";
    std::cout << tbl << "\n\n";
#endif
    
    saveToFile(tbl);

    return ErrorCode::SUCCESS;
}

ErrorCode Commands::Config::setSSL(const char* const arg, const char* const param){
    if(!strlen(arg)>0){
#ifdef DEBUG
        std::cout << "Commands::Config::setSSL: Invalid Input" << std::endl;
#endif
        return ErrorCode::INVALID_CA_STRING;
    }

    Foundation::Context *context = Foundation::Context::getInstance();

    toml::table tbl;
    tbl = toml::parse_file(context->getConfigFilePath());
    auto result = (tbl["ssl"].as_table())->insert_or_assign(param, std::string(arg));

#ifdef DEBUG
    std::cout << result.second << " ###### TOML ######" << "\n\n";
    std::cout << tbl << "\n\n";
#endif

    saveToFile(tbl);

    return ErrorCode::SUCCESS;
}