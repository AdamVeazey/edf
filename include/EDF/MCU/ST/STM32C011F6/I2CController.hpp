/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/I2CController.hpp"

#include "stm32c0xx_hal.h"

class I2CControllerFast {
private:
    I2C_HandleTypeDef* i2c;
    uint32_t timeout_ticks;
    uint8_t addr;
public:
    I2CControllerFast( I2C_HandleTypeDef* i2c, uint8_t addr_7bit ) :
        i2c(i2c), timeout_ticks(HAL_MAX_DELAY), addr(addr_7bit)
    {}
    inline void setTimeout( uint32_t ticks ) { timeout_ticks = ticks; }
    inline void setAddr_7bit( uint8_t addr_7bit ) { addr = addr_7bit << 1; }
    void transfer(
        const uint8_t* txData, std::size_t txLen,
        uint8_t* rxData, std::size_t rxLen
    ) const;
};

class I2CController : public I2CControllerFast, public EDF::I2CController {
public:
    I2CController( I2C_HandleTypeDef* i2c, uint8_t addr_7bit ) :
        I2CControllerFast(i2c, addr_7bit)
    {}
    virtual ~I2CController() = default;
    virtual void setAddress( uint8_t address_7bit ) override {
        I2CControllerFast::setAddr_7bit(address_7bit);
    }
    virtual void transfer(
        const uint8_t* txData, std::size_t txLen,
        uint8_t* rxData, std::size_t rxLen
    ) override {
        I2CControllerFast::transfer( txData, txLen, rxData, rxLen );
    }
};