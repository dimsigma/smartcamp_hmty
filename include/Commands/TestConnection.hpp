#pragma once

#include <errors.hpp>

namespace Commands {
    class TestConnection
    {
    private:
        ErrorCode err;
    public:
        TestConnection(const int argc, const char* const argv[]);
        ~TestConnection();
    };
    
}