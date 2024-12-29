#pragma once

#include <errors.hpp>

#define reservationsTODAY "RESERVATION.checkin_date = CURDATE()"
#define reservationsNEXT30D "RESERVATION.checkin_date <= DATE_ADD(CURDATE(), INTERVAL 30 DAY) AND RESERVATION.checkin_date >= CURDATE()"
#define reservationsPAST30d "RESERVATION.checkin_date >= DATE_SUB(CURDATE(), INTERVAL 30 DAY) AND RESERVATION.checkin_date <= CURDATE()"
#define reservationsPAST6m "RESERVATION.checkin_date >= DATE_SUB(CURDATE(), INTERVAL 6 MONTH) AND RESERVATION.checkin_date <= CURDATE()"
#define reservationsPAST1y "RESERVATION.checkin_date >= DATE_SUB(CURDATE(), INTERVAL 1 YEAR) AND RESERVATION.checkin_date <= CURDATE()"

#define customersRETURNING "( SELECT COUNT(RESERVATION.main_cuid) FROM RESERVATION WHERE RESERVATION.main_cuid = CUSTOMER.cuid GROUP BY RESERVATION.main_cuid HAVING COUNT(RESERVATION.main_cuid)>1 )"

#define parkingTODAY "RESERVATION.checkin_date <= CURDATE() AND RESERVATION.checkout_date >= CURDATE()"

namespace Commands {
    class Show
    {
    private:
        ErrorCode err;

        const char* const showReservationsSQL = "SELECT * FROM RESERVATION JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s;";
        const char* const showCustomersSQL = "SELECT * FROM CUSTOMER WHERE %s;";
        const char* const showPaymentsSQL = "SELECT PAYMENT.*, CUSTOMER.first_name, CUSTOMER.middle_name, CUSTOMER.last_name, CUSTOMER.cuid FROM PAYMENT JOIN RESERVATION ON PAYMENT.ruid = RESERVATION.ruid JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s;";
        const char* const showServicesSQL = "SELECT RESERVATION.ruid, SERVICE.* FROM SERVICE JOIN INCLUDED_SERVICE ON SERVICE.name = INCLUDED_SERVICE.service_name JOIN RESERVATION ON RESERVATION.ruid = INCLUDED_SERVICE.ruid WHERE %s;";
        const char* const showParkingSQL = "SELECT RESERVED_PARKING.*, RESERVATION.checkin_date, RESERVATION.checkout_date, CUSTOMER.* FROM PARKING_SPOT JOIN RESERVED_PARKING ON PARKING_SPOT.letter = RESERVED_PARKING.pletter AND PARKING_SPOT.number = RESERVED_PARKING.pnumber JOIN RESERVATION ON RESERVATION.ruid = RESERVED_PARKING.ruid JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s;";

        ErrorCode reservations(const int argc, const char* const argv[]);
        ErrorCode customers(const int argc, const char* const argv[]);
        ErrorCode payments(const int argc, const char* const argv[]);
        ErrorCode services(const int argc, const char* const argv[]);
        ErrorCode parking(const int argc, const char* const argv[]);
    public:
        Show(const int argc, const char* const argv[]);
        ~Show();
    };
    
}