#pragma once

#include <regex>

#include <toml++/toml.hpp>
#include <errors.hpp>

#include <Foundation/Context.hpp>

#define setCA(arg) setSSL(arg, "ca");
#define setCRT(arg) setSSL(arg, "crt");
#define setKEY(arg) setSSL(arg, "key");

namespace Commands {
    class Config
    {
    private:
        ErrorCode err;

        ErrorCode setServer(const char* const arg);
        ErrorCode setSSL(const char* const arg, const char* const param);

        inline toml::table createTomlNoPass(std::cmatch match){
            Foundation::Context *context = Foundation::Context::getInstance();
            return toml::table{
                { "server", toml::table{
                        { "ip", match[3].str().c_str() },
                        { "port", match[4].str().c_str() }
                    }
                },
                { "user", toml::table{
                        { "username", match[1].str().c_str() }
                    }
                },
                { "ssl", toml::table{
                        {"ca", context->config->sslCA},
                        {"crt", context->config->sslCRT},
                        {"key", context->config->sslKEY}
                    }
                }
            };
        }

        inline toml::table createTomlWithPass(std::cmatch match){
            Foundation::Context *context = Foundation::Context::getInstance();
            return toml::table{
                { "server", toml::table{
                        { "ip", match[3].str().c_str() },
                        { "port", match[4].str().c_str() }
                    }
                },
                { "user", toml::table{
                        { "username", match[1].str().c_str() },
                        { "passwd", match[2].str().c_str() }
                    }
                },
                { "ssl", toml::table{
                        {"ca", context->config->sslCA},
                        {"crt", context->config->sslCRT},
                        {"key", context->config->sslKEY}
                    }
                }
            };
        }

        inline void saveToFile(toml::table tbl){
            Foundation::Context *context = Foundation::Context::getInstance();
            std::ofstream file(context->getConfigFilePath());
            file << tbl << std::endl;
            file.close();
        }
    public:
        Config(const int argc, const char* const argv[]);
        ~Config();
    };
    
}