#pragma once

#define setCharConfigVar(structParam, fileCategory, fileParam)  const char* const structParam = ((string) fileConfig[fileCategory][fileParam].value_or(""sv)).c_str(); \
                                                                this->config->structParam = (char*) malloc((strlen(structParam) * sizeof(char)) + 1); \
                                                                strcpy(this->config->structParam, structParam);

#define setIntConfigVar(structParam, fileCategory, fileParam)   this->config->structParam = fileConfig[fileCategory][fileParam].value_or(3306);

#define setStrConfigVar(structParam, fileCategory, fileParam)   const std::string structParam = (std::string) fileConfig[fileCategory][fileParam].value_or(""sv); \
                                                                this->config->structParam = (char*) malloc((strlen(structParam.c_str()) * sizeof(char)) + 1); \
                                                                strcpy(this->config->structParam, structParam.c_str());

namespace Foundation {
    typedef struct
    {
        char* ip;
        int port;
        char* username;
        int hasPassword;
        char* passwd;
        char* sslCA;
        char* sslCRT;
        char* sslKEY;
    } Config;
}