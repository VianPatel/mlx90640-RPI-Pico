/**
 * @copyright (C) 2022 Vian Patel
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

#pragma once

#include <stdint.h>

#include <MLX90640_API.h>

namespace ThermalCamera {

constexpr int MLX_I2C_ADDR = 0x33;

// the default shift for a MLX90640 device in open air
constexpr int TA_SHIFT = 8;

class Frame {
public:
    inline int getWidth() { return 32; }
    inline int getHeight() { return 24; }
    inline int getNumPixels() { return 768; }
    inline float getTemp(int width, int height) { return data[32 * (23 - height) + width]; }
private:
    float data[768];
    friend class Camera;
};

class Camera {
public:
    Camera() {
        MLX90640_SetDeviceMode(MLX_I2C_ADDR, 0);
        MLX90640_SetSubPageRepeat(MLX_I2C_ADDR, 0);

        MLX90640_SetRefreshRate(MLX_I2C_ADDR, 0b100);

        MLX90640_SetChessMode(MLX_I2C_ADDR);

        uint16_t eeMLX90640[832];
        MLX90640_DumpEE(MLX_I2C_ADDR, eeMLX90640);
        MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
    }
    //https://en.wikipedia.org/wiki/Emissivity#Emissivities_of_common_surfaces
    inline void setEmissivity(float emissivity) { this->emissivity = emissivity; }
    inline float getEmissivity() { return emissivity; }
    void capture(Frame& frame) {
        uint16_t captureFrame[834];
        float eTa;

        MLX90640_GetFrameData(MLX_I2C_ADDR, captureFrame);
        eTa = MLX90640_GetTa(captureFrame, &mlx90640) - TA_SHIFT;

        MLX90640_GetSubPageNumber(captureFrame);
        MLX90640_CalculateTo(captureFrame, &mlx90640, emissivity, eTa, frame.data);

        MLX90640_BadPixelsCorrection(mlx90640.brokenPixels, frame.data, 1, &mlx90640);
        MLX90640_BadPixelsCorrection(mlx90640.outlierPixels, frame.data, 1, &mlx90640);
    }
    float getMaxTemp(Frame& frame) {
        float max = frame.data[0];
        for (int i = 0; i < frame.getNumPixels(); i++) {
            if (frame.data[i] > max) {
                max = frame.data[i];
            }
        }
        return max;
    }
    float getMinTemp(Frame& frame) {
        float min = frame.data[0];
        for (int i = 0; i < frame.getNumPixels(); i++) {
            if (frame.data[i] < min) {
                min = frame.data[i];
            }
        }
        return min;
    }
private:
    float emissivity = 0.98;
    paramsMLX90640 mlx90640;
};

}; //namespace ThermalCamera