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
    virtual ~I2CController() = default;
    virtual void setAddress( uint8_t address_7bit ) = 0;
    virtual void transfer(
        const uint8_t* txData, std::size_t txLen,
        uint8_t* rxData, std::size_t rxLen
    ) = 0;
};

} /* EDF */