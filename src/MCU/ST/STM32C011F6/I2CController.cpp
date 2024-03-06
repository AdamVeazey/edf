/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/MCU/ST/STM32C011F6/I2CController.hpp"
#include "EDF/Assert.hpp"


void I2CControllerFast::
transfer(
    const uint8_t* txData, std::size_t txLen,
    uint8_t* rxData, std::size_t rxLen
) const {
    auto ret = HAL_I2C_Master_Transmit(
        i2c,
        addr,
        const_cast<uint8_t*>(txData), txLen,
        timeout_ticks
    );
    EDF_ASSERT( ret == HAL_OK, "Master Transmit return value is HAL_OK" );
    ret = HAL_I2C_Master_Receive(
        i2c,
        addr,
        rxData, rxLen,
        timeout_ticks
    );
    EDF_ASSERT( ret == HAL_OK, "Master Receive return value is HAL_OK" );
}