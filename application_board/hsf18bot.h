/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef RUUVITAG_B_H
#define RUUVITAG_B_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> // Required by boards.h
#include <stdint.h>  // Required by boards.h
#include "nrf_peripherals.h" // GPIO definitions

// LEDs definitions for RuuviTag B
#define LEDS_NUMBER    0

#define LEDS_ACTIVE_STATE 0

#define LEDS_INV_MASK  LEDS_MASK

#define LEDS_LIST {}

#define DISTANCE_LEFT 17
#define DISTANCE_RIGHT 19

#define MOTOR_RIGHT_FORWARD  30
#define MOTOR_RIGHT_BACKWARD 31
#define MOTOR_LEFT_FORWARD   4
#define MOTOR_LEFT_BACKWARD  5

#define BUTTONS_NUMBER 0

#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { }

#define RX_PIN_NUMBER   4
#define TX_PIN_NUMBER   5
#define RTS_PIN_NUMBER  NRF_GPIO_UNUSED
#define CTS_PIN_NUMBER  NRF_GPIO_UNUSED
#define HWFC            false

#define BOARD_SPI_INSTANCE  0
#define BOARD_SPI_FREQUENCY RUUVI_SPI_FREQ_8M  // Use 1 MHz if connecting logic analyzer, 8 MHz otherwise
//#define BOARD_SPI_FREQUENCY RUUVI_SPI_FREQ_1M  // Use 1 MHz if connecting logic analyzer, 8 MHz otherwise
//#define BOARD_SPI_FREQUENCY RUUVI_SPI_FREQ_0M25  // Use 1 MHz if connecting logic analyzer, 8 MHz otherwise
#define SPIM0_SCK_PIN   29    // SPI clock GPIO pin number.
#define SPIM0_MOSI_PIN  25    // SPI Master Out Slave In GPIO pin number.
#define SPIM0_MISO_PIN  28    // SPI Master In Slave Out GPIO pin number.
#define SPIM0_SS_ACCELERATION_PIN   8  // SPI Slave Select (accelerometer)
#define SPIM0_SS_ENVIRONMENTAL_PIN  3  // SPI Slave Select (BME280)
#define SPI_SS_LIST {SPIM0_SS_ACCELERATION_PIN, SPIM0_SS_ENVIRONMENTAL_PIN}

#define INT_ACC1_PIN       2  // Accelerometer interrupt 1
#define INT_ACC2_PIN       6  // Accelerometer interrupt 2

#define LIS2DH12_ACCELERATION 1
#define BME280_ENVIRONMENTAL 1

#define DEVICE_MANUFACTURER "Ojousima Hacks"
#define DEVICE_NAME "HSF "                                   /**< Name of device. Will be included in the advertising data. */
#define DEVICE_MODEL "Bot 18"
#define DEVICE_HWREV "01"


#define REVERSE_PROT_VOLT_DROP_MV 1 //!< Typical forward voltage drop of the mosfet

// Low frequency clock source to be used by the SoftDevice
#define NRF_CLOCK_LFCLKSRC      {.source       = NRF_CLOCK_LF_SRC_XTAL,      \
                                 .rc_ctiv      = 0,                          \
                                 .rc_temp_ctiv = 0,                          \
                                 .accuracy     = NRF_CLOCK_LF_ACCURACY_20_PPM}

#ifdef __cplusplus
}
#endif

#endif // PCA10040_H
