#pragma once

#include <errors.hpp>
#include <Commands/Create.hpp>

ErrorCode getAccommodationGroupId(Commands::ReservationData *rd, const char* const tmpl, int *suid, int *defaultCost);