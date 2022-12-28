/**
 * @copyright (C) 2021 Vian Patel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdint.h>
#include <cstdio>
#include <string>

#include <MLX90640_API.h>
#include <pico/stdlib.h>

#include "ThermalCamera.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define NONE "\x1b[30m"
#define RESET "\x1b[0m"

//#define FMT_STRING "%+06.2f "
#define FMT_STRING "\u2588\u2588"

void printFrame(ThermalCamera::Frame& frame);
float toFahrenheit(float celcius);

int main() {
    stdio_init_all();
    ThermalCamera::Camera camera;
    ThermalCamera::Frame frame;

    while (true) {
        camera.capture(frame);
        printFrame(frame);
        printf(("Max temp (fahrenheit): " + std::to_string(toFahrenheit(frame.getMaxTemp()))).c_str());
        printf("\x1b[33A");
    }
    return 0;
}

void printFrame(ThermalCamera::Frame& frame) {
    for (int x = 0; x < frame.getWidth(); x++) {
        for (int y = 0; y < frame.getHeight(); y++) {
            //std::cout << image[32 * y + x] << ",";
            float temp = frame.getTemp(x, y);
            if (temp > 34.5) {
                printf(MAGENTA FMT_STRING RESET, temp);
            } else if (temp > 29.0) {
                printf(RED FMT_STRING RESET, temp);
            } else if (temp > 26.0) {
                printf(YELLOW FMT_STRING YELLOW, temp);
            } else if (temp > 20.0) {
                printf(NONE FMT_STRING RESET, temp);
            } else if (temp > 17.0) {
                printf(GREEN FMT_STRING RESET, temp);
            } else if (temp > 10.0) {
                printf(CYAN FMT_STRING RESET, temp);
            } else {
                printf(BLUE FMT_STRING RESET, temp);
            }
        }
        printf("\n");
    }
}

float toFahrenheit(float celcius) {
    return celcius * 1.8 + 32;
}