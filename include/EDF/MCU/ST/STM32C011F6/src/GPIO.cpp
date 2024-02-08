/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/MCU/ST/STM32C011F6/GPIO.hpp"

void GPIOFast::
configureAsInput( Pull pull ) {
    GPIO_InitTypeDef init;
    init.Pin = pin;
    init.Mode = GPIO_MODE_INPUT;
    init.Pull = static_cast<uint32_t>(pull);
    HAL_GPIO_Init( port, &init );
}

void GPIOFast::
configureAsInputInterrupt( Interrupt interruptMode, Pull pull ) {
    GPIO_InitTypeDef init;
    init.Pin = pin;
    init.Mode = static_cast<uint32_t>(interruptMode);
    init.Pull = static_cast<uint32_t>(pull);
    HAL_GPIO_Init( port, &init );
}

void GPIOFast::
configureAsInputEvent( Event eventMode, Pull pull ) {
    GPIO_InitTypeDef init;
    init.Pin = pin;
    init.Mode = static_cast<uint32_t>(eventMode);
    init.Pull = static_cast<uint32_t>(pull);
    HAL_GPIO_Init( port, &init );
}

void GPIOFast::
configureAsOutput(
    Level initialLevel,
    OutputMode outputMode,
    Pull pull,
    Speed speed
) {
    set( initialLevel );
    GPIO_InitTypeDef init;
    init.Pin = pin;
    init.Mode = static_cast<uint32_t>(outputMode);
    init.Pull = static_cast<uint32_t>(pull);
    init.Speed = static_cast<uint32_t>(speed);
    HAL_GPIO_Init( port, &init );
}

void GPIOFast::
lockConfiguration() {
    HAL_GPIO_LockPin( port, pin );
}

void GPIOFast::
deinit() {
    HAL_GPIO_DeInit( port, pin );
}

GPIOFast::Level GPIOFast::
getLevel() const {
    // EDF::GPIO::Level enumeration maps perfectly to GPIO_PinState
    return static_cast<Level>(HAL_GPIO_ReadPin( port, pin ));
}

void GPIOFast::
set( Level level ) const {
    // EDF::GPIO::Level enumeration maps perfectly to GPIO_PinState
    HAL_GPIO_WritePin( port, pin, static_cast<GPIO_PinState>(level) );
}

void GPIOFast::
toggle() const {
    HAL_GPIO_TogglePin( port, pin );
}