#pragma once

#include <errors.hpp>
#include <Commands/Create.hpp>

#define getLastIDQuery "SELECT LAST_INSERT_ID();"

ErrorCode createReservationEntry(Commands::ReservationData *rd, int defaultCost, int *cuids, int *ruid);
ErrorCode createContainedCustomer(Commands::ReservationData *rd, int *cuids, int ruid);
ErrorCode createReservedSpot(Commands::ReservationData *rd, int suid, int ruid);
ErrorCode createReservedParking(int actualParkingSpots, Commands::PARKING_SPOT *spots, int ruid);