#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#ifdef OS_WINDOWS
#include <mysql.h>
#elif OS_MACOS
#include <mysql/mysql.h>
#elif OS_LINUX
#include <mysql/mysql.h>
#endif

#include <toml++/toml.hpp>

#include <errors.hpp>

#include <Foundation/Context.hpp>
#include <Commands/Reservation-General-Info.hpp>

Commands::ReservationGeneralInfo::ReservationGeneralInfo(const int argc, const char* const argv[])
{
    if(argc != 4) {
        this->err=ErrorCode::MISSING_PARAMS;
#ifdef DEBUG
        std::cout << "Reservation-General-Info: Missing Parameters";
        std::cout << "Correct format: Reservation-General-Info firstname lastname checkindate" << std::endl;
#endif
        printError(err);
        return;
    }

    setFirstname(argv[0]);
    setLastname(argv[1]);
    setCheckindate(argv[2]);

    printInfo(GENERAL);
    printInfo(PAYMENT);
    printInfo(ACCOMODATION);
    printInfo(SERVICES);
    printInfo(PARKING);
}

int Commands::ReservationGeneralInfo::MySQL_connect()
{ 
    // Initialize MySQL connection
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "Could not initialize MySQL client library\n");
        exit(1);
    }

    conn = mysql_init(NULL);
    if (conn == nullptr) {
        fprintf(stderr, "MySQL initialization failed!");
        return 1;
    }

    // Set SSL options
    if (mysql_ssl_set(conn, ssl_key, ssl_cert, ssl_ca, nullptr, nullptr)) {
        std::cerr << "Failed to set SSL options: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Connect to the MySQL database 
    if (!mysql_real_connect(conn, host, user, nullptr, database, 3306, nullptr, CLIENT_SSL)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        return 1;
    }

    // Verify SSL connection
    if (mysql_get_ssl_cipher(conn)) {
        std::cout << "SSL Connection Established using " << mysql_get_ssl_cipher(conn) << std::endl;
    } else {
        std::cerr << "SSL Connection failed or not used!" << std::endl;
        mysql_close(conn);
        return 1;
    }
}

int Commands::ReservationGeneralInfo::printInfo(qtype type)
{
    char *q_part1;
    std::string title1, title2, title3;

    // Distinguish between the different querries

    switch (type)
    {
    case 1:
        strcpy(q_part1, general_part1);
        title1 = "General-Info query failed: ";
        title2 = "Failed to retrieve General-Info result set:";
        title3 = "\n\nGeneral-Info:\n";
        break;
    
    case 2:
        strcpy(q_part1, accomodation_part1);
        title1 = "Accomodation Spot-Info query failed: ";
        title2 = "Failed to retrieve Accomodation Spot-Info result set:";
        title3 = "\nAccomodation Spot-Info:\n";
        break;
    
    case 3:
        strcpy(q_part1, parking_part1);
        title1 = "Parking Spot-Info query failed: ";
        title2 = "Failed to retrieve Parking Spot-Info result set:";
        title3 = "\nParking Spot-Info:\n";
        break;
    
    case 4:
        strcpy(q_part1, services_part1);
        title1 = "Services-Info query failed: ";
        title2 = "Failed to retrieve Services-Info result set:";
        title3 = "\nServices-Info:\n";
        break;
    
    case 5:
        strcpy(q_part1, payment_part1);
        title1 = "Payment-Info query failed: ";
        title2 = "Failed to retrieve Payment-Info result set:";
        title3 = "\nPayment-Info:\n";
        break;
    }

    // Form final query
    char *query, *q2, *q3;
    strcpy(query, q_part1);
    strcpy(q2, q_part2);
    strcpy(q3, q_part3);

    strcat(query, first_name);
    strcat(query, q2);
    strcat(query, last_name);
    strcat(query, q3);
    strcat(query, checkin_date);
    strcat(query, ";");

    // Execute query
    if (mysql_query(conn, query)) {
        std::cerr << title1 << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Store the result set
    MYSQL_RES *res = mysql_store_result(conn);
    if (res == nullptr) {
        std::cerr << title2 << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Print the query results
    std::cout << title3;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        for (unsigned int i = 0; i < mysql_num_fields(res); i++) {
            if(row[i]) std::cout << row[i] << "\t";
        }
        std::cout << std::endl;
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
    mysql_library_end();
}