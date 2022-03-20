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

#include <stdio.h>

#include <iostream>

#include "MLX90640_I2C_Driver.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

int init = 0;

void MLX90640_I2CInit() {
}

int MLX90640_I2CRead(uint8_t slaveAddr, uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data) {
    if (!init) {
        i2c_init(i2c_default, 100 * 1000);
        gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
        // Make the I2C pins available to picotool
        bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
        init = 1;
    }

    uint8_t buf[1664];
    uint8_t cmd[2] = {0, 0};

    cmd[0] = startAddress >> 8;
    cmd[1] = startAddress & 0x00FF;

    uint16_t *p = data;

    i2c_write_blocking(i2c_default, slaveAddr, cmd, 2, 1);
    i2c_read_blocking(i2c_default, slaveAddr, buf, 2*nMemAddressRead, 0);

    for (int count = 0; count < nMemAddressRead; count++) {
        int i = count << 1;
        *p++ = ((uint16_t)buf[i] << 8) | buf[i + 1];
    }
    return 0;
}

void MLX90640_I2CFreqSet(int freq) {
}

int MLX90640_I2CWrite(uint8_t slaveAddr, uint16_t writeAddress, uint16_t data) {
    uint8_t cmd[4] = {0, 0, 0, 0};

    cmd[0] = writeAddress >> 8;
    cmd[1] = writeAddress & 0x00FF;
    cmd[2] = data >> 8;
    cmd[3] = data & 0x00FF;

    i2c_write_blocking(i2c_default, slaveAddr, cmd, 4, 0);
    return 0;
}
