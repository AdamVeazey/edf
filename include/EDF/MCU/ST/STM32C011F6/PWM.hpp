/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/PWM.hpp"

#include "stm32c0xx_hal.h"

class PWMFast {
public:
    enum class Channel {
        CH_1 = TIM_CHANNEL_1,
        CH_2 = TIM_CHANNEL_2,
        CH_3 = TIM_CHANNEL_3,
        CH_4 = TIM_CHANNEL_4,
        CH_5 = TIM_CHANNEL_5,
        CH_6 = TIM_CHANNEL_6,
    };
private:
    TIM_HandleTypeDef* timer;
    Channel channel;
public:
    PWMFast( TIM_HandleTypeDef* timer, Channel channel ) :
        timer(timer), channel(channel)
    {}
    void init();

    void setPeriod_MHz( std::uint32_t MHz );
    std::uint32_t getPeriod_MHz() const;

    void setPeriod_kHz( std::uint32_t kHz );
    std::uint32_t getPeriod_kHz() const;

    void setPeriod_Hz( std::uint32_t Hz );
    std::uint32_t getPeriod_Hz() const;

    void setPeriod_ticks( std::uint32_t ticks );
    std::uint32_t getPeriod_ticks() const;

    void setDutyCyclePercent( std::uint8_t percent );
    std::uint8_t getDutyCyclePercent() const;

    void setDutyCycleTicks( std::uint32_t ticks );
    std::uint32_t getDutyCycleTicks() const;
};

class PWM : public PWMFast, public EDF::PWM {
public:
    PWM( TIM_HandleTypeDef* timer, Channel channel ) :
        PWMFast(timer, channel)
    {}
    virtual ~PWM() = default;

    virtual void setPeriod_MHz( std::uint32_t MHz )                { PWMFast::setPeriod_MHz( MHz ); }
    virtual std::uint32_t getPeriod_MHz()                    const { return PWMFast::getPeriod_MHz(); }

    virtual void setPeriod_kHz( std::uint32_t kHz )                { PWMFast::setPeriod_kHz( kHz ); }
    virtual std::uint32_t getPeriod_kHz()                    const { return PWMFast::getPeriod_kHz(); }

    virtual void setPeriod_Hz( std::uint32_t Hz )                  { PWMFast::setPeriod_Hz( Hz ); }
    virtual std::uint32_t getPeriod_Hz()                     const { return PWMFast::getPeriod_Hz(); }

    virtual void setPeriod_ticks( std::uint32_t ticks )            { PWMFast::setPeriod_ticks( ticks ); }
    virtual std::uint32_t getPeriod_ticks()                  const { return PWMFast::getPeriod_ticks(); }

    virtual void setDutyCyclePercent( std::uint8_t percent )       { PWMFast::setDutyCyclePercent( percent ); }
    virtual std::uint8_t getDutyCyclePercent()               const { return PWMFast::getDutyCyclePercent(); }

    virtual void setDutyCycleTicks( std::uint32_t ticks )          { PWMFast::setDutyCycleTicks( ticks ); }
    virtual std::uint32_t getDutyCycleTicks()                const { return PWMFast::getDutyCycleTicks(); }
};