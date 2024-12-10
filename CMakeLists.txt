cmake_minimum_required(VERSION 3.30)
project(smartcamp)

set(CMAKE_CXX_STANDARD 11)

add_executable(smartcamp
        main.cpp
)

target_include_directories(smartcamp PRIVATE
        ".\\external\\mysqlclient\\include"
	    #"C:\\msys64\\mingw64\\include"
)

target_link_directories(smartcamp PRIVATE
        ".\\external\\mysqlclient\\lib"
	    #"C:\\msys64\\mingw64\\lib"
)

target_link_libraries(smartcamp PRIVATE
        mysqlclient
)