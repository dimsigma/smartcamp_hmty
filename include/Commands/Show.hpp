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

        const char* const showReservationsSQL = "SELECT * FROM RESERVATION JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s ORDER BY RESERVATION.checkin_date DESC;";
        const char* const showCustomersSQL = "SELECT CUSTOMER.*, COUNT(RESERVATION.main_cuid) AS total_reservations FROM CUSTOMER JOIN RESERVATION ON CUSTOMER.cuid = RESERVATION.main_cuid WHERE %s GROUP BY RESERVATION.main_cuid;";
        const char* const showPaymentsSQL = "SELECT PAYMENT.*, CUSTOMER.first_name, CUSTOMER.middle_name, CUSTOMER.last_name, CUSTOMER.cuid FROM PAYMENT JOIN RESERVATION ON PAYMENT.ruid = RESERVATION.ruid JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s;";
        const char* const showServicesSQL = "SELECT RESERVATION.ruid, SERVICE.* FROM SERVICE JOIN INCLUDED_SERVICE ON SERVICE.name = INCLUDED_SERVICE.service_name JOIN RESERVATION ON RESERVATION.ruid = INCLUDED_SERVICE.ruid WHERE %s;";
        const char* const showParkingSQL = "SELECT RESERVED_PARKING.*, RESERVATION.checkin_date, RESERVATION.checkout_date, CUSTOMER.* FROM PARKING_SPOT JOIN RESERVED_PARKING ON PARKING_SPOT.letter = RESERVED_PARKING.pletter AND PARKING_SPOT.number = RESERVED_PARKING.pnumber JOIN RESERVATION ON RESERVATION.ruid = RESERVED_PARKING.ruid JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid WHERE %s;";
        const char* const showAllAccommodationSQL = "SELECT ACCOMODATION_SPOT.*, SPOT_CLASS.cost FROM ACCOMODATION_SPOT JOIN SPOT_CLASS ON ACCOMODATION_SPOT.class_name = SPOT_CLASS.class_name AND ACCOMODATION_SPOT.class_type = SPOT_CLASS.class_type AND ((SPOT_CLASS.start_date <= CURDATE() AND SPOT_CLASS.end_date >= CURDATE()) OR (SPOT_CLASS.start_date > SPOT_CLASS.end_date AND (CURDATE() >= SPOT_CLASS.start_date OR CURDATE() <= SPOT_CLASS.end_date))) %s WHERE %s ORDER BY ACCOMODATION_SPOT.suid";
        const char* const showAccommodationSQL = "SELECT ACCOMODATION_SPOT.*, %s RESERVATION.*, CUSTOMER.first_name, CUSTOMER.middle_name, CUSTOMER.last_name FROM RESERVATION JOIN CUSTOMER ON RESERVATION.main_cuid = CUSTOMER.cuid NATURAL JOIN RESERVED_SPOT NATURAL JOIN ACCOMODATION_SPOT JOIN SPOT_CLASS ON ACCOMODATION_SPOT.class_name = SPOT_CLASS.class_name AND ACCOMODATION_SPOT.class_type = SPOT_CLASS.class_type AND ((SPOT_CLASS.start_date <= CURDATE() AND SPOT_CLASS.end_date >= CURDATE()) OR (SPOT_CLASS.start_date > SPOT_CLASS.end_date AND (CURDATE() >= SPOT_CLASS.start_date OR CURDATE() <= SPOT_CLASS.end_date))) %s WHERE %s ORDER BY RESERVATION.checkin_date ASC;";
        const char* const showSpotClassSQL = "SELECT SPOT_CLASS.class_name, SPOT_CLASS.class_type, SPOT_CLASS.season, SPOT_CLASS.cost, SPOT_CLASS.description, SPOT_CLASS.start_date, SPOT_CLASS.end_date, COUNT(ACCOMODATION_SPOT.suid) AS all_spots FROM SPOT_CLASS NATURAL JOIN ACCOMODATION_SPOT WHERE %s GROUP BY SPOT_CLASS.class_name, SPOT_CLASS.class_type, SPOT_CLASS.season, SPOT_CLASS.cost, SPOT_CLASS.description, SPOT_CLASS.start_date, SPOT_CLASS.end_date;";
        const char* const showSpotClassCountSQL = "SELECT SPOT_CLASS.class_name, SPOT_CLASS.class_type, COUNT(ACCOMODATION_SPOT.suid) AS all_spots FROM SPOT_CLASS NATURAL JOIN ACCOMODATION_SPOT WHERE %s GROUP BY SPOT_CLASS.class_name, SPOT_CLASS.class_type;";

        ErrorCode reservations(const int argc, const char* const argv[]);
        ErrorCode customers(const int argc, const char* const argv[]);
        ErrorCode payments(const int argc, const char* const argv[]);
        ErrorCode services(const int argc, const char* const argv[]);
        ErrorCode parking(const int argc, const char* const argv[]);
        ErrorCode accommodation(const int argc, const char* const argv[]);
        ErrorCode spot_class(const int argc, const char* const argv[]);
        ErrorCode spot_class_count(const int argc, const char* const argv[]);
    public:
        Show(const int argc, const char* const argv[]);
        ~Show();
    };
    
}