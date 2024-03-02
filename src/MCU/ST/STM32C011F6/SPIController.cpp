/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/MCU/ST/STM32C011F6/SPIController.hpp"
#include "EDF/Assert.hpp"

void SPIControllerFast::
select() {
    if( cs ) {
        // CS is software controlled
        cs->setLow();
    }
    else if( !(spi->Instance->CR1 & SPI_CR1_SSM) ) {
        // CS is HW controlled, abuse NSSP to control toggling
        spi->Instance->CR2 &= ~SPI_NSS_PULSE_ENABLE; // turn OFF nssp to pull line low
    }
}

void SPIControllerFast::
deselect() {
    if( cs ) {
        // CS is software controlled
        cs->setHigh();
    }
    else if( !(spi->Instance->CR1 & SPI_CR1_SSM) ) {
        // CS is HW controlled, abuse NSSP to control toggling
        spi->Instance->CR2 |= SPI_NSS_PULSE_ENABLE;
    }
}

uint8_t SPIControllerFast::
transfer( uint8_t data ) {
    transfer( &data, 1 );
    return data;
}

void SPIControllerFast::
transfer( uint8_t* dataInOut, std::size_t n ) {
    auto ret = HAL_SPI_TransmitReceive(
        spi,
        dataInOut,
        dataInOut,
        n,
        HAL_MAX_DELAY
    );
    EDF_ASSERTD( ret == HAL_StatusTypeDef::HAL_OK );
}
