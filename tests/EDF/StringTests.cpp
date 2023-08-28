/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/String.hpp>

#include <gtest/gtest.h>

TEST(String, InitializationDefault) {
    EDF::String<16> string;
    EXPECT_EQ( string.length(), 0 );
    EXPECT_EQ( string[0], '\0' );
    EXPECT_STREQ( string.asCString(), "" );
}

TEST(String, InitializationFromPointer) {
    EDF::String<32> stringChar( "const char*" );
    EXPECT_EQ( stringChar.length(), std::strlen("const char*") );
    EXPECT_STREQ( stringChar.asCString(), "const char*" );

    EDF::String<32> stringUint8_t( reinterpret_cast<const uint8_t*>("const uint8_t*") );
    EXPECT_EQ( stringUint8_t.length(), std::strlen("const uint8_t*") );
    EXPECT_STREQ( stringUint8_t.asCString(), "const uint8_t*" );
}

TEST(String, InitializationFromPointerAndLength) {
    EDF::String<32> stringChar( "const char*", std::strlen("const char*") );
    EXPECT_EQ( stringChar.length(), std::strlen("const char*") );
    EXPECT_STREQ( stringChar.asCString(), "const char*" );

    EDF::String<32> stringUint8_t( reinterpret_cast<const uint8_t*>("const uint8_t*"), std::strlen("const uint8_t*") );
    EXPECT_EQ( stringUint8_t.length(), std::strlen("const uint8_t*") );
    EXPECT_STREQ( stringUint8_t.asCString(), "const uint8_t*" );
}

TEST(String, InitializationFromArray) {
    const char cStringChar[] = "const char (&str)[S]";
    EDF::String<32> stringChar( cStringChar );
    EXPECT_EQ( stringChar.length(), std::strlen(cStringChar) );
    EXPECT_STREQ( stringChar.asCString(), cStringChar );

    const uint8_t cStringUint8_t[] = "const uint8_t (&str)[S]";
    EDF::String<32> stringUint8_t( cStringUint8_t );
    EXPECT_EQ( stringUint8_t.length(), std::strlen((const char*)cStringUint8_t) );
    EXPECT_STREQ( stringUint8_t.asCString(), (const char*)cStringUint8_t );
}

TEST(String, InitializationFromChar) {
    EDF::String<8> string( 'c' );
    EXPECT_EQ( string.length(), 1 );
    EXPECT_STREQ( string.asCString(), "c" );
}

