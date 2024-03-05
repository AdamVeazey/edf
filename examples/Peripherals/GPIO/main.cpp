/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Peripherals/GPIO.hpp>

#include <iostream>

// tag::mock_gpio[]
/* Simulate a GPIO memory mapped peripheral, here is just a single "register" */
struct MCU_GPIO_T {
    volatile uint32_t DATA_REGISTER;
};

/* For this example, we need a real instance of the fake memory mapped peripheral */
static MCU_GPIO_T MCU_GPIO_PORTA;

/* Normally the definition is a hardcoded address that comes from the datasheet */
#define GPIO_PORTA (&MCU_GPIO_PORTA)

class GPIO final : public EDF::GPIO {
public:
    using Level = EDF::GPIO::Level;
private:
    MCU_GPIO_T* port;
    uint32_t pin;
public:
    GPIO( MCU_GPIO_T* port, uint32_t pin ) : port(port), pin(1 << pin) {}
    virtual ~GPIO() = default;

    /* Initialization functions for the specific  */
    void configureAsInput() {}
    void configureAsOutput() {}

    virtual Level getLevel() const override {
        return static_cast<Level>((port->DATA_REGISTER & pin) != 0);
    }
    virtual void set( Level level ) const override {
        if( level == Level::HIGH ) {
            port->DATA_REGISTER |= pin;
        }
        else {
            port->DATA_REGISTER &= ~pin;
        }
    }
};
// end::mock_gpio[]

int main() {
    using namespace std;

    // tag::init[]
    GPIO pin( GPIO_PORTA, 5 );
    // end::init[]

    // tag::get_level[]
    if( pin.getLevel() == GPIO::Level::LOW ) {
        // ...
    }
    // end::get_level[]

    // tag::is_low[]
    if( pin.isLow() ) {
        // ...
    }
    // end::is_low[]

    // tag::is_high[]
    if( pin.isHigh() ) {
        // ...
    }
    // end::is_high[]

    // tag::set[]
    pin.set( GPIO::Level::LOW );
    // end::set[]

    // tag::toggle[]
    pin.toggle();
    // end::toggle[]

    // tag::set_low[]
    pin.setLow();
    // end::set_low[]

    // tag::set_high[]
    pin.setHigh();
    // end::set_high[]

    for( int k = 0; k < 5; ++k ) {
        cout << "level: " << (pin.isHigh() ? "High" : "Low") << endl;
        pin.toggle();
    }

    return 0;
}