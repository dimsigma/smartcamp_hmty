#pragma once

#define setCharConfigVar(structParam, fileCategory, fileParam)  const char* const structParam = ((string) fileConfig[fileCategory][fileParam].value_or(""sv)).c_str(); \
                                                                this->config->structParam = (char*) malloc(sizeof(structParam)); \
                                                                strcpy(this->config->structParam, structParam);

#define setIntConfigVar(structParam, fileCategory, fileParam)   this->config->structParam = fileConfig[fileCategory][fileParam].value_or(0);

#define setStrConfigVar(structParam, fileCategory, fileParam)   (this->config->structParam).assign((string) fileConfig[fileCategory][fileParam].value_or(""sv));

namespace Foundation {
    typedef struct
    {
        char* ip;
        int port;
        char* username;
        int hasPassword;
        char* passwd;
        std::string sslCA;
        std::string sslCRT;
        std::string sslKEY;
    } Config;
}