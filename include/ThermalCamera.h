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

#include "MLX90640_API.h"

#define MLX_I2C_ADDR 0x33

// the default shift for a MLX90640 device in open air
#define TA_SHIFT 8

class ThermalCamera {
private:
    uint16_t eeMLX90640[832];
    const float emissivity = 0.98;
    paramsMLX90640 mlx90640;
public:
    ThermalCamera() {
        MLX90640_SetDeviceMode(MLX_I2C_ADDR, 0);
        MLX90640_SetSubPageRepeat(MLX_I2C_ADDR, 0);

        MLX90640_SetRefreshRate(MLX_I2C_ADDR, 0b100);

        MLX90640_SetChessMode(MLX_I2C_ADDR);

        MLX90640_DumpEE(MLX_I2C_ADDR, eeMLX90640);
        MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
    }

    void capture(float* captureData) {
        uint16_t frame[834];
        float eTa;

        MLX90640_GetFrameData(MLX_I2C_ADDR, frame);
        eTa = MLX90640_GetTa(frame, &mlx90640)-TA_SHIFT;

        MLX90640_GetSubPageNumber(frame);
        MLX90640_CalculateTo(frame, &mlx90640, emissivity, eTa, captureData);

        MLX90640_BadPixelsCorrection((&mlx90640)->brokenPixels, captureData, 1, &mlx90640);
        MLX90640_BadPixelsCorrection((&mlx90640)->outlierPixels, captureData, 1, &mlx90640);
    }

    float getMaxTemp(float data[], int data_len) {
        float currentMax = data[0];
        for (int i = 0; i<data_len; i++) {
            if (data[i] > currentMax) {
                currentMax = data[i];
            }
        }
        return currentMax;
    }
};