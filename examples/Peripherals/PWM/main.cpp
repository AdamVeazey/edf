/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Peripherals/PWM.hpp>

#include <iostream>

// tag::mock_pwm[]
/* Simulate a Timer memory mapped peripheral, here is just a couple "registers" */
struct MCU_TIMER_T {
    volatile uint32_t AUTO_RELOAD;
    volatile uint32_t MATCH_CH0;
};

/* For this example, we need a real instance of the fake memory mapped peripheral */
static MCU_TIMER_T MCU_TIMER0;

/* Normally the definition is a hardcoded address that comes from the datasheet */
#define TIMER0 (&MCU_TIMER0)

class PWM final : public EDF::PWM {
private:
    MCU_TIMER_T* timer;
    uint32_t channel;
public:
    PWM( MCU_TIMER_T* timer, uint32_t channel ) : timer(timer), channel(channel) {}
    virtual ~PWM() = default;

    virtual void setPeriod_MHz( uint32_t MHz )                { setPeriod_kHz( MHz * 1000 ); }
    virtual uint32_t getPeriod_MHz()                    const { return getPeriod_kHz() / 1000; }

    virtual void setPeriod_kHz( uint32_t kHz )                { setPeriod_Hz( kHz * 1000 ); }
    virtual uint32_t getPeriod_kHz()                    const { return getPeriod_Hz() / 1000; }

    virtual void setPeriod_Hz( uint32_t Hz )                  { timer->AUTO_RELOAD = Hz; /* actually do math */  }
    virtual uint32_t getPeriod_Hz()                     const { return /* sysclk */48000000; }

    virtual void setPeriod_ticks( uint32_t ticks )            { timer->AUTO_RELOAD = ticks; }
    virtual uint32_t getPeriod_ticks()                  const { return timer->AUTO_RELOAD; }

    virtual void setDutyCyclePercent( uint8_t percent )       { setDutyCycleTicks( (getPeriod_ticks() * percent) / 100 ); }
    virtual uint8_t getDutyCyclePercent()               const { return static_cast<uint8_t>((getDutyCycleTicks() * 100) / getPeriod_ticks()); }

    virtual void setDutyCycleTicks( uint32_t ticks )          { if( channel == 0 ) timer->MATCH_CH0 = ticks; /* etc..*/ }
    virtual uint32_t getDutyCycleTicks()                const { return (channel == 0) ? timer->MATCH_CH0 : 0; /* etc..*/ }
};
// end::mock_pwm[]

int main() {
    using namespace std;

    // tag::init[]
    PWM pwm( TIMER0, 0 );
    // end::init[]

    // tag::pwm_set_period_mhz[]
    pwm.setPeriod_MHz( 5 );
    // end::pwm_set_period_mhz[]

    // tag::pwm_get_period_mhz[]
    uint32_t MHz = pwm.getPeriod_MHz();
    // end::pwm_get_period_mhz[]
    (void)MHz;

    // tag::pwm_set_period_khz[]
    pwm.setPeriod_kHz( 100 );
    // end::pwm_set_period_khz[]

    // tag::pwm_get_period_khz[]
    uint32_t kHz = pwm.getPeriod_kHz();
    // end::pwm_get_period_khz[]
    (void)kHz;

    // tag::pwm_set_period_hz[]
    pwm.setPeriod_Hz( 960 );
    // end::pwm_set_period_hz[]

    // tag::pwm_get_period_hz[]
    uint32_t hz = pwm.getPeriod_Hz();
    // end::pwm_get_period_hz[]
    (void)hz;

    // tag::pwm_set_duty_cycle_percent[]
    pwm.setDutyCyclePercent( 50 );
    // end::pwm_set_duty_cycle_percent[]

    // tag::pwm_get_duty_cycle_percent[]
    uint8_t dutyCyclePercent = pwm.getDutyCyclePercent();
    // end::pwm_get_duty_cycle_percent[]
    (void)dutyCyclePercent;

    // tag::pwm_set_duty_cycle_ticks[]
    pwm.setDutyCycleTicks( 960 / 2 );
    // end::pwm_set_duty_cycle_ticks[]

    // tag::pwm_get_duty_cycle_ticks[]
    uint32_t dutyCycleTicks = pwm.getDutyCycleTicks();
    // end::pwm_get_duty_cycle_ticks[]
    (void)dutyCycleTicks;

    return 0;
}