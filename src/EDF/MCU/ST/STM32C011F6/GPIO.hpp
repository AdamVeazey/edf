/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/GPIO.hpp"

#include "stm32c0xx_hal.h"

class GPIOFast {
public:
    using Level = EDF::GPIO::Level;
    enum class Interrupt {
        RISING_EDGE         = GPIO_MODE_IT_RISING,
        FALLING_EDGE        = GPIO_MODE_IT_FALLING,
        ALL_EDGES           = GPIO_MODE_IT_RISING_FALLING,
    };
    enum class Event { // Capture input pin events via EXTI, but don't generate an interrupt
        RISING_EDGE         = GPIO_MODE_EVT_RISING,
        FALLING_EDGE        = GPIO_MODE_EVT_FALLING,
        ALL_EDGES           = GPIO_MODE_EVT_RISING_FALLING,
    };
    enum class OutputMode {
        OUTPUT_PP           = GPIO_MODE_OUTPUT_PP,
        OUTPUT_OD           = GPIO_MODE_OUTPUT_OD,
    };
    enum class Pull {
        NOPULL              = GPIO_NOPULL,
        PULLUP              = GPIO_PULLUP,
        PULLDOWN            = GPIO_PULLDOWN,
    };
    enum class Speed {
        FREQ_LOW            = GPIO_SPEED_FREQ_LOW,
        FREQ_MEDIUM         = GPIO_SPEED_FREQ_MEDIUM,
        FREQ_HIGH           = GPIO_SPEED_FREQ_HIGH,
        FREQ_VERY_HIGH      = GPIO_SPEED_FREQ_VERY_HIGH,
    };
private:
    GPIO_TypeDef* port;
    uint16_t pin;
public:
    GPIOFast( GPIO_TypeDef* port, uint16_t pin ) : port(port), pin(pin) {}
    ~GPIOFast() = default;

    /* Configuration */
    void configureAsInput( Pull pull = Pull::NOPULL );
    void configureAsInputInterrupt(
        Interrupt interruptMode,
        Pull pull = Pull::NOPULL
    );
    void configureAsInputEvent(
        Event eventMode,
        Pull pull = Pull::NOPULL
    );
    void configureAsOutput(
        Level initialLevel,
        OutputMode outputMode = OutputMode::OUTPUT_PP,
        Pull pull = Pull::NOPULL,
        Speed speed = Speed::FREQ_LOW
    );
    void lockConfiguration();
    void deinit();

    /* Input member functions */
    Level getLevel()            const;
    inline bool isLow()         const { return getLevel() == Level::LOW; }
    inline bool isHigh()        const { return getLevel() == Level::HIGH; }

    /* Output member functions */
    void set( Level level )     const;
    void toggle()               const;
    inline void setLow()        const { set( Level::LOW ); }
    inline void setHigh()       const { set( Level::HIGH ); }
};

class GPIO : public GPIOFast, public EDF::GPIO {
public:
    using Level         = EDF::GPIO::Level;
    using Interrupt     = GPIOFast::Interrupt;
    using Event         = GPIOFast::Event;
    using OutputMode    = GPIOFast::OutputMode;
    using Pull          = GPIOFast::Pull;
    using Speed         = GPIOFast::Speed;
public:
    GPIO( GPIO_TypeDef* port, uint16_t pin ) : GPIOFast(port, pin) {}
    virtual ~GPIO() = default;

    /* Input member functions */
    virtual Level getLevel()        const { return GPIOFast::getLevel(); }
    inline bool isLow()             const { return GPIOFast::isLow(); }
    inline bool isHigh()            const { return GPIOFast::isHigh(); }

    /* Output member functions */
    virtual void set( Level level ) const { GPIOFast::set( level ); }
    virtual void toggle()           const { GPIOFast::toggle(); }
    inline void setLow()            const { GPIOFast::setLow(); }
    inline void setHigh()           const { GPIOFast::setHigh(); }
};