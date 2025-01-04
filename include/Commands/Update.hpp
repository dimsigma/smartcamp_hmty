#pragma once

#include <errors.hpp>

namespace Commands {
    class Update
    {
    private:
        ErrorCode err;

        // update customer [--firstname | --lastname | --telcountry | --telnumber] <new_value> --cuid <cuid>
        const char* const ShowCustomerInfo = "SELECT cus.cuid, cus.first_name, cus.middle_name, cus.last_name, cus.tel_country, cus.tel_num "
        "FROM CUSTOMER AS cus WHERE cus.cuid = %s;";
        const char* const CustomerFirstName = "UPDATE CUSTOMER SET first_name = '%s' WHERE cuid = %s;";
        const char* const CustomerLastName = "UPDATE CUSTOMER SET last_anme = '%s' WHERE cuid = %s;";
        const char* const CustomerTelcountry = "UPDATE CUSTOMER SET tel_country = %s WHERE cuid = %s;";
        const char* const CustomerTelnumber = "UPDATE CUSTOMER SET tel_num = %s WHERE cuid = %s;";

        // update reservation cost <new_cost> --ruid <ruid>
        const char* const ShowReservationCostInfo = "SELECT res.ruid, cus.first_name, cus.last_name, res.checkin_date, res.checkout_date, res.total_cost "
        "FROM RESERVATION AS res JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid WHERE res.ruid = %s;";
        const char* const ReservationCost = "UPDATE RESERVATION SET total_cost = %s WHERE ruid = %s;";

        // update reservation services [--add | --remove] <service> --ruid <ruid>
        const char* const ShowReservationServicesInfo = "SELECT inc_ser.service_name "
        "FROM RESERVATION AS res JOIN INCLUDED_SERVICE AS inc_ser ON res.ruid = inc_ser.ruid WHERE res.ruid = %s;";
        const char* const ReservationServices_add = "INSERT INTO INCLUDED_SERVICE(service_name, ruid) VALUES ('%s', %s);";
        const char* const ReservationServices_delete = "DELETE FROM INCLUDED_SERVICE WHERE service_name = '%s' AND ruid = %s;";

        // update reservation parking [--add | --remove] <pletter> <pnumber> --ruid <ruid>
        const char* const ShowReservationParkingInfo = "SELECT res_p.pletter, res_p.pnumber "
        "FROM RESERVATION AS res JOIN RESERVED_PARKING AS res_p ON res.ruid = res_p.ruid WHERE res.ruid = %s;";
        const char* const ReservationParking_add = "INSERT INTO RESERVED_PARKING(ruid, pletter, pnumber) VALUES (%s, '%s', %s);";
        const char* const ReservationParking_delete = "DELETE FROM RESERVED_PARKING WHERE ruid = %s AND pletter = '%s' AND pnumber = %s;";

        // update reservation accomodation [--add | --remove] <suid> --ruid <ruid>
        const char* const ShowReservationAccomodationInfo = "SELECT acc_s.suid, acc_s.commercial_name, acc_s.class_name, acc_s.class_type, sp_c.season, sp_c.cost "
        "FROM RESERVATION AS res JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "JOIN ACCOMODATION_SPOT AS acc_s ON res_s.suid = acc_s.suid "
        "JOIN SPOT_CLASS AS sp_c ON (acc_s.class_name = sp_c.class_name AND acc_s.class_type = sp_c.class_type) "
        "WHERE res.ruid = %s AND sp_c.season = IF(MONTH(res.checkin_date) < %s OR MONTH(res.checkin_date) > %s, '%s', '%s');";
        const char* const ReservationAccomodation_add = "INSERT INTO RESERVED_SPOT(ruid, suid) VALUES (%s, %s);";
        const char* const ReservationAccomodation_delete = "DELETE FROM RESERVED_SPOT WHERE ruid = %s AND suid = %s;";

        ErrorCode customer(const int argc, const char* const argv[]);
        ErrorCode customerShow(const int argc, const char* const argv[]);

        ErrorCode reservationCost(const int argc, const char* const argv[]);
        ErrorCode reservationCostShow(const int argc, const char* const argv[]);

        ErrorCode reservationServices(const int argc, const char* const argv[]);
        ErrorCode reservationServicesShow(const int argc, const char* const argv[]);

        ErrorCode reservationParking(const int argc, const char* const argv[]);
        ErrorCode reservationParkingShow(const int argc, const char* const argv[]);

        ErrorCode reservationAccomodation(const int argc, const char* const argv[]);
        ErrorCode reservationAccomodationShow(const int argc, const char* const argv[]);
    
    public:
        Update(const int argc, const char* const argv[]);
        ~Update();
    };
}