/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Peripherals/GPIO.hpp>

#include <iostream>

// ---------------------------------------------------------------------------
// --------------------- Buildable Documentation Snippts ---------------------
// ---------------------------------------------------------------------------

// tag::mock_gpio[]
/* Simulate a GPIO memory mapped peripheral, here is just a single "register" */
struct MCU_GPIO_T {
    volatile uint32_t DATA_REGISTER;
};

/* For this example, we need a real instance of the fake memory mapped peripheral */
static MCU_GPIO_T MCU_GPIO_PORTA = { .DATA_REGISTER = 0xFFFFFFFF };

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

    /* Initialization functions for the specific MCU */
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

void docStrings() {
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
}

// ---------------------------------------------------------------------------
// --------------------------- Simple Example --------------------------------
// ---------------------------------------------------------------------------

int main() {
    GPIO led( GPIO_PORTA, 4 );
    GPIO button( GPIO_PORTA, 0 );

    led.configureAsOutput();
    button.configureAsInput();

    std::cout << "Simulating Firmware Super-Loop\n\n";

    // while( true ) in real code - 3 iterations here purely for example purposes
    for( int k = 0; k < 3; ++k ) {
        // Enable LED (LOW) if button is pressed (LOW)
        bool pressed = button.isLow();
        led.set( pressed ? GPIO::Level::LOW : GPIO::Level::HIGH );
        if( pressed ) {
            std::cout << "Button is LOW (active). LED is LOW (active).\n";
        }
        else {
            std::cout << "Button is HIGH (idle). LED is HIGH (idle).\n";
        }
        // Simulate user button state changes
        button.toggle();
    }

    std::cout << "\nSimulation completed successfully.\n";

    return 0;
}