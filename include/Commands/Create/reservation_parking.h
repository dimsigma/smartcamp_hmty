#pragma once

#include <errors.hpp>
#include <Commands/Create.hpp>

ErrorCode getAvailParking(Commands::ReservationData *rd, Commands::PARKING_SPOT *spots, const char* const tmpl, int *actualParking);