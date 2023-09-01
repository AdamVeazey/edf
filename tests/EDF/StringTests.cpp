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

TEST(String, InitializationFromIntegerBase10) {
    int8_t valueInt8_t = 0xAA;
    EDF::String<32> stringInt8_t( valueInt8_t );
    EXPECT_STREQ( stringInt8_t.asCString(), "-86" );

    int16_t valueInt16_t = 0xAA55;
    EDF::String<32> stringInt16_t( valueInt16_t );
    EXPECT_STREQ( stringInt16_t.asCString(), "-21931" );

    int32_t valueInt32_t = 0x12345678;
    EDF::String<32> stringInt32_t( valueInt32_t );
    EXPECT_STREQ( stringInt32_t.asCString(), "305419896" );

    int64_t valueInt64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringInt64_t( valueInt64_t );
    EXPECT_STREQ( stringInt64_t.asCString(), "1311768467463790320" );

    uint8_t valueUint8_t = 0xAA;
    EDF::String<32> stringUint8_t( valueUint8_t );
    EXPECT_STREQ( stringUint8_t.asCString(), "170" );

    uint16_t valueUint16_t = 0xAA55;
    EDF::String<32> stringUint16_t( valueUint16_t );
    EXPECT_STREQ( stringUint16_t.asCString(), "43605" );

    uint32_t valueUint32_t = 0x12345678;
    EDF::String<32> stringUint32_t( valueUint32_t );
    EXPECT_STREQ( stringUint32_t.asCString(), "305419896" );

    uint64_t valueUint64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringUint64_t( valueUint64_t );
    EXPECT_STREQ( stringUint64_t.asCString(), "1311768467463790320" );
}

TEST(String, InitializationFromIntegerBase2) {
    int8_t valueInt8_t = 0xAA;
    EDF::String<32> stringInt8_t( valueInt8_t, 2 );
    EXPECT_STREQ( stringInt8_t.asCString(), "10101010" );

    int16_t valueInt16_t = 0xAA55;
    EDF::String<32> stringInt16_t( valueInt16_t, 2 );
    EXPECT_STREQ( stringInt16_t.asCString(), "1010101001010101" );

    int32_t valueInt32_t = 0x12345678;
    EDF::String<32> stringInt32_t( valueInt32_t, 2 );
    EXPECT_STREQ( stringInt32_t.asCString(), "10010001101000101011001111000" );

    int64_t valueInt64_t = 0x123456789ABCDEF0;
    EDF::String<64> stringInt64_t( valueInt64_t, 2 );
    EXPECT_STREQ( stringInt64_t.asCString(), "1001000110100010101100111100010011010101111001101111011110000" );

    uint8_t valueUint8_t = 0xAA;
    EDF::String<32> stringUint8_t( valueUint8_t, 2 );
    EXPECT_STREQ( stringUint8_t.asCString(), "10101010" );

    uint16_t valueUint16_t = 0xAA55;
    EDF::String<32> stringUint16_t( valueUint16_t, 2 );
    EXPECT_STREQ( stringUint16_t.asCString(), "1010101001010101" );

    uint32_t valueUint32_t = 0x12345678;
    EDF::String<32> stringUint32_t( valueUint32_t, 2 );
    EXPECT_STREQ( stringUint32_t.asCString(), "10010001101000101011001111000" );

    uint64_t valueUint64_t = 0x123456789ABCDEF0;
    EDF::String<64> stringUint64_t( valueUint64_t, 2 );
    EXPECT_STREQ( stringUint64_t.asCString(), "1001000110100010101100111100010011010101111001101111011110000" );
}

