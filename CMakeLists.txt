cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)

project(v5_sim_pros)
add_library(v5_sim_pros SHARED simulator/src/v5_stubs.c
        simulator/src/emu_core.c
        simulator/src/emu_devices.c
        simulator/src/emu_motors.c)

target_include_directories(v5_sim_pros PUBLIC simulator/include)