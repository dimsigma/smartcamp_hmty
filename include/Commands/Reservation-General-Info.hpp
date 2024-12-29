#pragma once

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
#include <Commands/Config.hpp>

namespace Commands{
    class ReservationGeneralInfo
    {
        private:
            ErrorCode err;

            // Οι επόμενες 7 μεταβλητές έχουν να κάνουν με τη σύνδεση στη βάση και ίσως πρέπει να αλλάξουν
            const char *host = "127.0.0.1";     // MySQL server address
            const char *user = "smarty";        // MySQL username
            const char *database = "smartcamp"; // Database name

            const char *ssl_key = "C:/Univeristy/Κατεύθυνση/Βάσεις δεδομένων/Εργασία/smartcamp/client.key";     // Client key
            const char *ssl_cert = "C:/Univeristy/Κατεύθυνση/Βάσεις δεδομένων/Εργασία/smartcamp/client.crt";    // Client certificate
            const char *ssl_ca = "C:/Univeristy/Κατεύθυνση/Βάσεις δεδομένων/Εργασία/smartcamp/ca.crt";          // CA certificate

            MYSQL *conn;

            char *first_name;
            char *last_name;
            char *checkin_date;

            const char *general_part1 = "SELECT res.ruid, cus.first_name, cus.last_name, "
            "res.checkin_date, res.checkout_date, res.total_cost "
            "FROM RESERVATION AS res "
            "JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid "
            "WHERE cus.first_name = ";

            const char *accomodation_part1 = "SELECT acc_s.suid, acc_s.commercial_name, sp_s.class_name, "
            "sp_c.class_type, sp_c.season, sp_c.cost "
            "FROM RESERVATION AS res "
            "JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
            "JOIN ACCOMODATION_SPOT AS acc_s ON res_s.suid = acc_s.suid "
            "JOIN SPOT_CLASS AS sp_c ON "
            "(acc_s.class_name = sp_c.class_name AND acc_s.class_type = sp_c.class_type AND acc_s.season = sp_c.season) "
            "JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid "
            "WHERE cus.first_name = ";

            const char *parking_part1 = "SELECT park_s.letter, park_s.number "
            "FROM RESERVATION AS res "
            "JOIN RESERVED_PARKING AS res_p ON res.ruid = res_p.ruid "
            "JOIN PARKING_SPOT AS park_s ON " 
            "(res_p.pletter = park_s.letter AND res_p.pnumber = park_s.number) "
            "JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid "
            "WHERE cus.first_name = ";

            const char *services_part1 = "SELECT ser.name"
            "FROM RESERVATION AS res "
            "JOIN INCLUDED_SERVICE AS inc_ser ON res.ruid = inc_ser.ruid "
            "JOIN SERVICE AS ser ON inc_ser.service_name = ser.name "
            "JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid "
            "WHERE cus.first_name = ";

            const char *payment_part1 = " SELECT pay.puid, pay.method, pay.amount, pay.date "
            "FROM RESERVATION AS res "
            "JOIN PAYMENT AS pay ON res.ruid = pay.ruid "
            "JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid "
            "WHERE cus.first_name = ";

            const char *q_part2 = " AND cus.last_name = ";
            const char *q_part3 = " AND res.checkin_date = ";

            enum qtype{
                GENERAL = 1, ACCOMODATION = 2,
                PARKING = 3, SERVICES = 4,
                PAYMENT = 5
            };

            inline void setFirstname(const char * arg){
                strcpy(first_name, arg);
            }

            inline void setLastname(const char * arg){
                strcpy(last_name, arg);
            }

            inline void setCheckindate(const char * arg){
                strcpy(checkin_date, arg);
            }

            int MySQL_connect(void); // Ίσως πρέπει να αλλάξει αυτή η συνάρτηση
            int printInfo(qtype type);
            
        public:
            ReservationGeneralInfo(const int argc, const char* const argv[]);
    };  
}