TEST(String, InitializationFromIntegerBase8) {
    int8_t valueInt8_t = 0xAA;
    EDF::String<32> stringInt8_t( valueInt8_t, 8 );
    EXPECT_STREQ( stringInt8_t.asCString(), "252" );

    int16_t valueInt16_t = 0xAA55;
    EDF::String<32> stringInt16_t( valueInt16_t, 8 );
    EXPECT_STREQ( stringInt16_t.asCString(), "125125" );

    int32_t valueInt32_t = 0x12345678;
    EDF::String<32> stringInt32_t( valueInt32_t, 8 );
    EXPECT_STREQ( stringInt32_t.asCString(), "2215053170" );

    int64_t valueInt64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringInt64_t( valueInt64_t, 8 );
    EXPECT_STREQ( stringInt64_t.asCString(), "110642547423257157360" );

    uint8_t valueUint8_t = 0xAA;
    EDF::String<32> stringUint8_t( valueUint8_t, 8 );
    EXPECT_STREQ( stringUint8_t.asCString(), "252" );

    uint16_t valueUint16_t = 0xAA55;
    EDF::String<32> stringUint16_t( valueUint16_t, 8 );
    EXPECT_STREQ( stringUint16_t.asCString(), "125125" );

    uint32_t valueUint32_t = 0x12345678;
    EDF::String<32> stringUint32_t( valueUint32_t, 8 );
    EXPECT_STREQ( stringUint32_t.asCString(), "2215053170" );

    uint64_t valueUint64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringUint64_t( valueUint64_t, 8 );
    EXPECT_STREQ( stringUint64_t.asCString(), "110642547423257157360" );
}

TEST(String, InitializationFromIntegerBase16) {
    int8_t valueInt8_t = 0xAA;
    EDF::String<32> stringInt8_t( valueInt8_t, 16 );
    EXPECT_STREQ( stringInt8_t.asCString(), "AA" );

    int16_t valueInt16_t = 0xAA55;
    EDF::String<32> stringInt16_t( valueInt16_t, 16 );
    EXPECT_STREQ( stringInt16_t.asCString(), "AA55" );

    int32_t valueInt32_t = 0x12345678;
    EDF::String<32> stringInt32_t( valueInt32_t, 16 );
    EXPECT_STREQ( stringInt32_t.asCString(), "12345678" );

    int64_t valueInt64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringInt64_t( valueInt64_t, 16 );
    EXPECT_STREQ( stringInt64_t.asCString(), "123456789ABCDEF0" );

    uint8_t valueUint8_t = 0xAA;
    EDF::String<32> stringUint8_t( valueUint8_t, 16 );
    EXPECT_STREQ( stringUint8_t.asCString(), "AA" );

    uint16_t valueUint16_t = 0xAA55;
    EDF::String<32> stringUint16_t( valueUint16_t, 16 );
    EXPECT_STREQ( stringUint16_t.asCString(), "AA55" );

    uint32_t valueUint32_t = 0x12345678;
    EDF::String<32> stringUint32_t( valueUint32_t, 16 );
    EXPECT_STREQ( stringUint32_t.asCString(), "12345678" );

    uint64_t valueUint64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringUint64_t( valueUint64_t, 16 );
    EXPECT_STREQ( stringUint64_t.asCString(), "123456789ABCDEF0" );
}

TEST(String, InitializationFromIntegerBase36) {
    int8_t valueInt8_t = 0xAA;
    EDF::String<32> stringInt8_t( valueInt8_t, 36 );
    EXPECT_STREQ( stringInt8_t.asCString(), "4Q" );

    int16_t valueInt16_t = 0xAA55;
    EDF::String<32> stringInt16_t( valueInt16_t, 36 );
    EXPECT_STREQ( stringInt16_t.asCString(), "XN9" );

    int32_t valueInt32_t = 0x12345678;
    EDF::String<32> stringInt32_t( valueInt32_t, 36 );
    EXPECT_STREQ( stringInt32_t.asCString(), "51U7I0" );

    int64_t valueInt64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringInt64_t( valueInt64_t, 36 );
    EXPECT_STREQ( stringInt64_t.asCString(), "9YS742PPS3QO" );

    uint8_t valueUint8_t = 0xAA;
    EDF::String<32> stringUint8_t( valueUint8_t, 36 );
    EXPECT_STREQ( stringUint8_t.asCString(), "4Q" );

    uint16_t valueUint16_t = 0xAA55;
    EDF::String<32> stringUint16_t( valueUint16_t, 36 );
    EXPECT_STREQ( stringUint16_t.asCString(), "XN9" );

    uint32_t valueUint32_t = 0x12345678;
    EDF::String<32> stringUint32_t( valueUint32_t, 36 );
    EXPECT_STREQ( stringUint32_t.asCString(), "51U7I0" );

    uint64_t valueUint64_t = 0x123456789ABCDEF0;
    EDF::String<32> stringUint64_t( valueUint64_t, 36 );
    EXPECT_STREQ( stringUint64_t.asCString(), "9YS742PPS3QO" );
}

