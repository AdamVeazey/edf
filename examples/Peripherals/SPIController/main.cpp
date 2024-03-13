/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Peripherals/SPIController.hpp>
#include <EDF/Peripherals/GPIO.hpp>
#include <EDF/Math.hpp>

struct MCU_GPIO_T {
    volatile uint32_t DATA_REGISTER;
};
static MCU_GPIO_T MCU_GPIO_PORTA;
#define GPIO_PORTA  (&MCU_GPIO_PORTA)

// in this example were going to manually control CS via GPIO
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

// tag::mock_spi_controller[]
/* Simulate a SPI memory mapped peripheral, here is just a single "register" */
struct MCU_SPI_T {
    volatile uint32_t DATA_REGISTER;
};

/* For this example, we need a real instance of the fake memory mapped peripheral */
static MCU_SPI_T MCU_SPI0;

/* Normally the definition is a hardcoded address that comes from the datasheet */
#define SPI0        (&MCU_SPI0)

extern "C"{
int HAL_SPI_TransmitReceive( MCU_SPI_T* hspi, uint8_t* txData, uint8_t* rxData, uint16_t size, uint32_t timeout ) {
    (void)hspi;
    (void)txData;
    (void)rxData;
    (void)size;
    (void)timeout;
    return 0; // OK
}
}

class SPIController final : public EDF::SPIController {
private:
    MCU_SPI_T* spi;
    GPIO& cs;
public:
    SPIController( MCU_SPI_T* spi, GPIO& cs ) : spi(spi), cs(cs) {}
    virtual ~SPIController() = default;

    virtual void select() override {
        cs.setLow();
    }
    virtual void deselect() override {
        cs.setHigh();
    }
    virtual ResponseData transfer( uint8_t data ) override {
        return ResponseData( transfer( &data, 1 ), data );
    }
    virtual Response transfer( uint8_t* dataInOut, std::size_t n ) override {
        auto ret = HAL_SPI_TransmitReceive(
            spi,
            dataInOut,
            dataInOut,
            static_cast<uint16_t>(n),
            0
        );
        (void)ret;
        /* Do error handling */
        return Response::Ok;
    }
};
// end::mock_spi_controller[]

int main() {
    using namespace std;

    // tag::init[]
    GPIO chipSelect( GPIO_PORTA, 5 );
    SPIController spi0( SPI0, chipSelect );
    // end::init[]

    // tag::init_chip_2[]
    GPIO chipSelect_chip2( GPIO_PORTA, 8 );
    SPIController spi0_chip2( SPI0, chipSelect_chip2 );
    // end::init_chip_2[]

    // tag::spi_select[]
    spi0.select();
    // end::spi_select[]

    // tag::spi_deselect[]
    spi0.deselect();
    // end::spi_deselect[]

    // tag::spi_types[]
    using Response = EDF::SPIController::Response;
    using ResponseData = EDF::SPIController::ResponseData;
    // end::spi_types[]

    // tag::spi_transfer_byte_1[]
    Response resp = spi0.transfer( 0x5A );
    // end::spi_transfer_byte_1[]
    (void)resp;

    // tag::spi_transfer_byte_2[]
    ResponseData rd = spi0.transfer( 0x55 );
    if( rd == Response::Ok ) {
        uint8_t value = rd.data();
        (void)value; // do something with valid data
    }
    // end::spi_transfer_byte_2[]

    // tag::spi_transfer_byte_3[]
    ResponseData r = spi0.transfer( 0xAA );
    switch( r ) {
    case Response::Ok:           r.data();  break;
    case Response::ErrorBusy:               break;
    case Response::ErrorOverrun:            break;
    case Response::Error:                   break;
    case Response::ErrorTimeout:            break;
    default:                                break;
    }
    // end::spi_transfer_byte_3[]

    // tag::spi_transfer_byte_array[]
    uint8_t data[] = { 1, 2, 3, 4 };
    Response response = spi0.transfer( data, EDF::nElements(data) );
    // end::spi_transfer_byte_array[]
    (void)response;

    return 0;
}