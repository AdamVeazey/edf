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

TEST(String, Append) {
    EDF::String<1024> string;

    string.append( "one " );
    EXPECT_STREQ( string.asCString(), "one " );

    string.append( reinterpret_cast<const uint8_t*>( "two " ) );
    EXPECT_STREQ( string.asCString(), "one two " );

    string.append( "three ", 6 );
    EXPECT_STREQ( string.asCString(), "one two three " );

    string.append( reinterpret_cast<const uint8_t*>( "four " ), 5 );
    EXPECT_STREQ( string.asCString(), "one two three four " );

    const char literalCharArray[] = "five ";
    string.append( literalCharArray );
    EXPECT_STREQ( string.asCString(), "one two three four five " );

    const uint8_t literalUint8_tArray[] = "six";
    string.append( literalUint8_tArray );
    EXPECT_STREQ( string.asCString(), "one two three four five six" );

    string.append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six " );

    int8_t vInt8_t = 0x7;
    string.append( vInt8_t, 16 ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 " );

    int16_t vInt16_t = 0x8;
    string.append( vInt16_t ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 " );

    int32_t vInt32_t = 0x9;
    string.append( vInt32_t ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 9 " );

    int32_t vInt64_t = 0xA;
    string.append( vInt64_t ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 9 10 " );

    uint8_t vUint8_t = 0xB;
    string.append( vUint8_t ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 9 10 11 " );

    uint16_t vUint16_t = 0xC;
    string.append( vUint16_t ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 9 10 11 12 " );

    uint32_t vUint32_t = 0xD;
    string.append( vUint32_t ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 9 10 11 12 13 " );

    uint32_t vUint64_t = 0xE;
    string.append( vUint64_t ).append( ' ' );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 9 10 11 12 13 14 " );

    EDF::String<32> otherString = "fifteen";
    string.append( otherString );
    EXPECT_STREQ( string.asCString(), "one two three four five six 7 8 9 10 11 12 13 14 fifteen" );
}

TEST(String, GetAppended) {
    EDF::String<32> string;

    EXPECT_STREQ( string.getAppended( "one " ).asCString(), "one " );

    EXPECT_STREQ( string.getAppended( reinterpret_cast<const uint8_t*>( "two " ) ).asCString(), "two " );

    EXPECT_STREQ( string.getAppended( "three ", 6 ).asCString(), "three " );

    EXPECT_STREQ( string.getAppended( reinterpret_cast<const uint8_t*>( "four " ), 5 ).asCString(), "four " );

    const char literalCharArray[] = "five ";
    EXPECT_STREQ( string.getAppended( literalCharArray ).asCString(), "five " );

    const uint8_t literalUint8_tArray[] = "six";
    EXPECT_STREQ( string.getAppended( literalUint8_tArray ).asCString(), "six" );

    EXPECT_STREQ( string.getAppended( ' ' ).asCString(), " " );

    int8_t vInt8_t = 0x7;
    EXPECT_STREQ( string.getAppended( vInt8_t, 16 ).asCString(), "7" );

    int16_t vInt16_t = 0x8;
    EXPECT_STREQ( string.getAppended( vInt16_t ).asCString(), "8" );

    int32_t vInt32_t = 0x9;
    EXPECT_STREQ( string.getAppended( vInt32_t ).asCString(), "9" );

    int32_t vInt64_t = 0xA;
    EXPECT_STREQ( string.getAppended( vInt64_t ).asCString(), "10" );

    uint8_t vUint8_t = 0xB;
    EXPECT_STREQ( string.getAppended( vUint8_t ).asCString(), "11" );

    uint16_t vUint16_t = 0xC;
    EXPECT_STREQ( string.getAppended( vUint16_t ).asCString(), "12" );

    uint32_t vUint32_t = 0xD;
    EXPECT_STREQ( string.getAppended( vUint32_t ).asCString(), "13" );

    uint32_t vUint64_t = 0xE;
    EXPECT_STREQ( string.getAppended( vUint64_t ).asCString(), "14" );

    EDF::String<32> otherString = "fifteen";
    EXPECT_STREQ( string.getAppended( otherString ).asCString(), "fifteen" );
}

TEST(String, Insert) {
    EDF::String<1024> string;

    string.insert( 0_uz, ' ' );
    EXPECT_STREQ( string.asCString(), " " );

    string.insert( 1_uz, 3_uz, ' ' );
    EXPECT_STREQ( string.asCString(), "    " );

    string.insert( 4_uz, { 't', 'e', 'e', 'n' } );
    EXPECT_STREQ( string.asCString(), "    teen" );

    string.insert( string.find('t'), 2_uz, 'f' );
    EXPECT_STREQ( string.asCString(), "    ffteen" );

    string.insert( string.find('f') + 1, 'i' );
    EXPECT_STREQ( string.asCString(), "    fifteen" );

    string.insert( string.find('f') - 1, {'f', 'o', 'u', 'r' } );
    EXPECT_STREQ( string.asCString(), "   four fifteen" );

    /**********************************************************************************************/

    string.insert( 7_uz, "teen" );
    EXPECT_STREQ( string.asCString(), "   fourteen fifteen" );

    string.insert( 2_uz, reinterpret_cast<const uint8_t*>("teen") );
    EXPECT_STREQ( string.asCString(), "  teen fourteen fifteen" );

    string.insert( string.find('t'), "th" );
    EXPECT_STREQ( string.asCString(), "  thteen fourteen fifteen" );

    string.insert( string.find('h') + 1, reinterpret_cast<const uint8_t*>("ir") );
    EXPECT_STREQ( string.asCString(), "  thirteen fourteen fifteen" );

    /**********************************************************************************************/

    string.insert( 1_uz, "twel", std::strlen("twel") );
    EXPECT_STREQ( string.asCString(), " twel thirteen fourteen fifteen" );

    string.insert( 5_uz, reinterpret_cast<const uint8_t*>("ve"), 2 );
    EXPECT_STREQ( string.asCString(), " twelve thirteen fourteen fifteen" );

    string.insert( string.begin(), reinterpret_cast<const uint8_t*>("ele"), 3 );
    EXPECT_STREQ( string.asCString(), "ele twelve thirteen fourteen fifteen" );

    string.insert( string.find( string.find('e') + 1, 'e' ) + 1, "ven", std::strlen("ven") );
    EXPECT_STREQ( string.asCString(), "eleven twelve thirteen fourteen fifteen" );

    /**********************************************************************************************/

    const char literalCharArray[] = "          ";
    string.insert( 0_uz, literalCharArray );
    EXPECT_STREQ( string.asCString(), "          eleven twelve thirteen fourteen fifteen" );

    const uint8_t literalUint8_tArray[] = "        ";
    string.insert( 49_uz, literalUint8_tArray );
    EXPECT_STREQ( string.asCString(), "          eleven twelve thirteen fourteen fifteen        " );

    const uint8_t literalUint8_tArray2[] = "ten";
    string.insert( string.find('e') - 1, literalUint8_tArray2 );
    EXPECT_STREQ( string.asCString(), "         ten eleven twelve thirteen fourteen fifteen        " );

    const char literalCharArray2[] = "nine";
    string.insert( string.find('t') - 1, literalCharArray2 );
    EXPECT_STREQ( string.asCString(), "        nine ten eleven twelve thirteen fourteen fifteen        " );

    /**********************************************************************************************/

    int8_t vInt8_t = 0x8;
    string.insert( 7_uz, vInt8_t, 16 );
    EXPECT_STREQ( string.asCString(), "       8 nine ten eleven twelve thirteen fourteen fifteen        " );

    int16_t vInt16_t = 7;
    string.insert( 6_uz, vInt16_t );
    EXPECT_STREQ( string.asCString(), "      7 8 nine ten eleven twelve thirteen fourteen fifteen        " );

    int32_t vInt32_t = 6;
    string.insert( 5_uz, vInt32_t );
    EXPECT_STREQ( string.asCString(), "     6 7 8 nine ten eleven twelve thirteen fourteen fifteen        " );

    int64_t vInt64_t = 5;
    string.insert( 4_uz, vInt64_t );
    EXPECT_STREQ( string.asCString(), "    5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen        " );

    uint8_t vUint8_t = 4;
    string.insert( 3_uz, vUint8_t );
    EXPECT_STREQ( string.asCString(), "   4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen        " );

    uint16_t vUint16_t = 3;
    string.insert( 2_uz, vUint16_t );
    EXPECT_STREQ( string.asCString(), "  3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen        " );

    uint32_t vUint32_t = 2;
    string.insert( 1_uz, vUint32_t );
    EXPECT_STREQ( string.asCString(), " 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen        " );

    uint64_t vUint64_t = 1;
    string.insert( 0_uz, vUint64_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen        " );

    vInt8_t = 16;
    string.insert( string.rfind('n').base() + 1, vInt8_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16       " );

    vInt16_t = 17;
    string.insert( string.rfind('6').base() + 1, vInt16_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17      " );

    vInt32_t = 18;
    string.insert( string.rfind('7').base() + 1, vInt32_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18     " );

    vInt64_t = 19;
    string.insert( string.rfind('8').base() + 1, vInt64_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18 19    " );

    vUint8_t = 20;
    string.insert( string.rfind('9').base() + 1, vUint8_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18 19 20   " );

    vUint16_t = 21;
    string.insert( string.rfind('0').base() + 1, vUint16_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18 19 20 21  " );

    vUint32_t = 22;
    string.insert( string.rfind('1').base() + 1, vUint32_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18 19 20 21 22 " );

    vUint64_t = 23;
    string.insert( string.rfind('2').base() + 1, vUint64_t );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18 19 20 21 22 23" );

    string.insert( 88_uz, EDF::String<13>(" twenty-four") );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18 19 20 21 22 23 twenty-four" );

    string.insert( string.end(), EDF::String<13>(" twenty-five") );
    EXPECT_STREQ( string.asCString(), "1 2 3 4 5 6 7 8 nine ten eleven twelve thirteen fourteen fifteen 16 17 18 19 20 21 22 23 twenty-four twenty-five" );
}

TEST(String, GetInserted) {
    EDF::String<32> string = "0123456789";

    EXPECT_STREQ( string.getInserted( 5_uz, ' ' ).asCString(), "01234 56789" );

    EXPECT_STREQ( string.getInserted( 2_uz, 3_uz, ' ' ).asCString(), "01   23456789" );

    EXPECT_STREQ( string.getInserted( 4_uz, { 't', 'e', 'e', 'n' } ).asCString(), "0123teen456789" );

    EXPECT_STREQ( string.getInserted( string.find('5'), 2_uz, 'f' ).asCString(), "01234ff56789" );

    EXPECT_STREQ( string.getInserted( string.find('3') + 1, 'i' ).asCString(), "0123i456789" );

    EXPECT_STREQ( string.getInserted( string.find('4') - 1, {'f', 'o', 'u', 'r' } ).asCString(), "012four3456789" );

    /**********************************************************************************************/

    EXPECT_STREQ( string.getInserted( 7_uz, "teen" ).asCString(), "0123456teen789" );

    EXPECT_STREQ( string.getInserted( 2_uz, reinterpret_cast<const uint8_t*>("teen") ).asCString(), "01teen23456789" );

    EXPECT_STREQ( string.getInserted( string.find('0'), "th" ).asCString(), "th0123456789" );

    EXPECT_STREQ( string.getInserted( string.find('3') + 1, reinterpret_cast<const uint8_t*>("ir") ).asCString(), "0123ir456789" );

    /**********************************************************************************************/

    EXPECT_STREQ( string.getInserted( 1_uz, "twel", std::strlen("twel") ).asCString(), "0twel123456789" );

    EXPECT_STREQ( string.getInserted( 5_uz, reinterpret_cast<const uint8_t*>("ve"), 2 ).asCString(), "01234ve56789" );

    EXPECT_STREQ( string.getInserted( string.begin(), reinterpret_cast<const uint8_t*>("ele"), 3 ).asCString(), "ele0123456789" );

    EXPECT_STREQ( string.getInserted( string.begin() + 2, "ven", std::strlen("ven") ).asCString(), "01ven23456789" );

    /**********************************************************************************************/

    const char literalCharArray[] = "          ";
    EXPECT_STREQ( string.getInserted( 0_uz, literalCharArray ).asCString(), "          0123456789" );

    const uint8_t literalUint8_tArray[] = "        ";
    EXPECT_STREQ( string.getInserted( 10_uz, literalUint8_tArray ).asCString(), "0123456789        " );

    const uint8_t literalUint8_tArray2[] = "ten";
    EXPECT_STREQ( string.getInserted( string.find('3') - 1, literalUint8_tArray2 ).asCString(), "01ten23456789" );

    const char literalCharArray2[] = "nine";
    EXPECT_STREQ( string.getInserted( string.find('7') - 1, literalCharArray2 ).asCString(), "012345nine6789" );

    /**********************************************************************************************/

    int8_t vInt8_t = 0x8;
    EXPECT_STREQ( string.getInserted( 7_uz, vInt8_t, 16 ).asCString(), "01234568789" );

    int16_t vInt16_t = 7;
    EXPECT_STREQ( string.getInserted( 6_uz, vInt16_t ).asCString(), "01234576789" );

    int32_t vInt32_t = 6;
    EXPECT_STREQ( string.getInserted( 5_uz, vInt32_t ).asCString(), "01234656789" );

    int64_t vInt64_t = 5;
    EXPECT_STREQ( string.getInserted( 4_uz, vInt64_t ).asCString(), "01235456789" );

    uint8_t vUint8_t = 4;
    EXPECT_STREQ( string.getInserted( 3_uz, vUint8_t ).asCString(), "01243456789" );

    uint16_t vUint16_t = 3;
    EXPECT_STREQ( string.getInserted( 2_uz, vUint16_t ).asCString(), "01323456789" );

    uint32_t vUint32_t = 2;
    EXPECT_STREQ( string.getInserted( 1_uz, vUint32_t ).asCString(), "02123456789" );

    uint64_t vUint64_t = 1;
    EXPECT_STREQ( string.getInserted( 0_uz, vUint64_t ).asCString(), "10123456789" );

    vInt8_t = 16;
    EXPECT_STREQ( string.getInserted( string.rfind('7').base() + 1, vInt8_t ).asCString(), "012345678169" );

    vInt16_t = 17;
    EXPECT_STREQ( string.getInserted( string.rfind('6').base() + 1, vInt16_t ).asCString(), "012345671789" );

    vInt32_t = 18;
    EXPECT_STREQ( string.getInserted( string.rfind('5').base() + 1, vInt32_t ).asCString(), "012345618789" );

    vInt64_t = 19;
    EXPECT_STREQ( string.getInserted( string.rfind('8').base() + 1, vInt64_t ).asCString(), "012345678919" );

    vUint8_t = 20;
    EXPECT_STREQ( string.getInserted( string.rfind('1').base() + 1, vUint8_t ).asCString(), "012203456789" );

    vUint16_t = 21;
    EXPECT_STREQ( string.getInserted( string.rfind('0').base() + 1, vUint16_t ).asCString(), "012123456789" );

    vUint32_t = 22;
    EXPECT_STREQ( string.getInserted( string.rfind('1').base() + 1, vUint32_t ).asCString(), "012223456789" );

    vUint64_t = 23;
    EXPECT_STREQ( string.getInserted( string.rfind('2').base() + 1, vUint64_t ).asCString(), "012323456789" );

    EXPECT_STREQ( string.getInserted( 8_uz, EDF::String<13>(" twenty-four") ).asCString(), "01234567 twenty-four89" );

    EXPECT_STREQ( string.getInserted( string.end(), EDF::String<13>(" twenty-five") ).asCString(), "0123456789 twenty-five" );
}

TEST(String, Erase) {
    EDF::String<40> string = "Messssage with extraa charrrrracters";

    string.erase( 19_uz );
    EXPECT_STREQ( string.asCString(), "Messssage with extra charrrrracters" );

    string.erase( 2_uz, 4_uz );
    EXPECT_STREQ( string.asCString(), "Message with extra charrrrracters" );

    auto firstRInLastWord = string.find( string.rfind(' ').base(), 'r' );
    firstRInLastWord = string.erase( firstRInLastWord );
    EXPECT_STREQ( string.asCString(), "Message with extra charrrracters" );

    string.erase( firstRInLastWord, string.find( firstRInLastWord, 'a' ) - 1 );
    EXPECT_STREQ( string.asCString(), "Message with extra characters" );
}

TEST(String, GetErased) {
    EDF::String<40> string = "Message with extraa charrrrracters";

    EXPECT_STREQ( string.getErased( 17_uz ).asCString(), "Message with extra charrrrracters" );
    EXPECT_STREQ( string.getErased( 23_uz, 27_uz ).asCString(), "Message with extraa characters" );

    auto firstRInLastWord = string.find( string.rfind(' ').base(), 'r' );
    EXPECT_STREQ( string.getErased( firstRInLastWord ).asCString(), "Message with extraa charrrracters" );
    EXPECT_STREQ( string.getErased( firstRInLastWord, firstRInLastWord + 4 ).asCString(), "Message with extraa characters" );
}

TEST(String, Clear) {
    EDF::String<32> string = "Something";

    string.clear();
    EXPECT_STREQ( string.asCString(), "" );
    EXPECT_EQ( string.length(), 0 );
}

TEST(String, CopyTo) {
    char outputCharBuffer[16];
    EDF::String<32>("Hello").copyTo( outputCharBuffer, sizeof(outputCharBuffer)/sizeof(outputCharBuffer[0]) );
    EXPECT_STREQ( outputCharBuffer, "Hello" );

    EDF::String<8>("World").copyTo( outputCharBuffer );
    EXPECT_STREQ( outputCharBuffer, "World" );

    uint8_t outputUint8_tBuffer[32];
    EDF::String<64>("Hello").copyTo( outputUint8_tBuffer, sizeof(outputUint8_tBuffer)/sizeof(outputUint8_tBuffer[0]) );
    EXPECT_STREQ( reinterpret_cast<const char*>(outputUint8_tBuffer), "Hello" );

    EDF::String<8>("World").copyTo( outputUint8_tBuffer );
    EXPECT_STREQ( reinterpret_cast<const char*>(outputUint8_tBuffer), "World" );
}

TEST(String, Find) {
    //      tens              0000000000111111111122222222
    //      ones              0123456789012345678901234567
    EDF::String<32> string = "abcdefABCDEF0123456789abcdef";

    EXPECT_EQ( string.find( 'A' ), &string[6] );
    EXPECT_EQ( string.find( "defABC" ), &string[3] );
    EXPECT_EQ( string.find( "cde", 3_uz ), &string[2] );
    EXPECT_EQ( string.find( EDF::String<8>("456") ), &string[16] );

    EXPECT_EQ( string.find( string.find('f') + 1, 'f' ), &string[27] );
    EXPECT_EQ( string.find( string.find('A'), "de" ), &string[25] );
    EXPECT_EQ( string.find( string.find('A'), "abc", std::strlen("abc") ), &string[22] );
    EXPECT_EQ( string.find( string.find('A'), EDF::String<8>("cde") ), &string[24] );
}

TEST(String, ReverseFind) {
    //      tens              0000000000111111111122222222
    //      ones              0123456789012345678901234567
    EDF::String<32> string = "abcdefABCDEF0123456789abcdef";

    EXPECT_EQ( &(*string.rfind( 'A' )), &string[6] );
    EXPECT_EQ( &(*string.rfind( "defABC" )), &string[8] );
    EXPECT_EQ( &(*string.rfind( "cde", 3_uz )), &string[26] );
    EXPECT_EQ( &(*string.rfind( EDF::String<8>("456") )), &string[18] );

    EXPECT_EQ( &(*string.rfind( string.rfind('f') + 1, 'f' )), &string[5] );
    EXPECT_EQ( &(*string.rfind( string.rfind('A'), "de" )), &string[4] );
    EXPECT_EQ( &(*string.rfind( string.rfind('A'), "bcd", std::strlen("bcd") )), &string[3] );
    EXPECT_EQ( &(*string.rfind( string.rfind('A'), EDF::String<8>("cde") )), &string[4] );
}

TEST(String, Contains) {
    EDF::String<32> string = "Hello, world!";

    EXPECT_TRUE( string.contains( 'H' ) );
    EXPECT_FALSE( string.contains( 'h' ) );

    EXPECT_TRUE( string.contains( "Hello" ) );
    EXPECT_FALSE( string.contains( "hello" ) );

    EXPECT_TRUE( string.contains( "world", std::strlen("world") ) );
    EXPECT_FALSE( string.contains( "World", 5_uz ) );

    EXPECT_TRUE( string.contains( EDF::String<8>("o, w") ) );
    EXPECT_FALSE( string.contains( EDF::String<64>("o w") ) );
    EXPECT_TRUE( string.contains( EDF::String<32>(string) ) );
}