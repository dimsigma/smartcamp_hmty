#pragma once

#include <errors.hpp>
#include <Foundation/Config.hpp>

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
    const char* configFilePath;               //The path to the config file
    const std::FILE* configFilePointer;       //Pointer to the config file
    Foundation::Config* config;

    ErrorCode getConfigDirectory();     //Sets configFilePath
    ErrorCode getFile();                //Sets configFilePointer (Also creates file and directory if needed)
    ErrorCode getConfig();
    void printError();                  //Prints error codes

    inline static Context* instance = nullptr;

    Context();                          //Constructor
public:
    Context(const Context& obj) = delete;

    inline static Context* getInstance(){
        if(instance == nullptr) instance = new Context();
        return instance;
    }

    ~Context();                         //Deconstractor
};

}