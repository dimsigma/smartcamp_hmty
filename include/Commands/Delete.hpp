#pragma once

#include <errors.hpp>

namespace Commands {
    class Delete
    {
    private:
        ErrorCode err;

        // delete reservation <ruid>
        const char* const reservation = "DELETE FROM RESERVATION WHERE ruid = %s;";

        // delete customer <cuid>
        const char* const customer = "DELETE FROM CUSTOMER WHERE cuid = %s;";

        // delete service <name>
        const char* const service = "DELETE FROM SERVICE WHERE name = '%s';";

        ErrorCode delReservation(const int argc, const char* const argv[]);
        ErrorCode delCustomer(const int argc, const char* const argv[]);
        ErrorCode delService(const int argc, const char* const argv[]);

    public:
        Delete(const int argc, const char* const argv[]);
        ~Delete();
    };
}