TEST(String, InitializationFromEDFString) {
    EDF::String<16> smallerString = "Smaller String";
    EDF::String<32> string( smallerString );

    EXPECT_EQ( string.length(), 14 );
    EXPECT_STREQ( string.asCString(), "Smaller String" );

    EDF::String<20> fromLargerString( string );
    EXPECT_EQ( fromLargerString.length(), 14 );
    EXPECT_STREQ( fromLargerString.asCString(), "Smaller String" );
}

TEST(String, IsEmpty) {
    EDF::String<2> string;
    EXPECT_TRUE( string.isEmpty() );

    string += 'H';
    EXPECT_FALSE( string.isEmpty() );
}

TEST(String, IsFull) {
    EDF::String<2> string;
    EXPECT_FALSE( string.isFull() );

    string += 'H';
    EXPECT_EQ( string.length(), 1 );
    EXPECT_TRUE( string.isFull() );
}

TEST(String, Length) {
    EDF::String<32> string;
    EXPECT_EQ( string.length(), 0 );

    string = "Four";
    EXPECT_EQ( string.length(), 4 );

    string += " more characters";
    EXPECT_EQ( string.length(), 20 );

    string.insert( string.begin(), "Twelve ch. " );
    EXPECT_EQ( string.length(), 31 );
    EXPECT_EQ( string.length(), string.maxLength() );
}

TEST(String, MaxLength) {
    EDF::String<1> stringOne;
    EXPECT_EQ( stringOne.maxLength(), 0 );

    EDF::String<2> stringTwo;
    EXPECT_EQ( stringTwo.maxLength(), 1 );

    EDF::String<8> stringEight;
    EXPECT_EQ( stringEight.maxLength(), 7 );

    EDF::String<10> stringTen;
    EXPECT_EQ( stringTen.maxLength(), 9 );

    EDF::String<100> stringOneHundred;
    EXPECT_EQ( stringOneHundred.maxLength(), 99 );

    EDF::String<1000> stringOneThousand;
    EXPECT_EQ( stringOneThousand.maxLength(), 999 );
}

TEST(String, At) {
    EDF::String<16> string = "Hello, World!";

    EXPECT_EQ( string.at( 0 ), 'H' );
    EXPECT_EQ( string.at( 1 ), 'e' );
    EXPECT_EQ( string.at( 2 ), 'l' );
    EXPECT_EQ( string.at( 3 ), 'l' );
    EXPECT_EQ( string.at( 4 ), 'o' );
    EXPECT_EQ( string.at( 5 ), ',' );
    EXPECT_EQ( string.at( 6 ), ' ' );
    EXPECT_EQ( string.at( 7 ), 'W' );
    EXPECT_EQ( string.at( 8 ), 'o' );
    EXPECT_EQ( string.at( 9 ), 'r' );
    EXPECT_EQ( string.at( 10 ), 'l' );
    EXPECT_EQ( string.at( 11 ), 'd' );
    EXPECT_EQ( string.at( 12 ), '!' );

    EXPECT_DEATH( string.at( 13 ), "" );

    string.at( 7 ) = 'w';
    EXPECT_EQ( string.at( 7 ), 'w' );
}

TEST(String, OperatorIndex) {
    EDF::String<16> string = "Hello, World!";

    EXPECT_EQ( string[0], 'H' );
    EXPECT_EQ( string[1], 'e' );
    EXPECT_EQ( string[2], 'l' );
    EXPECT_EQ( string[3], 'l' );
    EXPECT_EQ( string[4], 'o' );
    EXPECT_EQ( string[5], ',' );
    EXPECT_EQ( string[6], ' ' );
    EXPECT_EQ( string[7], 'W' );
    EXPECT_EQ( string[8], 'o' );
    EXPECT_EQ( string[9], 'r' );
    EXPECT_EQ( string[10], 'l' );
    EXPECT_EQ( string[11], 'd' );
    EXPECT_EQ( string[12], '!' );

    string[7] = 'w';
    EXPECT_EQ( string[7], 'w' );
}

TEST(String, AsCString) {
    EDF::String<16> string = "Hello, world!";
    EXPECT_STREQ( string.asCString(), "Hello, world!" );

    EXPECT_STREQ( EDF::String<16>().asCString(), "" );

    char* p = string.asCString();
    EXPECT_STREQ( p, "Hello, world!" );
}

