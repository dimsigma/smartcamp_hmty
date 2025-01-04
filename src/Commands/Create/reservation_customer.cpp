#include <cstdlib>
#include <iostream>
#include <sstream>

#include <errors.hpp>

#include <Foundation/db.hpp>

#include <Commands/Create/reservation_customer.h>

struct Customer {
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string phoneCountryCode;
    std::string phoneNumber;
};

ErrorCode handleCustomer(int *cuid){
    std::string newCust;

    std::cout << "Are you entering a new Customer or an existing Customer?" << std::endl;
    std::cout << "1. New Customer" << std::endl;
    std::cout << "2. Existing Customer" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    //std::cin >> newCust;
    std::getline(std::cin, newCust);

    if (newCust == "1") {
        return handleNewCustomer(cuid);
    } else if (newCust == "2") {
        return handleExistingCustomer(cuid);
    } else {
        std::cout << "Invalid choice. Please run the program again." << std::endl;
    }

    return ErrorCode::SUCCESS;
}

ErrorCode handleNewCustomer(int *cuid){
    Customer customer;
    ErrorCode sqlerr;

    // First Name
    std::cout << "Enter First Name: ";
    std::getline(std::cin, customer.firstName);

    // Middle Name (Optional)
    std::cout << "Enter Middle Name (or press Enter to skip): ";
    std::getline(std::cin, customer.middleName);

    // Last Name
    std::cout << "Enter Last Name: ";
    std::getline(std::cin, customer.lastName);

    // Phone Country Code (Optional)
    std::cout << "Enter Phone Country Code (or press Enter to skip): ";
    std::getline(std::cin, customer.phoneCountryCode);

    // Phone Number (Optional)
    std::cout << "Enter Phone Number (or press Enter to skip): ";
    std::getline(std::cin, customer.phoneNumber);

    //Create the query //https://stackoverflow.com/questions/12233710/how-do-i-use-the-ostringstream-properly-in-c
    std::ostringstream sql;
    sql << "INSERT INTO CUSTOMER (first_name, middle_name, last_name, tel_country, tel_num) VALUES ('" << customer.firstName << "', ";
    if (!customer.middleName.empty()) sql << "'" << customer.middleName << "', ";
    else sql << "NULL, ";
    sql << "'" << customer.lastName << "', ";
    if (!customer.phoneCountryCode.empty()) sql << "'" << customer.phoneCountryCode << "', ";
    else sql << "'0030', ";
    if (!customer.phoneNumber.empty()) sql << customer.phoneNumber;
    else sql << "NULL";
    sql << ");";

    Foundation::db *db = Foundation::db::getInstance();
    sqlerr = db->executeSQL(sql.str().c_str());
    if(sqlerr != ErrorCode::SUCCESS){
        return sqlerr;
    }

    MYSQL_RES *res;
    sqlerr = db->executeSQL(getLastIDQuery, &res);
    if(sqlerr != ErrorCode::SUCCESS){
        return sqlerr;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int id = atoi(row[0]);
    std::cout << id << std::endl;

    if(id == 0) {
        return ErrorCode::INSERT_FAILED;
    }

    db->freeResult(res);

    *cuid = id;

    return ErrorCode::SUCCESS;
}

ErrorCode handleExistingCustomer(int *cuid){
    ErrorCode sqlerr;
    MYSQL_RES *res;

    std::string cuidinput;

    std::cout << "Enter Customer Unique ID (CUID): ";
    std::getline(std::cin, cuidinput);

    char* sql;
    sql = (char*) malloc((strlen(validateCUID) + strlen(cuidinput.c_str())) * sizeof(char));
    sprintf(sql, validateCUID, cuidinput.c_str());

    Foundation::db *db = Foundation::db::getInstance();
    sqlerr = db->executeSQL(sql, &res);
    if(sqlerr != ErrorCode::SUCCESS){
        return sqlerr;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int c = atoi(row[0]);
    std::cout << c << std::endl;

    if(c == 0) {
        return ErrorCode::INSERT_FAILED;
    }

    db->freeResult(res);
    free(sql);

    *cuid = atoi(cuidinput.c_str());

    return ErrorCode::SUCCESS;
}