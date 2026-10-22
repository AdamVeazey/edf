/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Color.hpp>

#include <gtest/gtest.h>

TEST(Color, InitializationRGB) {
    EDF::Color black;
    EXPECT_EQ( black.asRGB(), 0 );

    EDF::Color foreground( 0x4B85E3 ); // from color code
    EXPECT_EQ( foreground.asRGB(), 0x4B85E3 );

    EDF::Color background( 46, 51, 59 );
    EXPECT_EQ( background.asRGB(), 0x2E333B );
}

TEST(Color, InitializationRGBA) {
    EDF::Color black;
    EXPECT_EQ( black.asRGBA(), 0 );

    EDF::Color foreground( 0x804B85E3 );
    EXPECT_EQ( foreground.asRGBA(), 0x804B85E3 );

    EDF::Color background( 46, 51, 59 );
    EXPECT_EQ( background.asRGBA(), 0xFF2E333B );
}

TEST(Color, GetColorComponents) {
    EDF::Color black;
    EXPECT_EQ( black.r(), 0 );
    EXPECT_EQ( black.g(), 0 );
    EXPECT_EQ( black.b(), 0 );
    EXPECT_EQ( black.a(), 0 );

    EDF::Color foreground( 0x804B85E3 );
    EXPECT_EQ( foreground.r(), 0x4B );
    EXPECT_EQ( foreground.g(), 0x85 );
    EXPECT_EQ( foreground.b(), 0xE3 );
    EXPECT_EQ( foreground.a(), 0x80 );

    EDF::Color background( 46, 51, 59 );
    EXPECT_EQ( background.r(), 46 );
    EXPECT_EQ( background.g(), 51 );
    EXPECT_EQ( background.b(), 59 );
    EXPECT_EQ( background.a(), 0xFF );
}

TEST(Color, SetColorComponents) {
    EDF::Color originallyBlack;

    originallyBlack.setR( 255 );
    EXPECT_EQ( originallyBlack.r(), 255 );
    EXPECT_EQ( originallyBlack.g(), 0 );
    EXPECT_EQ( originallyBlack.b(), 0 );
    EXPECT_EQ( originallyBlack.a(), 0 );

    originallyBlack.setG( 255 );
    EXPECT_EQ( originallyBlack.r(), 255 );
    EXPECT_EQ( originallyBlack.g(), 255 );
    EXPECT_EQ( originallyBlack.b(), 0 );
    EXPECT_EQ( originallyBlack.a(), 0 );

    originallyBlack.setB( 255 );
    EXPECT_EQ( originallyBlack.r(), 255 );
    EXPECT_EQ( originallyBlack.g(), 255 );
    EXPECT_EQ( originallyBlack.b(), 255 );
    EXPECT_EQ( originallyBlack.a(), 0 );

    originallyBlack.setA( 255 );
    EXPECT_EQ( originallyBlack.r(), 255 );
    EXPECT_EQ( originallyBlack.g(), 255 );
    EXPECT_EQ( originallyBlack.b(), 255 );
    EXPECT_EQ( originallyBlack.a(), 255 );

    originallyBlack.setG( 128 );
    EXPECT_EQ( originallyBlack.r(), 255 );
    EXPECT_EQ( originallyBlack.g(), 128 );
    EXPECT_EQ( originallyBlack.b(), 255 );
    EXPECT_EQ( originallyBlack.a(), 255 );
}

TEST(Color, NamedColors) {
    auto red = EDF::Color::red();
    EXPECT_EQ( red.r(), 255 );
    EXPECT_EQ( red.g(), 0 );
    EXPECT_EQ( red.b(), 0 );

    auto green = EDF::Color::green();
    EXPECT_EQ( green.r(), 0 );
    EXPECT_EQ( green.g(), 255 );
    EXPECT_EQ( green.b(), 0 );

    auto blue = EDF::Color::blue();
    EXPECT_EQ( blue.r(), 0 );
    EXPECT_EQ( blue.g(), 0 );
    EXPECT_EQ( blue.b(), 255 );

    auto white = EDF::Color::white();
    EXPECT_EQ( white.r(), 255 );
    EXPECT_EQ( white.g(), 255 );
    EXPECT_EQ( white.b(), 255 );
}

