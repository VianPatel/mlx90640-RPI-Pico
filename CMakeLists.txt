cmake_minimum_required(VERSION 3.13)

include(pico-sdk/pico_sdk_init.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(mlx90640-RPI-Pico src/MLX90640_API.cpp src/MLX90640_PICO_I2C_Driver.cpp)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

target_include_directories(mlx90640-RPI-Pico PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(mlx90640-RPI-Pico pico_stdlib hardware_i2c)