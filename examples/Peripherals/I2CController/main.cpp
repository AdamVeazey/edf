/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Peripherals/I2CController.hpp>
#include <EDF/Assert.hpp>
#include <EDF/Math.hpp>
#include <iostream>

// tag::mock_i2c_controller[]
/* Simulate a GPIO memory mapped peripheral, here is just a single "register" */
struct MCU_I2C_T {

};

/* For this example, we need a real instance of the fake memory mapped peripheral */
static MCU_I2C_T MCU_I2C0;

/* Normally the definition is a hardcoded address that comes from the datasheet */
#define I2C0 (&MCU_I2C0)

extern "C"{
int HAL_I2C_Master_Transmit( MCU_I2C_T* hi2c, uint8_t address, uint8_t* txData, size_t txLen, uint32_t timeout ) {
    /* Vendor provided code here ... */
    (void)hi2c;
    (void)address;
    (void)txData;
    (void)txLen;
    (void)timeout;
    return 0; // OK, possibly HAL_OK
}
int HAL_I2C_Master_Receive( MCU_I2C_T* hi2c, uint8_t address, uint8_t* rxData, size_t rxLen, uint32_t timeout ) {
    /* Vendor provided code here ... */
    (void)hi2c;
    (void)address;
    (void)rxData;
    (void)rxLen;
    (void)timeout;
    return 0; // OK, possibly HAL_OK
}
} /* extern "C" */

class I2CController final : public EDF::I2CController {
public:
    using Response = EDF::I2CController::Response;
    enum class Mode {
        Standard,
        Fast,
        FastPlus,
    };
private:
    MCU_I2C_T* i2c;
    uint32_t timeout_ticks;
public:
    I2CController( MCU_I2C_T* i2c ) :
        i2c(i2c),
        timeout_ticks(0)
    {}
    virtual ~I2CController() = default;

    /* Initialization functions for the specific I2C device */
    void init( Mode mode ) { (void)mode; /* ... */ }
    inline void setTimeout( uint32_t ticks ) { timeout_ticks = ticks; }
    virtual Response transfer(
        uint8_t address_7bit,
        const uint8_t* txData, std::size_t txLen,
        uint8_t* rxData = nullptr, std::size_t rxLen = 0
    ) override {
        /* If HAL is provided by vendor you may choose to use that here. */
        auto ret = HAL_I2C_Master_Transmit(
            i2c,
            static_cast<uint8_t>(address_7bit << 1),
            const_cast<uint8_t*>(txData), txLen,
            timeout_ticks
        );
        (void)ret; // do error handling
        if( (rxData != nullptr) && (rxLen != 0) ) {
            ret = HAL_I2C_Master_Receive(
                i2c,
                static_cast<uint8_t>(address_7bit << 1),
                rxData, rxLen,
                timeout_ticks
            );
            // do error handling again
        }
        return Response::ACK; // or NACK, or other error based on error handling
    }
    Response write8BitRegister( uint8_t address_7bit, uint8_t reg, uint8_t value ){
        uint8_t txData[2] = { reg, value };
        return transfer( address_7bit, txData, EDF::nElements(txData) );
    }
    Response read8BitRegister( uint8_t address_7bit, uint8_t& regInOut ) {
        return transfer(
            address_7bit,
            &regInOut,
            1,
            &regInOut, 1
        );
    }
    Response write16BitRegister( uint8_t address_7bit, uint16_t reg, uint16_t value ) {
        uint8_t txData[4];
        txData[0] = static_cast<uint8_t>(reg >> 8);
        txData[1] = static_cast<uint8_t>(reg >> 0);
        txData[2] = static_cast<uint8_t>(value >> 8);
        txData[3] = static_cast<uint8_t>(value >> 0);
        return transfer( address_7bit, txData, EDF::nElements(txData) );
    }
    Response read16BitRegister( uint8_t address_7bit, uint16_t& regInOut ) {
        uint8_t data[2];
        data[0] = static_cast<uint8_t>(regInOut >> 8);
        data[1] = static_cast<uint8_t>(regInOut >> 0);
        auto response = transfer(
            address_7bit,
            data, EDF::nElements(data),
            data, EDF::nElements(data)
        );
        regInOut = static_cast<uint16_t>(data[0] << 8);
        regInOut |= data[1];
        return response;
    }
};
// end::mock_i2c_controller[]

int main() {
    using namespace std;

    // tag::init[]
    I2CController i2c0( I2C0 );
    // end::init[]

    // tag::i2c_set_timeout[]
    i2c0.setTimeout( 0xFFFFFFFFu );
    // end::i2c_set_timeout[]

    // tag::i2c_write_8_bit_register[]
    I2CController::Response resW8 = i2c0.write8BitRegister( 0x30, 0x40, 0xAA );
    // end::i2c_write_8_bit_register[]
    (void)resW8;

    // tag::i2c_read_8_bit_register[]
    uint8_t value8Bit = 0x12;
    I2CController::Response resR8 = i2c0.read8BitRegister( 0x30, value8Bit );
    // end::i2c_read_8_bit_register[]
    (void)value8Bit;
    (void)resR8;

    // tag::i2c_write_16_bit_register[]
    I2CController::Response resW16 = i2c0.write16BitRegister( 0x30, 0x1234, 0x55AA );
    // end::i2c_write_16_bit_register[]
    (void)resW16;

    // tag::i2c_read_16_bit_register[]
    uint16_t value16Bit = 0x3456;
    I2CController::Response resR16 = i2c0.read16BitRegister( 0x30, value16Bit );
    // end::i2c_read_16_bit_register[]
    (void)value16Bit;
    (void)resR16;

    // tag::i2c_transfer[]
    uint8_t value = 0x40;
    I2CController::Response res = i2c0.transfer( 0x30, &value, 1, &value, 1 ); // same as read8BitRegister
    // end::i2c_transfer[]
    (void)value;
    (void)res;

    return 0;
}