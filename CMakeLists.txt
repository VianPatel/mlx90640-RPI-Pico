cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(FaceTemp C CXX ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)


# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

include_directories(mlx90640-RPI-Pico "include")

add_executable(mlx90640-RPI-Pico src/main.cpp src/MLX90640_API.cpp src/MLX90640_PICO_I2C_Driver.cpp)

target_link_libraries(mlx90640-RPI-Pico pico_stdlib hardware_i2c)

pico_add_extra_outputs(mlx90640-RPI-Pico)

pico_enable_stdio_usb(mlx90640-RPI-Pico 1)
pico_enable_stdio_uart(mlx90640-RPI-Pico 0)
