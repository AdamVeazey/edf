/*
 * Copyright (c) 2024, Adam Veazey
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

SPIControllerFast::ResponseData SPIControllerFast::
transfer( uint8_t data ) {
    return ResponseData( transfer( &data, 1 ), data );
}

SPIControllerFast::Response SPIControllerFast::
transfer( uint8_t* dataInOut, std::size_t n ) {
    auto ret = HAL_SPI_TransmitReceive(
        spi,
        dataInOut,
        dataInOut,
        n,
        timeout_ticks
    );
    switch( ret ) {
    case HAL_OK:        break;
    case HAL_BUSY:      return Response::ErrorBusy;
    case HAL_TIMEOUT:   return Response::ErrorTimeout;
    default:            break;
    }
    switch( spi->ErrorCode ) {
    case HAL_SPI_ERROR_NONE:    return Response::Ok;
    case HAL_SPI_ERROR_OVR:     return Response::ErrorOverrun;
    default:                    break;
    }
    return Response::Error;
}
