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