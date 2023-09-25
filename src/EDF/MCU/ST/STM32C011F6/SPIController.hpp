/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/SPIController.hpp"
#include "EDF/MCU/ST/STM32C011F6/GPIO.hpp"

class SPIControllerFast {
private:
    SPI_HandleTypeDef* spi;
    GPIOFast* cs;
public:
    SPIControllerFast(
        SPI_HandleTypeDef* spi,
        GPIOFast* chipSelect = nullptr
    ) : spi(spi), cs(chipSelect) {}
    ~SPIControllerFast() = default;
    void select();
    void deselect();
    uint8_t transfer( uint8_t data );
    void transfer( uint8_t* dataInOut, std::size_t n );
};

class SPIController : public SPIControllerFast, public EDF::SPIController {
public:
    SPIController(
        SPI_HandleTypeDef* spi,
        GPIOFast* chipSelect = nullptr
    ) : SPIControllerFast(spi, chipSelect) {}
    virtual ~SPIController() = default;

    virtual void select()                                       override { SPIControllerFast::select(); }
    virtual void deselect()                                     override { SPIControllerFast::deselect(); }
    virtual uint8_t transfer( uint8_t data )                    override { return SPIControllerFast::transfer( data ); }
    virtual void transfer( uint8_t* dataInOut, std::size_t n )  override { SPIControllerFast::transfer( dataInOut, n ); }
};