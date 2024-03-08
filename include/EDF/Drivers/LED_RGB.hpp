/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/PWM.hpp"
#include "EDF/Color.hpp"

namespace EDF {

class LED_RGB {
private:
    PWM& red;
    PWM& green;
    PWM& blue;
public:
    LED_RGB( PWM& red, PWM& green, PWM& blue ) :
        red(red), green(green), blue(blue)
    {}
    void setColor( const Color& c );
    Color getColor() const;
    inline void off() { setColor( Color::black() ); };
};

} /* EDF */