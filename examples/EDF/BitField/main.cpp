/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/BitField.hpp>

// tag::example_register_psr[]
// Cortex-M0 Program Status Register
// Composed of APSR (Application), IPSR (Interrupt), and EPSR (Execution)
class PSR : public EDF::BitField32 {
public:
    enum class InterruptExceptionNumber {
        ThreadMode  = 0,
        NMI         = 2,
        HardFault   = 3,
        PendSV      = 14,
        SysTick     = 15, // Might not be implemented
        IRQ0,  IRQ1,  IRQ2,  IRQ3,
        IRQ4,  IRQ5,  IRQ6,  IRQ7,
        IRQ8,  IRQ9,  IRQ10, IRQ11,
        IRQ12, IRQ13, IRQ14, IRQ15,
        IRQ16, IRQ17, IRQ18, IRQ19,
        IRQ20, IRQ21, IRQ22, IRQ23,
        IRQ24, IRQ25, IRQ26, IRQ27,
        IRQ28, IRQ29, IRQ30, IRQ31,
        // else Reserved
    };
    using IEN = InterruptExceptionNumber;
public:
    constexpr PSR( uint32_t initialValue = 0 ) : EDF::BitField32( initialValue ) {}

    /* IPSR bits */
    constexpr IEN getInterruptExceptionNumber()     const { return static_cast<IEN>(get( 0, 6 )); }
    constexpr IEN getIEN()                          const { return getInterruptExceptionNumber(); }
    constexpr PSR& setInterruptExceptionNumber( IEN n )   { set( 0, 6, static_cast<uint32_t>(n) ); return *this; }
    constexpr PSR& setIEN( IEN n )                        { setInterruptExceptionNumber( n ); return *this; }

    /* EPSR bits */
    constexpr bool isExecutionThumbBitSet()         const { return get( 24, 1 ); }
    constexpr bool isT()                            const { return isExecutionThumbBitSet(); }
    constexpr PSR& setExecutionThumbBit( bool v )         { set( 24, 1, v ); return *this; }
    constexpr PSR& setT( bool v )                         { setExecutionThumbBit( v ); return *this; }

    /* APSR bits */
    constexpr bool isApplicationOverflowSet()       const { return get( 28, 1 ); }
    constexpr bool isV()                            const { return isApplicationOverflowSet(); }
    constexpr PSR& setApplicationOverflow( bool v )       { set( 28, 1, v ); return *this; }
    constexpr PSR& setV( bool v )                         { setApplicationOverflow( v ); return *this; }

    constexpr bool isApplicationCarryBorrowSet()    const { return get( 29, 1 ); }
    constexpr bool isC()                            const { return isApplicationCarryBorrowSet(); }
    constexpr PSR& setApplicationCarryBorrow( bool v )    { set( 29, 1, v ); return *this; }
    constexpr PSR& setC( bool v )                         { setApplicationCarryBorrow( v ); return *this; }

    constexpr bool isApplicationZeroSet()           const { return get( 30, 1 ); }
    constexpr bool isZ()                            const { return isApplicationZeroSet(); }
    constexpr PSR& setApplicationZero( bool v )           { set( 30, 1, v ); }
    constexpr PSR& setZ( bool v )                         { setApplicationZero( v ); return *this; }

    constexpr bool isApplicationNegativeSet()       const { return get( 31, 1 ); }
    constexpr bool isN()                            const { return isApplicationNegativeSet(); }
    constexpr PSR& setApplicationNegative( bool v )       { set( 31, 1, v ); return *this; }
    constexpr PSR& setN( bool v )                         { setApplicationNegative( v ); return *this; }
};

void function() {
    PSR currentState = 0x41000000;
    bool isEqual = currentState.isApplicationZeroSet();
    bool isGreaterThan = !isEqual && currentState.isN() == currentState.isV();
    if( isGreaterThan ) {
        currentState.setIEN( PSR::IEN::IRQ23 ); // software trigger interrupt
    }
    else if( currentState.isApplicationZeroSet() ) {
        currentState.setIEN( PSR::IEN::HardFault ); // software trigger interrupt
    }
}
// end::example_register_psr[]

// tag::example_bme280_config[]
// BME280 - Combined humidity and pressure sensor
class Config : public EDF::BitField8 {
public:
    enum class Filter {
        OFF     = 0b000,
        Two     = 0b001,
        Four    = 0b010,
        Eight   = 0b011,
        Sixteen = 0b100
    };
    enum class InactiveDuration {
        MS_0_5  = 0b000, // 0.5 ms
        MS_62_5 = 0b001, // 62.5 ms
        MS_125  = 0b010, // 125 ms
        MS_250  = 0b011, // 250 ms
        MS_500  = 0b100, // 500 ms
        MS_1000 = 0b101, // 1000 ms
        MS_10   = 0b110, // 10 ms
        MS_20   = 0b111, // 20 ms
    };
public:
    constexpr Config( uint8_t initialValue = 0 ) : EDF::BitField8( initialValue ) {}

    /* 3-wire SPI enabled = 1, disabled = 0 */
    constexpr bool isSPI3w_en() const { return get( 0, 1 ); }
    constexpr Config& setSPI3w_en( bool enable ) { set( 0, 1, enable ); return *this; }

    /* IIR time constant */
    constexpr Filter getFilter() const { return static_cast<Filter>(get( 2, 3 )); }
    constexpr Config& setFilter( Filter f ) { set( 2, 3, static_cast<uint8_t>(f) ); return *this; }

    /* Inactive duration t_standby in normal mode */
    constexpr InactiveDuration getT_sb() const { return static_cast<InactiveDuration>(get( 5, 3 )); }
    constexpr InactiveDuration getInactiveDuration() const { return getT_sb(); }
    constexpr Config& setT_sb( InactiveDuration d ) { set( 5, 3, static_cast<uint8_t>(d)); return *this; }
    constexpr Config& setInactiveDuration( InactiveDuration d ) { setT_sb( d ); return *this; }
};

void BME280_init() {
    // ...
    Config()
        .setSPI3w_en( false )
        .setFilter( Config::Filter::OFF )
        .setInactiveDuration( Config::InactiveDuration::MS_10 );
    // ...
}

Config readConfig() {
    // Imagine this value was read from the sensor
    return Config( 0xC0 );
}

void someOtherFunction() {
    // Imagine Config
    if( readConfig().getInactiveDuration() == Config::InactiveDuration::MS_10 ) {
        /* ...  */
    }
}
// end::example_bme280_config[]


int main( void ) {
    // tag::init_default[]
    EDF::BitField32 bitfield;
    // end::init_default[]

    // tag::init_with_value[]
    EDF::BitField8 bitfieldWithValue( 0xB1 );
    // end::init_with_value[]
    (void)bitfieldWithValue;
    // tag::operation_set[]
    bitfield.set( 8, 16, 0xAA55 ); // 0x00AA5500
    // end::operation_set[]

    // tag::operation_get[]
    bitfield.get( 12, 8 ); // 0x000000A5
    // end::operation_get[]

    // tag::operation_operatorT[]
    uint32_t value = bitfield & 0xFFFF;
    // end::operation_operatorT[]
    (void)value;

    return 0;
}
