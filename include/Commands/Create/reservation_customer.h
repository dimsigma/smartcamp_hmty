#pragma once

#include <errors.hpp>

#define getLastIDQuery "SELECT LAST_INSERT_ID();"
#define validateCUID "SELECT COUNT(*) FROM CUSTOMER WHERE CUSTOMER.cuid=%s;"

ErrorCode handleCustomer(int *cuid);
ErrorCode handleNewCustomer(int *cuid);
ErrorCode handleExistingCustomer(int *cuid);