TEST(Color565, InitializationAndConversion) {
    EDF::Color565 col( 0xF800 ); // Pure Red in 565
    EXPECT_EQ( col.asRGB(), 0xF800 );
    EXPECT_EQ( col.r(), 31 ); // 5 bits max mapped back (approx or exact depending on shift logic)
    EXPECT_EQ( col.g(), 0 );
    EXPECT_EQ( col.b(), 0 );

    // Conversion from 24-bit Color
    EDF::Color565 red = EDF::Color::red();
    EXPECT_EQ( red.r(), 31 );
    EXPECT_EQ( red.g(), 0 );
    EXPECT_EQ( red.b(), 0 );

    EDF::Color565 green = EDF::Color::green();
    EXPECT_EQ( green.r(), 0 );
    EXPECT_EQ( green.g(), 63 );
    EXPECT_EQ( green.b(), 0 );

    EDF::Color565 blue = EDF::Color::blue();
    EXPECT_EQ( blue.r(), 0 );
    EXPECT_EQ( blue.g(), 0 );
    EXPECT_EQ( blue.b(), 31 );

    EDF::Color565 white = EDF::Color::white();
    EXPECT_EQ( white.r(), 31 );
    EXPECT_EQ( white.g(), 63 );
    EXPECT_EQ( white.b(), 31 );
}

TEST(Color, ConstexprCompileTimeEvaluation) {
    // Verify constructors and getters evaluate at compile-time via static_assert
    constexpr EDF::Color compileTimeBlack;
    static_assert( compileTimeBlack.asRGB() == 0, "Compile-time black failed" );
    static_assert( compileTimeBlack.r() == 0, "Compile-time red component failed" );

    constexpr EDF::Color compileTimeCustom( 100, 150, 200 );
    static_assert( compileTimeCustom.r() == 100, "Compile-time custom R failed" );
    static_assert( compileTimeCustom.g() == 150, "Compile-time custom G failed" );
    static_assert( compileTimeCustom.b() == 200, "Compile-time custom B failed" );

    // Verify named colors can be used in constexpr contexts
    constexpr EDF::Color compileTimeRed = EDF::Color::red();
    static_assert( compileTimeRed.r() == 255, "Compile-time named red R failed" );
    static_assert( compileTimeRed.g() == 0, "Compile-time named red G failed" );

    // Verify setters work in a constexpr context (constructing and mutating a temporary)
    constexpr auto mutatedColor = []() {
        EDF::Color c;
        c.setR( 42 );
        c.setG( 84 );
        return c;
    }();
    static_assert( mutatedColor.r() == 42, "Compile-time mutation R failed" );
    static_assert( mutatedColor.g() == 84, "Compile-time mutation G failed" );

    // Verify Color565 compile-time evaluation
    constexpr EDF::Color565 compileTime565( EDF::Color::white() ); // Max RGB565 values
    static_assert( compileTime565.asRGB() == 0xFFFF, "Compile-time Color565 failed" );

    // If everything compiled successfully, pass a dummy runtime assertion so GTest counts it
    SUCCEED();
}

TEST(Color, EqualityOperators) {
    constexpr EDF::Color red1 = EDF::Color::red();
    constexpr EDF::Color red2( 255, 0, 0 );
    constexpr EDF::Color blue = EDF::Color::blue();

    // Test equality
    EXPECT_EQ( red1, red2 );
    EXPECT_TRUE( red1 == red2 );

    // Test inequality
    EXPECT_NE( red1, blue );
    EXPECT_TRUE( red1 != blue );

    // Compile-time (constexpr) verification
    static_assert( EDF::Color::red() == EDF::Color(255, 0, 0), "Constexpr color equality failed" );
    static_assert( EDF::Color::red() != EDF::Color::blue(), "Constexpr color inequality failed" );
}

TEST(Color565, EqualityOperators) {
    constexpr EDF::Color565 col1( 0xF800 ); // Pure Red in 565
    constexpr EDF::Color565 col2( 0xF800 );
    constexpr EDF::Color565 col3( 0x001F ); // Pure Blue in 565

    // Test equality
    EXPECT_EQ( col1, col2 );
    EXPECT_TRUE( col1 == col2 );

    // Test inequality
    EXPECT_NE( col1, col3 );
    EXPECT_TRUE( col1 != col3 );

    // Compile-time (constexpr) verification
    static_assert( col1 == col2, "Constexpr Color565 equality failed" );
    static_assert( col1 != col3, "Constexpr Color565 inequality failed" );
}