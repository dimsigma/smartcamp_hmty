#pragma once

#include <errors.hpp>

#if OS_WINDOWS
#define CONFIG_PATH "\\smartcamp\\.config"
#elif OS_MACOS
#define CONFIG_PATH "/Library/Application Support/smartcamp/.config"
#elif OS_LINUX
#define CONFIG_PATH "/.config/smartcamp/.config"
#endif

namespace Foundation {

class Context
{
private:
    /* data */
    char* configFilePath;               //The path to the config file
    std::FILE* configFilePointer;       //Pointer to the config file

    ErrorCode getConfigDirectory();     //Sets configFilePath
    ErrorCode getFile();                //Sets configFilePointer (Also creates file and directory if needed)
    void printError();                  //Prints error codes
public:
    Context();                          //Constructor
    ~Context();                         //Deconstractor
};

}