#pragma once

#include <errors.hpp>

namespace Commands {
    class Stats
    {
    private:
        ErrorCode err;

        // stats occupancy <startdate> <enddate>
        const char* const Occupancy = "SELECT SUM(IF(res.checkin_date >= '%s', IF(res.checkout_date < '%s', DATEDIFF(res.checkout_date, res.checkin_date), DATEDIFF('%s', res.checkin_date)), DATEDIFF(res.checkout_date, '%s'))) / ((SELECT COUNT(*) FROM ACCOMODATION_SPOT) * DATEDIFF('%s', '%s'))  AS occupancy "
        "FROM RESERVATION AS res JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "WHERE res.checkin_date <= '%s' AND res.checkout_date > '%s';";

        // stats earnings <startdate> <enddate>
        const char* const Earnings = "SELECT SUM(total_cost) AS total_earnings FROM RESERVATION "
        "WHERE checkin_date >= '%s' AND checkin_date <= '%s';";

        // stats earnings --permonth <year>
        const char* const EarningsMonth = "SELECT MONTH(checkin_date) AS month, SUM(total_cost) AS total_earnings FROM RESERVATION "
        "WHERE YEAR(checkin_date) = '%s' "
        "GROUP BY MONTH(checkin_date);";

        // stats accomodation <startdate> <enddate>
        const char* const Accomodation = "SELECT res_s.suid AS spot, SUM(DATEDIFF(IF(res.checkout_date > '%s', '%s', res.checkout_date), IF(res.checkin_date < '%s', '%s', res.checkin_date))) AS total_days_booked "
        "FROM RESERVATION AS res JOIN RESERVED_SPOT AS res_s ON res.ruid = res_s.ruid "
        "WHERE res.checkin_date <= '%s' AND res.checkin_date > '%s' "
        "GROUP BY res_s.suid ORDER BY res_s.suid ASC;";

        ErrorCode occupancy(const int argc, const char* const argv[]);
        ErrorCode earnings(const int argc, const char* const argv[]);
        ErrorCode accomodation(const int argc, const char* const argv[]);

    public:
        Stats(const int argc, const char* const argv[]);
        ~Stats();
    };
}