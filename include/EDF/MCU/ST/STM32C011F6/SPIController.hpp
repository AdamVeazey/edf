/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/SPIController.hpp"
#include "EDF/MCU/ST/STM32C011F6/GPIO.hpp"

class SPIControllerFast {
public:
    using Response = EDF::SPIController::Response;
    using ResponseData = EDF::SPIController::ResponseData;
private:
    SPI_HandleTypeDef* spi;
    GPIOFast* cs;
    uint32_t timeout_ticks;
public:
    SPIControllerFast(
        SPI_HandleTypeDef* spi,
        GPIOFast* chipSelect = nullptr
    ) : spi(spi), cs(chipSelect), timeout_ticks(0) {}
    ~SPIControllerFast() = default;
    inline void setTimeout( uint32_t ticks ) { timeout_ticks = ticks; }
    void select();
    void deselect();
    ResponseData transfer( uint8_t dataInOut );
    Response transfer( uint8_t* dataInOut, std::size_t n );
};

class SPIController : public SPIControllerFast, public EDF::SPIController {
public:
    using Response = EDF::SPIController::Response;
    using ResponseData = EDF::SPIController::ResponseData;
public:
    SPIController(
        SPI_HandleTypeDef* spi,
        GPIOFast* chipSelect = nullptr
    ) : SPIControllerFast(spi, chipSelect) {}
    virtual ~SPIController() = default;

    virtual void select()                                           override { SPIControllerFast::select(); }
    virtual void deselect()                                         override { SPIControllerFast::deselect(); }
    virtual ResponseData transfer( uint8_t dataInOut )              override { return SPIControllerFast::transfer( dataInOut ); }
    virtual Response transfer( uint8_t* dataInOut, std::size_t n )  override { return SPIControllerFast::transfer( dataInOut, n ); }
};