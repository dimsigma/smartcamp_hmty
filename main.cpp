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
#include <Foundation/db.hpp>
#include <Foundation/Injector.hpp>
#include <Commands/Config.hpp>
#include <Commands/TestConnection.hpp>
#include <Commands/Show.hpp>
#include <Commands/Create.hpp>
#include <Commands/Describe.hpp>
#include <Commands/Update.hpp>
#include <Commands/Delete.hpp>
#include <Commands/Stats.hpp>

int main(int argc, char* argv[]){
    Foundation::Context* cont = Foundation::Context::getInstance();
    Foundation::Injector* inject = new Foundation::Injector(argc, argv);

    if(argc == 1){
        std::cout << "Missing Parameters" << std::endl;
        return 1;
    }

    if(!strcmp(argv[1], "config")){
        Commands::Config(argc-2,(char**) &argv[2]); //argc is decreased by 2 and also pass the 3 argument.
    }

    if(!strcmp(argv[1], "test")){
        Commands::TestConnection(argc-2,(char**) &argv[2]);
    }

    if(!strcmp(argv[1], "show")){
        Commands::Show(argc-2,(char**) &argv[2]);
    }

    if(!strcmp(argv[1], "create")){
        Commands::Create(argc-2,(char**) &argv[2]);
    }
  
    if(!strcmp(argv[1], "describe")){
        Commands::Describe(argc-2, (char **) &argv[2]);
    }

    if(!strcmp(argv[1], "update")){
        Commands::Update(argc-2, (char **) &argv[2]);
    }

    if(!strcmp(argv[1], "delete")){
        Commands::Delete(argc-2, (char **) &argv[2]);
    }

    if(!strcmp(argv[1], "stats")){
        Commands::Stats(argc-2, (char **) &argv[2]);
    }
  
    delete inject;
    delete cont;
    return (int) ErrorCode::SUCCESS;
}

/*
Foundation::db *db = Foundation::db::getInstance();
    const char* const query = "SELECT * FROM CUSTOMER;";
    MYSQL_RES *res;
    db->executeSQL(query, &res);
    
    std::cout << "Query Results:" << std::endl;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        for (unsigned int i = 0; i < mysql_num_fields(res); i++) {
            if(row[i]) std::cout << row[i] << "\t";
        }
        std::cout << std::endl;
    }
*/

/*int main() {
    // MySQL result set
    //MYSQL_ROW row;               // Row data


    const char* host = "127.0.0.1";  // MySQL server address
    const char* user = "smarty";       // MySQL username
    const char* database = "smartcamp"; // Database name
    const char* query = "SELECT * FROM CUSTOMER;"; // SELECT query

    // SSL Certificates 
    const char* ssl_key = "/Users/ssveronis/Library/CloudStorage/GoogleDrive-ssveronis@gmail.com/Άλλοι υπολογιστές/Ο υπολογιστής μου (1)/Σχολή/7ο εξάμηνο/Βάσεις Δεδομένων/docker/ssl/macOS/client-key.pem";  // Client private key
    const char* ssl_cert = "/Users/ssveronis/Library/CloudStorage/GoogleDrive-ssveronis@gmail.com/Άλλοι υπολογιστές/Ο υπολογιστής μου (1)/Σχολή/7ο εξάμηνο/Βάσεις Δεδομένων/docker/ssl/macOS/client-cert.pem"; // Client certificate
    const char* ssl_ca = "/Users/ssveronis/Library/CloudStorage/GoogleDrive-ssveronis@gmail.com/Άλλοι υπολογιστές/Ο υπολογιστής μου (1)/Σχολή/7ο εξάμηνο/Βάσεις Δεδομένων/docker/ssl/macOS/ca-cert.pem";      // CA certificate

    // Initialize MySQL connection
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "Could not initialize MySQL client library\n");
        exit(1);
    }

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
            if(row[i]) std::cout << row[i] << "\t";
        }
        std::cout << std::endl;
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
    mysql_library_end();

    std::cout << "Query executed successfully.\n";
    return 0;
}
*/