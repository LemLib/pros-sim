cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)

project(v5_Sim)
add_library(v5_Sim SHARED simulator/src/v5_stubs.c
        simulator/src/emu_core.c
        simulator/src/emu_devices.c
        simulator/src/emu_motors.c)
target_include_directories(v5_Sim PUBLIC simulator/include)

project(Example)
add_executable(Example example/src/main.cpp
        simulator/include/emu_devices.h)
target_link_libraries(Example v5_Sim)
target_include_directories(Example PUBLIC simulator/include)
target_include_directories(Example PUBLIC example/include)