TEST(String, AsByteData) {
    static constexpr uint8_t data[] = { 0x27, 'O', 'k', 'a', 'y', '\0' };
    EDF::String<16> string = data;

    for( std::size_t k = 0; k < sizeof(data)/sizeof(data[0]); ++k ) {
        EXPECT_EQ( string.asByteData()[k], data[k] );
    }

    uint8_t* p = string.asByteData();
    p[1] = 'o';
    EXPECT_EQ( string.asByteData()[1], 'o' );
}

TEST(String, ToIntegralBase10) {
    EXPECT_EQ( EDF::String<16>("-55").toInt8_t(), -55 );
    EXPECT_EQ( EDF::String<16>("-5566").toInt16_t(), -5566 );
    EXPECT_EQ( EDF::String<16>("-556677788").toInt32_t(), -556677788 );
    EXPECT_EQ( EDF::String<32>("-5566777889999999999").toInt64_t(), -5566777889999999999ll );

    EXPECT_EQ( EDF::String<16>("55").toUint8_t(), 55 );
    EXPECT_EQ( EDF::String<16>("5566").toUint16_t(), 5566 );
    EXPECT_EQ( EDF::String<16>("556677788").toUint32_t(), 556677788 );
    EXPECT_EQ( EDF::String<32>("5566777889999999999").toUint64_t(), 5566777889999999999ll );
}

TEST(String, ToIntegralBase16) {
    EXPECT_EQ( EDF::String<16>("C9").toInt8_t( 16 ), -55 );
    EXPECT_EQ( EDF::String<16>("EA42").toInt16_t( 16 ), -5566 );
    EXPECT_EQ( EDF::String<16>("DED1C564").toInt32_t( 16 ), -556677788 );
    EXPECT_EQ( EDF::String<32>("B2BED500CB0D2C01").toInt64_t( 16 ), -5566777889999999999ll );

    EXPECT_EQ( EDF::String<16>("37").toUint8_t( 16 ), 55 );
    EXPECT_EQ( EDF::String<16>("15BE").toUint16_t( 16 ), 5566 );
    EXPECT_EQ( EDF::String<16>("212E3A9C").toUint32_t( 16 ), 556677788 );
    EXPECT_EQ( EDF::String<32>("4D412AFF34F2D3FF").toUint64_t( 16 ), 5566777889999999999ll );
}

TEST(String, ToIntegralBase2) {
    EXPECT_EQ( EDF::String<9>("11001001").toInt8_t( 2 ), -55 );
    EXPECT_EQ( EDF::String<17>("1110101001000010").toInt16_t( 2 ), -5566 );
    EXPECT_EQ( EDF::String<33>("11011110110100011100010101100100").toInt32_t( 2 ), -556677788 );
    EXPECT_EQ( EDF::String<65>("1011001010111110110101010000000011001011000011010010110000000001").toInt64_t( 2 ), -5566777889999999999ll );

    EXPECT_EQ( EDF::String<9>("00110111").toUint8_t( 2 ), 55 );
    EXPECT_EQ( EDF::String<17>("0001010110111110").toUint16_t( 2 ), 5566 );
    EXPECT_EQ( EDF::String<33>("00100001001011100011101010011100").toUint32_t( 2 ), 556677788 );
    EXPECT_EQ( EDF::String<65>("0100110101000001001010101111111100110100111100101101001111111111").toUint64_t( 2 ), 5566777889999999999ll );
}

TEST(String, ToIntegralBase8) {
    EXPECT_EQ( EDF::String<16>("311").toInt8_t( 8 ), -55 );
    EXPECT_EQ( EDF::String<16>("165102").toInt16_t( 8 ), -5566 );
    EXPECT_EQ( EDF::String<16>("33664342544").toInt32_t( 8 ), -556677788 );
    EXPECT_EQ( EDF::String<32>("1312766520031303226001").toInt64_t( 8 ), -5566777889999999999ll );

    EXPECT_EQ( EDF::String<16>("67").toUint8_t( 8 ), 55 );
    EXPECT_EQ( EDF::String<16>("12676").toUint16_t( 8 ), 5566 );
    EXPECT_EQ( EDF::String<16>("4113435234").toUint32_t( 8 ), 556677788 );
    EXPECT_EQ( EDF::String<32>("465011257746474551777").toUint64_t( 8 ), 5566777889999999999ll );
}