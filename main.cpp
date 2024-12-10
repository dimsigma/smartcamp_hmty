#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>

int main() {
    // MySQL result set
    //MYSQL_ROW row;               // Row data


    const char* host = "127.0.0.1";  // MySQL server address
    const char* user = "smarty";       // MySQL username
    const char* database = "smartcamp"; // Database name
    const char* query = "SELECT * FROM CUSTOMER;"; // SELECT query

    // SSL Certificates (Replace with actual paths to your certificates)
    const char* ssl_key = "C:\\Univeristy\\Κατεύθυνση\\Βάσεις δεδομένων\\Εργασία\\smartcamp\\client.key";  // Client private key
    const char* ssl_cert = "C:\\Univeristy\\Κατεύθυνση\\Βάσεις δεδομένων\\Εργασία\\smartcamp\\client.crt"; // Client certificate
    const char* ssl_ca = "C:\\Univeristy\\Κατεύθυνση\\Βάσεις δεδομένων\\Εργασία\\smartcamp\\ca.crt";      // CA certificate

    // Initialize MySQL connection
    MYSQL *conn;
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

    /*if (mysql_options(conn, MYSQL_OPT_SSL_CIPHER, "TLS_AES_128_GCM_SHA256") != 0) {
        std::cerr << "Failed to set SSL cipher: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }*/

    // Connect to the MySQL database without a password
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

    // Execute the SELECT query
    if (mysql_query(conn, query)) {
        std::cerr << "SELECT query failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Store the result set
    MYSQL_RES *res = mysql_store_result(conn);
    if (res == nullptr) {
        std::cerr << "Failed to retrieve result set: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Print the query results
    std::cout << "Query Results:\n";
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        for (unsigned int i = 0; i < mysql_num_fields(res); i++) {
            std::cout << row[i] << "\t";
        }
        std::cout << std::endl;
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    std::cout << "Query executed successfully.\n";
    return 0;
}
