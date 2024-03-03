/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <cstdint>

namespace EDF {

class GPIO {
public:
    enum class Level : uint8_t {
        LOW,
        HIGH
    };
public:
    virtual ~GPIO() = default;

    /* Input member functions */
    virtual Level getLevel()    const = 0;
    inline bool isLow()         const { return getLevel() == Level::LOW; }
    inline bool isHigh()        const { return getLevel() == Level::HIGH; }

    /* Output member functions */
    virtual void set( Level level ) const = 0;
    virtual void toggle()       const { set( isHigh() ? Level::LOW : Level::HIGH ); }
    inline void setLow()        const { set( Level::LOW ); }
    inline void setHigh()       const { set( Level::HIGH ); }
};

} /* EDF */