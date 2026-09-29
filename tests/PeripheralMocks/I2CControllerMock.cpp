/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "I2CControllerMock.hpp"
#include "EDF/Math.hpp"

void I2CControllerMock::MockResponse::
copyDataOut( uint8_t* data, std::size_t expectedLen ) {
    std::copy(
        dataOut.begin(),
        dataOut.begin() + EDF::min(expectedLen, dataOut.size()),
        data
    );
}

I2CControllerMock::Response I2CControllerMock::
transfer(
    uint8_t address_7bit,
    const uint8_t* txData, std::size_t txLen,
    uint8_t* rxData, std::size_t rxLen
) {
    if( responses.empty() ) {
        return Response::Error;
    }
    auto data = responses.front();
    responses.pop();
    data.copyDataOut( rxData, rxLen );
    return data.getResponse();
}