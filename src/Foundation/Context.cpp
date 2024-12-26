#include <cstdlib>
#include <iostream>
#include <regex>
#include <string.h>

#if OS_WINDOWS
#include <windows.h>
#elif OS_MACOS
#include <dirent.h>
#elif OS_LINUX
#include <dirent.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>

#include <toml++/toml.hpp>

#include <errors.hpp>
#include <Foundation/Context.hpp>
#include <Foundation/Config.hpp>

using namespace Foundation;
using namespace std;

ErrorCode err;

Context::Context(){
    err = this->getConfigDirectory();
    if(err != ErrorCode::SUCCESS) this->printError();
    std::cout << "Config directory is: " << this->configFilePath << endl;
    
    err = this->getFile();
    if(err != ErrorCode::SUCCESS) this->printError();

    err = this->getConfig();
}

Context::~Context(){
    free((void*) this->configFilePath);
    if(this->configFilePointer != NULL) fclose((FILE*) this->configFilePointer);
}

ErrorCode Context::getConfigDirectory(){

#ifdef OS_WINDOWS
    const char* localappdata = getenv("LOCALAPPDATA");                                  //Get %localappdata%
    if(localappdata == nullptr) return ErrorCode::ENV_LOCALAPPDATA_NOT_SET;             //Check for errors
    char* fullPath = (char*) malloc(strlen(localappdata) + strlen(CONFIG_PATH) + 1);    //Allocate memory for the full path
    strcpy(fullPath, localappdata);                                                     //Copy to fullPath %localappdata%
#elif OS_MACOS
    const char* home = getenv("HOME");                                                  //Get $HOME
    if(home == nullptr) return ErrorCode::ENV_HOME_NOT_SET;                             //Check for errors
    char* fullPath = (char*) malloc(strlen(home) + strlen(CONFIG_PATH) + 1);            //Allocate memory for the full path
    strcpy(fullPath, home);                                                             //Copy to fullPath $HOME
#elif OS_LINUX
    const char* home = "/home/";                                                        //home directory
    const char* user = getenv("USER");                                                  //get username
    if(user == nullptr) return ErrorCode::ENV_XDG_CONFIG_HOME_NOT_SET;                  //Check for errors
    char* fullPath = (char*) malloc(strlen(home) + strlen(user) + strlen(CONFIG_PATH) + 1);//Allocate memory for the full path
    strcpy(fullPath, home);                                                             //Copy to fullPath $XDG_CONFIG_HOME
    strcat(fullPath, user);                                                             //Copy to fullPath the username
#endif

    strcat(fullPath, CONFIG_PATH);                                                      //Copy the rest of the path
    this->configFilePath = fullPath;                                                    //Point configFilePath to the allocated memory
    return ErrorCode::SUCCESS;
}

ErrorCode Context::getFile(){
    this->configFilePointer = fopen(this->configFilePath, "r+");                        //Try openning the file for read/write
    if(this->configFilePointer == NULL) {                                               //If the file does not exist
        regex re("^(.*)\\.config$");                                                    //Get the directory
        cmatch m;
        regex_match(this->configFilePath, m, re);                                       //match
        //cout << m[1] << endl;
        
#if OS_WINDOWS
        if (!CreateDirectory(                                                           //https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createdirectory
            m[1].str().c_str(),
            NULL
        ) && GetLastError() == ERROR_PATH_NOT_FOUND) {
            cout << "Windows Error: 3" << endl;
            return ErrorCode::WIN32_ERROR;
        }
#else
        DIR* d = opendir(m[1].str().c_str());                                           //Try opening the directory
        if (d) closedir(d);                                                             //If it exists, close it
        else if (ENOENT == errno) {                                                     //If the directory does not exist
            mkdir(m[1].str().c_str(),                                                   //create it
                S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH);   // rwxr-xr--
        } else return ErrorCode::UNKNOWN_ERROR;                                         //opendir() failed
#endif

        this->configFilePointer = fopen(this->configFilePath, "w");                     //Create the file
        if(this->configFilePointer == NULL) return ErrorCode::UNABLE_TO_CREATE_CONFIG_FILE;
        std::cout << "Config file created" << endl;
    }
    std::cout << "Config file opened" << endl;
    fclose((FILE*) this->configFilePointer);
    return ErrorCode::SUCCESS;
}

ErrorCode Context::getConfig(){
    this->config = (Config*) malloc(sizeof(Config));
    
    auto fileConfig = toml::parse_file(this->configFilePath);

    /*const char* const ip = ((string) fileConfig["server"]["ip"].value_or(""sv)).c_str();
    this->config->ip = (char*) malloc(sizeof(ip));
    strcpy(this->config->ip, ip);*/
    setCharConfigVar(ip, "server", "ip");
    setIntConfigVar(port, "server", "port");

    setCharConfigVar(username, "user", "username");
    setCharConfigVar(passwd, "user", "passwd");
    this->config->hasPassword = (strcmp(this->config->passwd, "") == 0) ? 0 : 1;

    setStrConfigVar(sslCA, "ssl", "ca");
    setStrConfigVar(sslCRT, "ssl", "crt");
    setStrConfigVar(sslKEY, "ssl", "key");

#ifdef DEBUG
    std::cout << this->config->ip << endl;
    std::cout << this->config->port << endl;
    std::cout << this->config->username << endl;
    std::cout << this->config->passwd << endl;
    std::cout << this->config->hasPassword << endl;
    std::cout << this->config->sslCA << endl;
    std::cout << this->config->sslCRT << endl;
    std::cout << this->config->sslKEY << endl;
#endif

    return ErrorCode::SUCCESS;
}

void Context::printError(){
    cerr << "Error: " << hex << (int) err << endl;
    exit((int) err);
}