cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(../pico-sdk/pico_sdk_init.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_SYSTEM_NAME  Generic)
#set(CMAKE_SYSTEM_PROCESSOR ARM)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(ThermalCamera C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

include_directories(ThermalCamera "include")

add_executable(ThermalCamera src/main.cpp)

# MLX90640 api
add_subdirectory("../" mlx90640api)
target_link_libraries(ThermalCamera mlx90640-RPI-Pico)

target_link_libraries(ThermalCamera pico_stdlib hardware_i2c)

pico_enable_stdio_usb(ThermalCamera 1)
pico_enable_stdio_uart(ThermalCamera 0)

pico_add_extra_outputs(ThermalCamera)