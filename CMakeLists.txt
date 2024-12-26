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
        src/Commands/Config.cpp
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
        "./external/tomlplusplus/include"
        "./include"
)

target_link_libraries(smartcamp PRIVATE
        mysqlclient
)
