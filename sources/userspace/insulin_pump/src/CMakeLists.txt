cmake_minimum_required(VERSION 3.14)
project(Emulated_IP)

# Přesuňte include_directories na začátek souboru
include_directories( "C:/Users/rosaj/source/repos/KIV-RTOS/sources/stdlib/include/")
include_directories( "C:/Users/rosaj/source/repos/KIV-RTOS/sources/kernel/include/")
include_directories( "C:/Users/rosaj/source/repos/KIV-RTOS/sources/stdutils/include/")
include_directories( "C:/Users/rosaj/source/repos/KIV-RTOS/sources/kernel/include/board/rpi0/")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

ADD_DEFINITIONS(-DRPI0)

add_executable(Emulated_IP 
    src/main.cpp 
    src/insulin_pump/pid_regulator/pid_regulator.cpp
    src/insulin_pump/basal/basal_profile.cpp
    src/math/math.cpp
    src/utils/logger/logger.cpp
)

target_include_directories(Emulated_IP PUBLIC ${CMAKE_SOURCE_DIR}/include)
