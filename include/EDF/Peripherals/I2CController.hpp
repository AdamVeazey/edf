/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <cstdint>

namespace EDF {

class I2CController {
public:
    enum class Response{
        ACK,
        NACK,
        ErrorBusy,
        ErrorBus, /* Misplaced start/stop detected */
        ErrorArbLost, /* Arbitration lost. Another master took bus */
        ErrorOverrun, /* Data lost */
        Error, /* Any other error */
        ErrorTimeout,
    };
public:
    virtual ~I2CController() = default;
    virtual Response transfer(
        uint8_t address_7bit,
        const uint8_t* txData = nullptr, std::size_t txLen = 0,
        uint8_t* rxData = nullptr, std::size_t rxLen = 0
    ) = 0;
};

} /* EDF */