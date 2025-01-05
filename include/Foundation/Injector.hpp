#pragma once

#include <regex>

#include <errors.hpp>

#define InjectorPatern ".*(?:(?:[Ss][Ee][Ll][Ee][Cc][Tt])|(?:[Ii][Nn][Ss][Ee][Rr][Tt])|(?:[Dd][Rr][Oo][Pp])|(?:[Aa][Ll][Tt][Ee][Rr])|(?:[Uu][Nn][Ii][Oo][Nn])|(?:[Ww][Hh][Ee][Rr][Ee])|(?:[Aa][Nn][Dd])|(?:[Oo][Rr])|(?:[Ll][Ii][Kk][Ee])|(?:[Ii][Nn])|(?:[Ee][Xx][Ii][Ss][Tt][Ss])|(?:[Oo][Rr][Dd][Ee][Rr])|(?:[Gg][Rr][Oo][Uu][Pp])|(?:[Hh][Aa][Vv][Ii][Nn][Gg])|(?:[Ee][Xx][Ee][Cc][Uu][Tt][Ee])|(?:[Cc][Aa][Ss][Tt])|(?:[Cc][Oo][Nn][Vv][Ee][Rr][Tt])|(?:[Ll][Ii][Mm][Ii][Tt])|(?:[Oo][Ff][Ff][Ss][Ee][Tt])|(?:[Jj][Oo][Ii][Nn])|(?:[Dd][Ee][Ss][Cc][Rr][Ii][Bb][Ee])|(?:[Tt][Aa][Bb][Ll][Ee])|(?:[Dd][Aa][Tt][Aa][Bb][Aa][Ss][Ee])|;|#).*"

namespace Foundation {
    class Injector
    {
    private:
        ErrorCode err;
        ErrorCode match(std::regex re, const char* const arg) const;
    public:
        Injector(const int argc, const char* const argv[]);
        ~Injector();
    };
    
}