cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)

project(v5_sim_pros)
add_library(v5_sim_pros STATIC simulator/src/v5_stubs.c
        simulator/src/emu_core.c
        simulator/src/devices/emu_devices.c
        simulator/src/devices/emu_motors.c
        pros/src/devices/battery.c
        pros/src/devices/battery.cpp
        pros/src/devices/controller.c
        pros/src/devices/controller.cpp
        pros/src/devices/registry.c
        pros/src/devices/screen.c
        pros/src/devices/screen.cpp
        pros/src/devices/vdml.c
        pros/src/devices/vdml_adi.c
        pros/src/devices/vdml_adi.cpp
        pros/src/devices/vdml_device.c
        pros/src/devices/vdml_device.cpp
        pros/src/devices/vdml_distance.c
        pros/src/devices/vdml_distance.cpp
        pros/src/devices/vdml_ext_adi.c
        pros/src/devices/vdml_gps.c
        pros/src/devices/vdml_gps.cpp
        pros/src/devices/vdml_imu.c
        pros/src/devices/vdml_imu.cpp
        pros/src/devices/vdml_link.c
        pros/src/devices/vdml_link.cpp
        pros/src/devices/vdml_motorgroup.cpp
        pros/src/devices/vdml_motors.c
        pros/src/devices/vdml_motors.cpp
        pros/src/devices/vdml_optical.c
        pros/src/devices/vdml_optical.cpp
        pros/src/devices/vdml_rotation.c
        pros/src/devices/vdml_rotation.cpp
        pros/src/devices/vdml_serial.c
        pros/src/devices/vdml_serial.cpp
        pros/src/devices/vdml_usd.c
        pros/src/devices/vdml_usd.cpp
        pros/src/devices/vdml_vision.c
        pros/src/devices/vdml_vision.cpp
        pros/include/pros/abstract_motor.hpp
        pros/include/pros/adi.h
        pros/include/pros/adi.hpp
        pros/include/pros/apix.h
        pros/include/pros/colors.h
        pros/include/pros/colors.hpp
        pros/include/pros/device.h
        pros/include/pros/device.hpp
        pros/include/pros/distance.h
        pros/include/pros/distance.hpp
        pros/include/pros/error.h
        pros/include/pros/ext_adi.h
        pros/include/pros/gps.h
        pros/include/pros/gps.hpp
        pros/include/pros/imu.h
        pros/include/pros/imu.hpp
        pros/include/pros/link.h
        pros/include/pros/link.hpp
        pros/include/pros/llemu.h
        pros/include/pros/llemu.hpp
        pros/include/pros/misc.h
        pros/include/pros/misc.hpp
        pros/include/pros/motor_group.hpp
        pros/include/pros/motors.h
        pros/include/pros/motors.hpp
        pros/include/pros/optical.h
        pros/include/pros/optical.hpp
        pros/include/pros/rotation.h
        pros/include/pros/rotation.hpp
        pros/include/pros/rtos.h
        pros/include/pros/rtos.hpp
        pros/include/pros/screen.h
        pros/include/pros/screen.hpp
        pros/include/pros/serial.h
        pros/include/pros/serial.hpp
        pros/include/pros/vision.h
        pros/include/pros/vision.hpp
        pros/include/vdml/port.h
        pros/include/vdml/registry.h
        pros/include/vdml/vdml.h
        pros/include/api.h
        pros/include/kapi.h
        pros/src/system/startup.c
        pros/src/system/system_daemon.c
        pros/src/common/gid.c
        pros/src/common/linkedlist.c
        pros/src/common/set.c
        pros/src/common/string.c
        pros/include/common/cobs.h
        pros/include/common/gid.h
        pros/include/common/linkedlist.h
        pros/include/common/set.h
        pros/include/common/string.h
        pros/include/system/dev/banners.h
        simulator/src/emu_rtos.c
        simulator/src/emu_rtos_cpp.cpp
        simulator/include/emu_rtos.h
        simulator/src/emu_display.c
        pros/include/system/startup.h)

target_include_directories(v5_sim_pros PUBLIC simulator/include)
target_include_directories(v5_sim_pros PUBLIC pros/include)
target_include_directories(v5_sim_pros PUBLIC user/include)

project(v5_sim_user)
add_library(v5_sim_user SHARED user/src/main.cpp
        user/include/api.h user/include/main.h)
target_include_directories(v5_sim_user PUBLIC user/include)
target_include_directories(v5_sim_user PUBLIC user/pros/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
add_link_options(v5_sim_user -fPIC)
target_link_libraries(v5_sim_user PUBLIC v5_sim_pros SDL2 SDL2_gfx SDL2_FontCache)