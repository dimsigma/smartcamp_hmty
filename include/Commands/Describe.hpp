#pragma once

#include <errors.hpp>

namespace Commands {
    class Describe
    {
    private:
        ErrorCode err;

        // describe customer --bycuid <cuid>
        const char* const CustomerGeneral_bycuid = "SELECT cus.cuid, cus.first_name, cus.middle_name, cus.last_name, cus.tel_country, cus.tel_num "
        "FROM CUSTOMER AS cus "
        "WHERE cus.cuid = %s;";
        const char* const CustomerReservation_bycuid = "SELECT res.ruid, res.checkin_date, res.checkout_date, res.total_cost "
        "FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid "
        "WHERE cus.cuid = %s;";

        // describe customer --byname <first_name> <last_name>
        const char* const CustomerGeneral_byname = "SELECT cus.cuid, cus.first_name, cus.middle_name, cus.last_name, cus.tel_country, cus.tel_num "
        "FROM CUSTOMER AS cus "
        "WHERE cus.first_name = '%s' AND cus.last_name = '%s';";
        const char* const CustomerReservation_byname = "SELECT cus.cuid, res.ruid, res.checkin_date, res.checkout_date, res.total_cost "
        "FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid "
        "WHERE cus.first_name = '%s' AND cus.last_name = '%s';";

        // describe customer --byruid <ruid>
        const char* const CustomerGeneral_byruid = "SELECT cus.cuid, cus.first_name, cus.middle_name, cus.last_name, cus.tel_country, cus.tel_num "
        "FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid "
        "WHERE res.ruid = %s;";
        const char* const CustomerReservation_byruid = "SELECT res.ruid, res.checkin_date, res.checkout_date, res.total_cost "
        "FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid "
        "WHERE cus.cuid IN (SELECT cus.cuid FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid WHERE res.ruid = %s);";

        // describe customer --bysuid <suid>
        const char* const CustomerGeneral_bysuid = "SELECT cus.cuid, cus.first_name, cus.middle_name, cus.last_name, cus.tel_country, cus.tel_num "
        "FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid "
        "JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "WHERE res_s.suid = %s AND res.checkin_date <= GETDATE() AND res.checkout_date > GETDATE();";
        const char* const CustomerReservation_bysuid = "SELECT res.ruid, res.checkin_date, res.checkout_date, res.total_cost "
        "FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid "
        "WHERE cus.cuid IN (SELECT cus.cuid FROM CUSTOMER AS cus JOIN RESERVATION AS res ON cus.cuid = res.main_cuid "
        "JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid WHERE res_s.suid = %s AND res.checkin_date <= GETDATE() AND res.checkout_date > GETDATE());";

        // describe reservation --byruid <ruid>
        const char* const ReservationGeneral_byruid = "SELECT res.ruid, cus.first_name, cus.last_name, res.checkin_date, res.checkout_date, res.total_cost "
        "FROM RESERVATION AS res JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid "
        "WHERE res.ruid = %s;";
        const char* const ReservationAccomodation_byruid = "SELECT acc_s.suid, acc_s.commercial_name, acc_s.class_name, acc_s.class_type, sp_c.season, sp_c.cost "
        "FROM RESERVATION AS res JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "JOIN ACCOMODATION_SPOT AS acc_s ON res_s.suid = acc_s.suid "
        "JOIN SPOT_CLASS AS sp_c ON (acc_s.class_name = sp_c.class_name AND acc_s.class_type = sp_c.class_type) "
        "WHERE res.ruid = %s;";
        const char* const ReservationServices_byruid = "SELECT inc_ser.name "
        "FROM RESERVATION AS res JOIN INCLUDED_SERVICE AS inc_ser ON res.ruid = inc_ser.ruid "
        "WHERE res.ruid = %s;";
        const char* const ReservationParking_byruid = "SELECT res_p.pletter, res_p.pnumber "
        "FROM RESERVATION AS res JOIN RESERVED_PARKING AS res_p ON res.ruid = res_p.ruid "
        "WHERE res.ruid = %s;";
        const char* const ReservationPayment_byruid = "SELECT pay.puid, pay.method, pay.amount, pay.date "
        "FROM RESERVATION AS res JOIN PAYMENT AS pay ON res.ruid = pay.ruid "
        "WHERE res.ruid = %s "
        "ORDER BY pay.date DESC;";

