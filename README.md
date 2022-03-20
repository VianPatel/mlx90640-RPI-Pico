## mlx90640 RPI Pico
This project provides a driver allowing communication between a raspberry pi pico and an mlx90640 thermal sensor.
Example code is provided allowing visualization of the thermal sensor's output via a com port.


**Prior setup:**

connect the mlx90640 camera pins as follows:

(mlx90640 pin) -> (pico pin)

sda -> gp4

scl -> gp5

gnd -> gnd

3-6v -> 3v3


**Building:**

install gcc-arm-none-eabi from:
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads
or: `sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib`


`git clone  https://github.com/VianPatel/ThermalCamera-RPI-Pico.git`

`cd ThermalCamera-RPI-Pico`

`git submodule update --init pico-sdk/`

`cd pico-sdk`

`git submodule update --init lib/tinyusb/`

`cd ../`

`mkdir build`

`cd build`

`cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH="fullPathToCompiler" -DCMAKE_CXX_COMPILER:FILEPATH="fullPathToCompiler" ..`

`cmake --build .`


**Usage:**

Copy "ThermalCamera-RPI-Pico.uf2" inside the build folder to the pico's root folder
Connect the pico's to a computer via a micro usb data cable
Establish a connection to the com port (this can be done via putty on windows)
