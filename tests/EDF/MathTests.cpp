/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Math.hpp>

#include <gtest/gtest.h>

TEST(Math, NumberOfElements) {
#define ARRAY_SIZE (10)
    unsigned char array[ARRAY_SIZE];

    // Comparison of nElements vs other methods typically used to find the array size
    EXPECT_EQ( EDF::nElements(array), sizeof(array)/sizeof(array[0]) );
    EXPECT_EQ( EDF::nElements(array), ARRAY_SIZE );
    EXPECT_EQ( EDF::nElements(array), 10 );
#undef ARRAY_SIZE
}

TEST(Math, IsPowerOfTwo) {
    EXPECT_TRUE( EDF::isPow2( 1 ) );
    EXPECT_TRUE( EDF::isPow2( 2 ) );
    EXPECT_TRUE( EDF::isPow2( 4 ) );
    EXPECT_TRUE( EDF::isPow2( 2147483648 ) );
    EXPECT_TRUE( EDF::isPow2( (1_uz << 31) ) );

    EXPECT_FALSE( EDF::isPow2( 0 ) );
    EXPECT_FALSE( EDF::isPow2( 3 ) );
    EXPECT_FALSE( EDF::isPow2( 5 ) );
    EXPECT_FALSE( EDF::isPow2( 6 ) );
    EXPECT_FALSE( EDF::isPow2( 7 ) );
    EXPECT_FALSE( EDF::isPow2( 1234567890 ) );
}

TEST(Math, Minimum) {
    EXPECT_EQ( EDF::min( 0, 0 ), 0 );
    EXPECT_EQ( EDF::min( 0, 1 ), 0 );
    EXPECT_EQ( EDF::min( 1, 0 ), 0 );
    EXPECT_EQ( EDF::min( -1, -1 ), -1 );
    EXPECT_EQ( EDF::min( 0, -1 ), -1 );
    EXPECT_EQ( EDF::min( -1, 0 ), -1 );
    EXPECT_EQ( EDF::min( 1, 1 ), 1 );
    EXPECT_EQ( EDF::min( -1, 1 ), -1 );
    EXPECT_EQ( EDF::min( 1, -1 ), -1 );
}

TEST(Math, Maximum) {
    EXPECT_EQ( EDF::max( 0, 0 ), 0 );
    EXPECT_EQ( EDF::max( 0, 1 ), 1 );
    EXPECT_EQ( EDF::max( 1, 0 ), 1 );
    EXPECT_EQ( EDF::max( -1, -1 ), -1 );
    EXPECT_EQ( EDF::max( 0, -1 ), 0 );
    EXPECT_EQ( EDF::max( -1, 0 ), 0 );
    EXPECT_EQ( EDF::max( 1, 1 ), 1 );
    EXPECT_EQ( EDF::max( -1, 1 ), 1 );
    EXPECT_EQ( EDF::max( 1, -1 ), 1 );
}

TEST(Math, VoltageDividerCalculateVoltageOutput) {
    constexpr std::size_t R1 = 5000;
    constexpr std::size_t R2 = 10000;

    constexpr int vOutInt_mV = EDF::voltageDividerCalcVout<R1, R2>( 3300 );
    EXPECT_EQ( vOutInt_mV, 2200 );

    constexpr int vOutInt_V = EDF::voltageDividerCalcVout<R1, R2>( 12 );
    EXPECT_EQ( vOutInt_V, 8 );

    constexpr float vOutFloat_mV = EDF::voltageDividerCalcVout<R1, R2>( 3.3f );
    EXPECT_FLOAT_EQ( vOutFloat_mV, 2.2f );

    constexpr double vOutDouble_V = EDF::voltageDividerCalcVout<R1, R2>( 12.0 );
    EXPECT_FLOAT_EQ( vOutDouble_V, 8.0 );
}

TEST(Math, VoltageDividerCalculateVoltageInput) {
    constexpr std::size_t R1 = 5000;
    constexpr std::size_t R2 = 10000;

    constexpr int vInInt_mV = EDF::voltageDividerCalcVin<R1, R2>( 2200 );
    EXPECT_EQ( vInInt_mV, 3300 );

    constexpr int vInInt_V = EDF::voltageDividerCalcVin<R1, R2>( 8 );
    EXPECT_EQ( vInInt_V, 12 );

    constexpr float vInFloat_mV = EDF::voltageDividerCalcVin<R1, R2>( 2.2f );
    EXPECT_FLOAT_EQ( vInFloat_mV, 3.3f );

    constexpr double vInDouble_V = EDF::voltageDividerCalcVin<R1, R2>( 8.0 );
    EXPECT_FLOAT_EQ( vInDouble_V, 12.0 );
}

TEST(Math, TemperatureCelsiusToFahrenheit) {
    const int degreesFInt1 = EDF::temperatureCtoF( 0 );
    EXPECT_EQ( degreesFInt1, 32 );

    const int degreesFInt2 = EDF::temperatureCtoF( -40 );
    EXPECT_EQ( degreesFInt2, -40 );

    const int degreesFInt3 = EDF::temperatureCtoF( 100 );
    EXPECT_EQ( degreesFInt3, 212 );

    const float degreesFFloat1 = EDF::temperatureCtoF( 0.0f );
    EXPECT_FLOAT_EQ( degreesFFloat1, 32.0f );

    const float degreesFFloat2 = EDF::temperatureCtoF( -40.0f );
    EXPECT_FLOAT_EQ( degreesFFloat2, -40.0f );

    const float degreesFFloat3 = EDF::temperatureCtoF( 100.0f );
    EXPECT_FLOAT_EQ( degreesFFloat3, 212.0f );
}

TEST(Math, TemperatureFahrenheitToCelsius) {
    const int degreesCInt1 = EDF::temperatureFtoC( 32 );
    EXPECT_EQ( degreesCInt1, 0 );

    const int degreesCInt2 = EDF::temperatureFtoC( -40 );
    EXPECT_EQ( degreesCInt2, -40 );

    const int degreesCInt3 = EDF::temperatureFtoC( 212 );
    EXPECT_EQ( degreesCInt3, 100 );

    const float degreesCFloat1 = EDF::temperatureFtoC( 32.0f );
    EXPECT_FLOAT_EQ( degreesCFloat1, 0.0f );

    const float degreesCFloat2 = EDF::temperatureFtoC( -40.0f );
    EXPECT_FLOAT_EQ( degreesCFloat2, -40.0f );

    const double degreesCFloat3 = EDF::temperatureFtoC( 212.0 );
    EXPECT_FLOAT_EQ( degreesCFloat3, 100.0f );
}