        // describe reservation --bysuid <suid>
        const char* const ReservationGeneral_bysuid = "SELECT res.ruid, cus.first_name, cus.last_name, res.checkin_date, res.checkout_date, res.total_cost "
        "FROM RESERVATION AS res JOIN CUSTOMER AS cus ON res.main_cuid = cus.cuid "
        "JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "WHERE res_s.suid = %s AND res.checkin_date <= GETDATE() AND res.checkout_date > GETDATE();";
        const char* const ReservationAccomodation_bysuid = "SELECT acc_s.suid, acc_s.commercial_name, acc_s.class_name, acc_s.class_type, sp_c.season, sp_c.cost "
        "FROM RESERVATION AS res JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "JOIN ACCOMODATION_SPOT AS acc_s ON res_s.suid = acc_s.suid "
        "JOIN SPOT_CLASS AS sp_c ON (acc_s.class_name = sp_c.class_name AND acc_s.class_type = sp_c.class_type) "
        "WHERE res_s.suid = %s AND res.checkin_date <= GETDATE() AND res.checkout_date > GETDATE();";
        const char* const ReservationServices_bysuid = "SELECT inc_ser.service_name "
        "FROM RESERVATION AS res JOIN INCLUDED_SERVICE AS inc_ser ON res.ruid = inc_ser.ruid "
        "JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "WHERE res_s.suid = %s AND res.checkin_date <= GETDATE() AND res.checkout_date > GETDATE();";
        const char* const ReservationParking_bysuid = "SELECT res_p.pletter, res_p.pnumber "
        "FROM RESERVATION AS res JOIN RESERVED_PARKING AS res_p ON res.ruid = res_p.ruid "
        "JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "WHERE res_s.suid = %s AND res.checkin_date <= GETDATE() AND res.checkout_date > GETDATE();";
        const char* const ReservationPayment_bysuid = "SELECT pay.puid, pay.method, pay.amount, pay.date "
        "FROM RESERVATION AS res JOIN PAYMENT AS pay ON res.ruid = pay.ruid "
        "JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "WHERE res_s.suid = %s AND res.checkin_date <= GETDATE() AND res.checkout_date > GETDATE() "
        "ORDER BY pay.date DESC;";

        // describe accomodation --bysuid <suid>
        const char* const AccomodationGeneral = "SELECT acc_s.suid, acc_s.commercial_name, sp_c.class_name, sp_c.class_type, sp_c.season, sp_c.cost "
        "FROM ACCOMODATION_SPOT AS acc_s JOIN SPOT_CLASS AS sp_c ON (acc_s.class_name = sp_c.class_name AND acc_s.class_type = sp_c.class_type)"
        "WHERE acc_s.suid = %s;";
        const char* const AccomodationReservation = "SELECT res.ruid, res.checkin_date, res.checkout_date, res.main_cuid "
        "FROM ACCOMODATION_SPOT AS acc_s JOIN RESERVED_SPOT AS res_s ON acc_s.suid = res_s.suid "
        "JOIN RESERVATION AS res ON res_s.ruid = res.ruid "
        "WHERE acc_s.suid = %s "
        "ORDER BY res.checkin_date DESC;";

        ErrorCode customerGeneral(const int argc, const char* const argv[]);
        ErrorCode customerReservation(const int argc, const char* const argv[]);
        ErrorCode reservationGeneral(const int argc, const char* const argv[]);
        ErrorCode reservationAccomodation(const int argc, const char* const argv[]);
        ErrorCode reservationServices(const int argc, const char* const argv[]);
        ErrorCode reservationParking(const int argc, const char* const argv[]);
        ErrorCode reservationPayment(const int argc, const char* const argv[]);
        ErrorCode accomodationGeneral(const int argc, const char* const argv[]);
        ErrorCode accomodationReservation(const int argc, const char* const argv[]);

    public:
        Describe(const int argc, const char* const argv[]);
        ~Describe();
    };
}