cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 23)

project(v5_Sim)
add_library(v5_Sim SHARED simulator/src/init.cpp)
target_include_directories(v5_Sim PUBLIC simulator/include)

project(Example)
add_executable(Example example/src/main.cpp)
target_link_libraries(Example v5_Sim)
target_include_directories(Example PUBLIC simulator/include)
target_include_directories(Example PUBLIC example/include)