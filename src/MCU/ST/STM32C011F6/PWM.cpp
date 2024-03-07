/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/MCU/ST/STM32C011F6/PWM.hpp"
#include "EDF/Assert.hpp"

void PWMFast::
init() {
    if( timer->State != HAL_TIM_STATE_READY ) {
        HAL_TIM_Base_Init( timer );
    }
    HAL_TIM_PWM_Start( timer, static_cast<uint32_t>(channel) );
    EDF_ASSERTD( timer->Init.AutoReloadPreload == TIM_AUTORELOAD_PRELOAD_ENABLE, "AutoReloadPreload is enabled" );
}

void PWMFast::
setPeriod_MHz( uint32_t MHz ) {
    setPeriod_kHz( MHz * 1000 );
}

uint32_t PWMFast::
getPeriod_MHz() const {
    return getPeriod_kHz() / 1000;
}

void PWMFast::
setPeriod_kHz( uint32_t kHz ) {
    setPeriod_Hz( kHz * 1000 );
}

uint32_t PWMFast::
getPeriod_kHz() const {
    return getPeriod_Hz() / 1000;
}

void PWMFast::
setPeriod_Hz( uint32_t Hz ) {
    EDF_ASSERTD(Hz < HAL_RCC_GetSysClockFreq(), "Target Hz is less than internal clock frequency");
    const uint32_t sysFreq = HAL_RCC_GetSysClockFreq();
    uint32_t prescaler = 0;
    uint32_t period = sysFreq / Hz;
    for (uint32_t candidatePrescaler = 1; candidatePrescaler <= 0xFFFF; ++candidatePrescaler) {
        uint32_t candidatePeriod = period / candidatePrescaler;
        if ((candidatePeriod >= 100) && (candidatePeriod <= 0xFFFF)) {
            prescaler = candidatePrescaler - 1;
            period = candidatePeriod - 1;
            break;
        }
    }
    EDF_ASSERTD(prescaler <= 0xFFFF, "Prescaler is not a valid value. Try a different frequency");
    EDF_ASSERTD((period >= 100) && (period <= 0xFFFF), "Period is not a valid value. Try a different frequency");
    timer->Instance->ARR = period; // auto reload register
    timer->Instance->PSC = prescaler; // prescaler register
}

uint32_t PWMFast::
getPeriod_Hz() const {
    // Assume clock source is Internal for this chip.
    return HAL_RCC_GetSysClockFreq() / timer->Instance->PSC;
}

void PWMFast::
setPeriod_ticks( uint32_t ticks ) {
    EDF_ASSERTD(ticks <= 0xFFFF, "Ticks is a 16-bit value");
    // auto reload register
    timer->Instance->ARR = static_cast<uint16_t>(ticks);
}

uint32_t PWMFast::
getPeriod_ticks() const {
    return static_cast<uint32_t>(timer->Instance->ARR);
}


void PWMFast::
setDutyCyclePercent( uint8_t percent ) {
    setDutyCycleTicks( (getPeriod_ticks() * percent) / 100 );
}

uint8_t PWMFast::
getDutyCyclePercent() const {
    return static_cast<uint8_t>((getDutyCycleTicks() * 100) / getPeriod_ticks());
}

void PWMFast::
setDutyCycleTicks( uint32_t ticks ) {
    switch( channel ) {
    case Channel::CH_1: timer->Instance->CCR1 = static_cast<uint16_t>(ticks);   break;
    case Channel::CH_2: timer->Instance->CCR2 = static_cast<uint16_t>(ticks);   break;
    case Channel::CH_3: timer->Instance->CCR3 = static_cast<uint16_t>(ticks);   break;
    case Channel::CH_4: timer->Instance->CCR4 = static_cast<uint16_t>(ticks);   break;
    case Channel::CH_5: timer->Instance->CCR5 = static_cast<uint16_t>(ticks);   break;
    case Channel::CH_6: timer->Instance->CCR6 = static_cast<uint16_t>(ticks);   break;
    default:            EDF_ASSERTD(!"channel not valid", "Channel is valid");  break;
    }
}

uint32_t PWMFast::
getDutyCycleTicks() const {
    switch( channel ) {
    case Channel::CH_1: return static_cast<uint32_t>(timer->Instance->CCR1);
    case Channel::CH_2: return static_cast<uint32_t>(timer->Instance->CCR2);
    case Channel::CH_3: return static_cast<uint32_t>(timer->Instance->CCR3);
    case Channel::CH_4: return static_cast<uint32_t>(timer->Instance->CCR4);
    case Channel::CH_5: return static_cast<uint32_t>(timer->Instance->CCR5);
    case Channel::CH_6: return static_cast<uint32_t>(timer->Instance->CCR6);
    default:            EDF_ASSERTD(!"channel not valid", "Channel is valid");  return 0;
    }
}