#pragma once

#include <errors.hpp>

namespace Commands {

    typedef struct {
        const char* checkinData;
        const char* checkoutData;
        int people;
        int spots;
        int parking;
    } ReservationData;

    typedef struct {
        char* letters;
        int number;
    } PARKING_SPOT;

    class Create
    {
    private:
        ErrorCode err;

        const char* const neighbouringAccomodation = "WITH A AS (SELECT ACCOMODATION_SPOT.*, SPOT_CLASS.cost, DATEDIFF('%s', '%s') * SPOT_CLASS.cost AS cost_per_spot FROM ACCOMODATION_SPOT JOIN SPOT_CLASS ON ACCOMODATION_SPOT.class_name = SPOT_CLASS.class_name AND ACCOMODATION_SPOT.class_type = SPOT_CLASS.class_type AND ((SPOT_CLASS.start_date <= CURDATE() AND SPOT_CLASS.end_date >= CURDATE()) OR (SPOT_CLASS.start_date > SPOT_CLASS.end_date AND (CURDATE() >= SPOT_CLASS.start_date OR CURDATE() <= SPOT_CLASS.end_date))) NATURAL LEFT OUTER JOIN RESERVED_SPOT NATURAL LEFT OUTER JOIN RESERVATION WHERE NOT ((RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkout_date <= '%s') OR (RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s')) OR RESERVATION.ruid IS NULL), B AS (SELECT suid, suid - ROW_NUMBER() OVER (ORDER BY suid) AS group_id FROM A ), C AS (SELECT group_id, COUNT(*) AS group_size, MIN(suid) AS start_suid, MAX(suid) AS end_suid FROM B GROUP BY group_id HAVING COUNT(*) >= %d) SELECT DISTINCT B.group_id, A.class_name, A.class_type, A.cost, A.cost_per_spot, C.group_size, C.start_suid, C.end_suid FROM A JOIN B ON A.suid = B.suid JOIN C ON B.group_id = C.group_id WHERE C.group_size >= %d ORDER BY B.group_id;";
        const char* const availableParking = "SELECT PARKING_SPOT.letter, PARKING_SPOT.number FROM PARKING_SPOT WHERE (PARKING_SPOT.letter, PARKING_SPOT.number) NOT IN (SELECT PARKING_SPOT.letter, PARKING_SPOT.number FROM PARKING_SPOT JOIN RESERVED_PARKING ON PARKING_SPOT.letter = RESERVED_PARKING.pletter AND PARKING_SPOT.number = RESERVED_PARKING.pnumber JOIN RESERVATION ON RESERVATION.ruid = RESERVED_PARKING.ruid WHERE (RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkout_date <= '%s') OR (RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date <= '%s' AND RESERVATION.checkout_date >= '%s') OR (RESERVATION.checkin_date >= '%s' AND RESERVATION.checkin_date <= '%s' AND RESERVATION.checkout_date >= '%s')) LIMIT %d;";

        ErrorCode reservation(const int argc, const char* const argv[]);
        ErrorCode payment(const int argc, const char* const argv[]);
    public:
        Create(const int argc, const char* const argv[]);
        ~Create();
    };
    
}