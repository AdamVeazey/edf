/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/MCU/ST/STM32C011F6/I2CController.hpp"
#include "EDF/Assert.hpp"


I2CControllerFast::Response I2CControllerFast::
toResponse( HAL_StatusTypeDef status, uint32_t i2cError ) {
    switch( status ) {
    case HAL_BUSY:      return Response::ErrorBusy;
    case HAL_TIMEOUT:   return Response::ErrorTimeout;
    case HAL_OK:
    default:
        break;
    }
    switch( i2cError ) {
    case HAL_I2C_ERROR_NONE:    return Response::ACK;
    case HAL_I2C_ERROR_AF:      return Response::NACK;
    case HAL_I2C_ERROR_BERR:    return Response::ErrorBus;
    case HAL_I2C_ERROR_ARLO:    return Response::ErrorArbLost;
    case HAL_I2C_ERROR_OVR:     return Response::ErrorOverrun;
    default:
        break;
    }
    return Response::Error;
}

I2CControllerFast::Response I2CControllerFast::
transfer(
    uint8_t address_7bit,
    const uint8_t* txData, std::size_t txLen,
    uint8_t* rxData, std::size_t rxLen
) const {
    auto ret = HAL_I2C_Master_Transmit(
        i2c,
        static_cast<uint8_t>(address_7bit << 1),
        const_cast<uint8_t*>(txData), txLen,
        timeout_ticks
    );
    Response response = toResponse( ret, i2c->ErrorCode );
    if( (response != Response::ACK) && (response != Response::NACK) ) {
        // some kind of error occurred. Don't bother attempting to read data
        return response;
    }
    if( (rxData != nullptr) && (rxLen != 0) ) {
        ret = HAL_I2C_Master_Receive(
            i2c,
            static_cast<uint8_t>(address_7bit << 1),
            rxData, rxLen,
            timeout_ticks
        );
        response = toResponse( ret, i2c->ErrorCode );
    }
    return response;
}