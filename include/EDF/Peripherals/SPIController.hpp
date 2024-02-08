/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <cstdint>

namespace EDF {

class SPIController {
public:
    virtual ~SPIController() = default;
    virtual void select() = 0;
    virtual void deselect() = 0;
    virtual uint8_t transfer( uint8_t data ) = 0;
    virtual void transfer( uint8_t* dataInOut, std::size_t n ) = 0;
};

} /* EDF */