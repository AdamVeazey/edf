/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/Drivers/LED_RGB.hpp"

namespace EDF {

void LED_RGB::
setColor( const Color& c ) {
    red.setDutyCyclePercent( (c.r() * 100) / 255 );
    green.setDutyCyclePercent( (c.g() * 100) / 255 );
    blue.setDutyCyclePercent( (c.b() * 100) / 255 );
}

Color LED_RGB::
getColor() const {
    return Color(
        (red.getDutyCyclePercent() * 255) / 100,
        (green.getDutyCyclePercent() * 255) / 100,
        (blue.getDutyCyclePercent() * 255) / 100
    );
}

} /* EDF */