/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <cstdint>

namespace EDF {

class PWM {
public:
    virtual ~PWM() = default;

    virtual void setPeriod_MHz( std::uint32_t MHz ) = 0;
    virtual std::uint32_t getPeriod_MHz() const = 0;

    virtual void setPeriod_kHz( std::uint32_t kHz ) = 0;
    virtual std::uint32_t getPeriod_kHz() const = 0;

    virtual void setPeriod_Hz( std::uint32_t Hz ) = 0;
    virtual std::uint32_t getPeriod_Hz() const = 0;

    virtual void setPeriod_ticks( std::uint32_t ticks ) = 0;
    virtual std::uint32_t getPeriod_ticks() const = 0;

    virtual void setDutyCyclePercent( std::uint8_t percent ) = 0;
    virtual std::uint8_t getDutyCyclePercent() const = 0;

    virtual void setDutyCycleTicks( std::uint32_t ticks ) = 0;
    virtual std::uint32_t getDutyCycleTicks() const = 0;
};

} /* EDF */