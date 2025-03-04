cmake_minimum_required(VERSION 3.30)
project(smartcamp)

set(CMAKE_CXX_STANDARD 17)

if (WIN32 AND (CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64") AND (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))
        add_compile_definitions(ARCH_AMD64)
        add_compile_definitions(OS_WINDOWS)
        set(PLATFORM "Win32")
        message(STATUS "Running on AMD64 Windows using Microsoft Visual C++")
elseif (APPLE AND (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64") AND (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
        add_compile_definitions(ARCH_ARM64)
        add_compile_definitions(OS_MACOS)
        set(PLATFORM "APPLE")
        message(STATUS "Running on ARM64 macOS using Apple Clang")
elseif ((UNIX AND NOT APPLE) AND (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
        add_compile_definitions(ARCH_AMD64)
        add_compile_definitions(OS_LINUX)
        set(PLATFORM "Linux")
        message(STATUS "Running on x86_64 Linux using GNU")
else ()
        message(FATAL_ERROR "Failed to identify system.")
endif ()

add_executable(smartcamp
        main.cpp
        src/errors.cpp
        src/Foundation/Context.cpp
        src/Foundation/db.cpp
        src/Foundation/Injector.cpp
        src/Commands/Config.cpp
        src/Commands/TestConnection.cpp
        src/Commands/Show/Show.cpp
        src/Commands/Show/reservations.cpp
        src/Commands/Show/customers.cpp
        src/Commands/Show/payments.cpp
        src/Commands/Show/services.cpp
        src/Commands/Show/parking.cpp
        src/Commands/Show/accommodation.cpp
        src/Commands/Show/spot_class.cpp
        src/Commands/Show/spot_class_count.cpp
        src/Commands/Create/Create.cpp
        src/Commands/Create/reservation.cpp
        src/Commands/Create/reservation_customer.cpp
        src/Commands/Create/reservation_accommodation.cpp
        src/Commands/Create/reservation_parking.cpp
        src/Commands/Create/reservation_creator.cpp
        src/Commands/Create/service.cpp
        src/Commands/Create/payment.cpp
        src/Commands/Describe/Describe.cpp
        src/Commands/Describe/customer.cpp
        src/Commands/Describe/reservation.cpp
        src/Commands/Describe/accomodation.cpp
        src/Commands/Update/Update.cpp
        src/Commands/Update/customer.cpp
        src/Commands/Update/reservation_cost.cpp
        src/Commands/Update/reservation_services.cpp
        src/Commands/Update/reservation_parking.cpp
        src/Commands/Update/reservation_accomodation.cpp
        src/Commands/Delete/Delete.cpp
        src/Commands/Delete/reservation.cpp
        src/Commands/Delete/customer.cpp
        src/Commands/Delete/service.cpp
        src/Commands/Stats/Stats.cpp
        src/Commands/Stats/occupancy.cpp
        src/Commands/Stats/earnings.cpp
        src/Commands/Stats/accomodation.cpp
)

if (NOT PLATFORM STREQUAL "Linux")

        target_include_directories(smartcamp PRIVATE
                "./external/mysqlclient/${PLATFORM}/include"
        )

        target_link_directories(smartcamp PRIVATE
                "./external/mysqlclient/${PLATFORM}/lib"
        )
else ()

        message(STATUS "Incude directory ${MYSQL_CLIENT_LIB_INCLUDE_DIR}")
        message(STATUS "Link directory ${MYSQL_CLIENT_LIB_LIB_DIR}")

        if (NOT DEFINED MYSQL_CLIENT_LIB_INCLUDE_DIR OR NOT DEFINED MYSQL_CLIENT_LIB_LIB_DIR)
                message(FATAL_ERROR "MYSQL_CLIENT_LIB_INCLUDE_DIR and MYSQL_CLIENT_LIB_LIB_DIR not defined")
        endif ()

        target_include_directories(smartcamp PRIVATE
        "${MYSQL_CLIENT_LIB_INCLUDE_DIR}"
        )

        target_link_directories(smartcamp PRIVATE
        "${MYSQL_CLIENT_LIB_LIB_DIR}"
        )
endif()

target_include_directories(smartcamp PRIVATE
        #"./external/tomlplusplus/include"
        "./include"
)

target_link_libraries(smartcamp PRIVATE
        mysqlclient
)
