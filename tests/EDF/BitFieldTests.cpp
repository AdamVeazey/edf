/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/BitField.hpp>

#include <gtest/gtest.h>

TEST(BitField, Initialization) {
    EDF::BitField64 bitField64;
    EXPECT_EQ( bitField64.get(0, 64), 0 );

    EDF::BitField32 bitField32 = 0x12345678;
    EXPECT_EQ( bitField32.get(0, 32), 0x12345678 );

    EDF::BitField16 bitField16( 0xA500 );
    EXPECT_EQ( bitField16.get(0, 16), 0xA500 );

    EDF::BitField8 bitField8 = 0b00110010;
    EXPECT_EQ( bitField8.get(0, 8), 0b00110010 );
}

TEST(BitField, SetAndGetBits) {
    EDF::BitField32 bitField;

    bitField.set( 0, 4, 12 );
    EXPECT_EQ( bitField.get( 0, 4 ), 12 );

    bitField.set( 0, 4, 5 );
    EXPECT_EQ( bitField.get( 0, 4 ), 5 );

    bitField.set( 4, 8, 255 );
    EXPECT_EQ( bitField.get( 0, 4 ), 5 ); // these bits should not have changed
    EXPECT_EQ( bitField.get( 4, 8 ), 255 );
    EXPECT_EQ( bitField.get( 0, 32 ), 0xFF5 );
}

// Example Register description
// [Enable][x][MODE1][MODE0][x][x][SPEED1][SPEED0]    <- Meaning
//    7     6    5      4    3  2    1        0       <- bits
struct PeripheralRegister : public EDF::BitField8 {
    enum class Speed : uint8_t {
        SLOW,
        MODERATE,
        FAST,
    };
    enum class Mode : uint8_t {
        MODE_1,
        MODE_2,
        MODE_3,
    };
    using EDF::BitField8::BitField8;
    constexpr PeripheralRegister( uint8_t initialValue = 0 ) :
        EDF::BitField8( initialValue )
    {}

    constexpr Speed getSpeed()                                  const { return static_cast<Speed>(get( 0, 2 )); }
    constexpr PeripheralRegister& setSpeed( const Speed& s )          { setSpeed( static_cast<std::underlying_type_t<Speed>>(s) ); return *this; }
    constexpr PeripheralRegister& setSpeed( uint8_t speed )           { set( 0, 2, speed ); return *this; }

    constexpr Mode getMode()                                    const { return static_cast<Mode>(get( 4, 2 )); }
    constexpr PeripheralRegister& setMode( const Mode& m )            { setMode( static_cast<std::underlying_type_t<Mode>>(m) ); return *this; }
    constexpr PeripheralRegister& setMode( uint8_t mode )             { set( 4, 2, mode ); return *this; }

    constexpr bool isEnabled()                                  const { return get( 7, 1 ); }
    constexpr PeripheralRegister& setEnable( bool enable )            { set( 7, 1, enable ); return *this; }
};

TEST(BitField, PeripheralRegister) {
    PeripheralRegister config = 0x21;

    // initial values, found by looking at the 'Example Register description'
    EXPECT_EQ( config.getSpeed(), PeripheralRegister::Speed::MODERATE );
    EXPECT_EQ( config.getMode(), PeripheralRegister::Mode::MODE_3 );
    EXPECT_EQ( config.isEnabled(), false );

    // Set speed using enumeration. No need to think about the bit shifting
    config.setSpeed( PeripheralRegister::Speed::FAST );
    EXPECT_EQ( config.getSpeed(), PeripheralRegister::Speed::FAST );
    EXPECT_EQ( config.getMode(), PeripheralRegister::Mode::MODE_3 );    // Should not change
    EXPECT_EQ( config.isEnabled(), false );                             // Should not change

    // Set mode using enumeration. No need to think about the bit shifting
    config.setMode( PeripheralRegister::Mode::MODE_1 );
    EXPECT_EQ( config.getSpeed(), PeripheralRegister::Speed::FAST );    // should not change
    EXPECT_EQ( config.getMode(), PeripheralRegister::Mode::MODE_1 );
    EXPECT_EQ( config.isEnabled(), false );                             // Should not change

    // Enable peripheral. No need to think about the bit shifting
    config.setEnable( true );
    EXPECT_EQ( config.getSpeed(), PeripheralRegister::Speed::FAST );    // should not change
    EXPECT_EQ( config.getMode(), PeripheralRegister::Mode::MODE_1 );    // Should not change
    EXPECT_EQ( config.isEnabled(), true );
}

/* --- Compile-Time (constexpr) Verification --- */
constexpr bool verifyPeripheralRegisterConstexpr() {
    PeripheralRegister config = PeripheralRegister()
        .setSpeed(PeripheralRegister::Speed::MODERATE)
        .setMode(PeripheralRegister::Mode::MODE_3)
        .setEnable(false);

    if( config.getSpeed() != PeripheralRegister::Speed::MODERATE )  return false;
    if( config.getMode() != PeripheralRegister::Mode::MODE_3 )      return false;
    if( config.isEnabled() != false )                               return false;

    config.setSpeed( PeripheralRegister::Speed::FAST );
    if( config.getSpeed() != PeripheralRegister::Speed::FAST )      return false;

    config.setMode( PeripheralRegister::Mode::MODE_1 );
    if( config.getMode() != PeripheralRegister::Mode::MODE_1 )      return false;

    config.setEnable( true );
    if( !config.isEnabled() )                                       return false;

    return true;
}

// This static_assert forces the compiler to evaluate the entire sequence
// of bitfield manipulations at COMPILE TIME. If any function wasn't truly
// constexpr, compilation would fail instantly right here.
static_assert( verifyPeripheralRegisterConstexpr(), "BitField and PeripheralRegister must be fully constexpr capable!" );

TEST(BitField, ConstexprEvaluation) {
    // Double-check at runtime as well to ensure test framework tracks it
    constexpr bool result = verifyPeripheralRegisterConstexpr();
    EXPECT_TRUE( result );
}

TEST(BitField, InvalidValues) {
    EDF::BitField8 bf8 = 0xF0;
    // Invalid span values
    EXPECT_DEATH(bf8.set( 0, 9, 0xFF ), ""); // would spill outside of the bitfield
    EXPECT_DEATH(bf8.set( 4, 5, 0x1F ), ""); // would spill outside of the bitfield
    EXPECT_DEATH(bf8.get( 4, 5 ), ""); // startBit + span = 9 > 8
    EXPECT_DEATH(bf8.get( 8, 1 ), ""); // startBit >= 8
    EXPECT_DEATH(bf8.set( 0, 0, 0 ), ""); // 0 span!?
    EXPECT_DEATH(bf8.get( 0, 0 ), ""); // 0 span!?

    // Invalid values
    EXPECT_DEATH(bf8.set( 0, 2, 0xF ), ""); // 0xF bigger than 2 bits
}

TEST(BitField, FullWidthBoundary) {
    EDF::BitField32 bf32 = 0;
    bf32.set(0, 32, 0xFFFFFFFF);
    EXPECT_EQ(bf32.get(0, 32), 0xFFFFFFFF);
}