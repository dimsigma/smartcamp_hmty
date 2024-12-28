#pragma once

#include <errors.hpp>

#define reservationsTODAY "RESERVATION.checkin_date = CURDATE()"
#define reservationsNEXT30D "RESERVATION.checkin_date <= DATE_ADD(CURDATE(), INTERVAL 30 DAY) AND RESERVATION.checkin_date >= CURDATE()"
#define reservationsPAST30d "RESERVATION.checkin_date >= DATE_SUB(CURDATE(), INTERVAL 30 DAY) AND RESERVATION.checkin_date <= CURDATE()"
#define reservationsPAST6m "RESERVATION.checkin_date >= DATE_SUB(CURDATE(), INTERVAL 6 MONTH) AND RESERVATION.checkin_date <= CURDATE()"
#define reservationsPAST1y "RESERVATION.checkin_date >= DATE_SUB(CURDATE(), INTERVAL 1 YEAR) AND RESERVATION.checkin_date <= CURDATE()"

#define customersRETURNING "( SELECT COUNT(RESERVATION.main_cuid) FROM RESERVATION WHERE RESERVATION.main_cuid = CUSTOMER.cuid GROUP BY RESERVATION.main_cuid HAVING COUNT(RESERVATION.main_cuid)>1 )"

#define paymentsUNPAID "SELECT RESERVATION.ruid, RESERVATION.total_cost, SUM(PAYMENT.amount) AS total_paid FROM RESERVATION JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid LEFT OUTER JOIN PAYMENT ON PAYMENT.ruid = RESERVATION.ruid WHERE 1 GROUP BY RESERVATION.ruid HAVING RESERVATION.total_cost > SUM(PAYMENT.amount) OR SUM(PAYMENT.amount) IS NULL;"

namespace Commands {
    class Show
    {
    private:
        ErrorCode err;

        const char* const showReservationsSQL = "SELECT * FROM RESERVATION JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s;";
        const char* const showCustomersSQL = "SELECT * FROM CUSTOMER WHERE %s;";
        const char* const showPaymentsSQL = "SELECT PAYMENT.*, CUSTOMER.first_name, CUSTOMER.middle_name, CUSTOMER.last_name, CUSTOMER.cuid FROM PAYMENT JOIN RESERVATION ON PAYMENT.ruid = RESERVATION.ruid JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s;";

        ErrorCode reservations(const int argc, const char* const argv[]);
        ErrorCode customers(const int argc, const char* const argv[]);
        ErrorCode payments(const int argc, const char* const argv[]);
    public:
        Show(const int argc, const char* const argv[]);
        ~Show();
    };
    
}