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
public:
    using Response = EDF::I2CController::Response;
private:
    I2C_HandleTypeDef* i2c;
    std::uint32_t timeout_ticks;
private:
    static Response toResponse( HAL_StatusTypeDef status, std::uint32_t i2cError );
public:
    I2CControllerFast( I2C_HandleTypeDef* i2c ) :
        i2c(i2c), timeout_ticks(HAL_MAX_DELAY)
    {}
    inline void setTimeout( std::uint32_t ticks ) { timeout_ticks = ticks; }
    Response transfer(
        std::uint8_t address_7bit,
        const std::uint8_t* txData = nullptr, std::size_t txLen = 0,
        std::uint8_t* rxData = nullptr, std::size_t rxLen = 0
    ) const;
};

class I2CController : public I2CControllerFast, public EDF::I2CController {
public:
    using Response = EDF::I2CController::Response;
public:
    I2CController( I2C_HandleTypeDef* i2c ) :
        I2CControllerFast(i2c)
    {}
    virtual ~I2CController() = default;
    virtual Response transfer(
        std::uint8_t address_7bit,
        const std::uint8_t* txData = nullptr, std::size_t txLen = 0,
        std::uint8_t* rxData = nullptr, std::size_t rxLen = 0
    ) override {
        return I2CControllerFast::transfer(
            address_7bit,
            txData, txLen,
            rxData, rxLen
        );
    }
};