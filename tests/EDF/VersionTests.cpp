/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Version.hpp>

#include <gtest/gtest.h>

TEST(Version, Initialization) {
    EDF::Version versionDefault;
    EXPECT_STREQ( versionDefault.asCString(), "0.0.0" );
    EXPECT_TRUE( versionDefault.asString().equals( EDF::Version::String("0.0.0") ) );
    EXPECT_EQ( versionDefault.asNumber(), 0 );
    EXPECT_EQ( versionDefault.getMajor(), 0 );
    EXPECT_EQ( versionDefault.getMinor(), 0 );
    EXPECT_EQ( versionDefault.getPatch(), 0 );

    EDF::Version versionFromString( "1.2.3" );
    EXPECT_STREQ( versionFromString.asCString(), "1.2.3" );
    EXPECT_TRUE( versionFromString.asString().equals( EDF::Version::String("1.2.3") ) );
    EXPECT_EQ( versionFromString.asNumber(), 1002003 );
    EXPECT_EQ( versionFromString.getMajor(), 1 );
    EXPECT_EQ( versionFromString.getMinor(), 2 );
    EXPECT_EQ( versionFromString.getPatch(), 3 );

    static constexpr char VERSION[] = "100.200.300";
    EDF::Version versionFromCharArray( VERSION );
    EXPECT_STREQ( versionFromCharArray.asCString(), "100.200.300" );
    EXPECT_TRUE( versionFromCharArray.asString().equals( EDF::Version::String("100.200.300") ) );
    EXPECT_EQ( versionFromCharArray.asNumber(), 100200300 );
    EXPECT_EQ( versionFromCharArray.getMajor(), 100 );
    EXPECT_EQ( versionFromCharArray.getMinor(), 200 );
    EXPECT_EQ( versionFromCharArray.getPatch(), 300 );

    EDF::Version versionFromMaxString( EDF::String<20>("999.999.999") );
    EXPECT_STREQ( versionFromMaxString.asCString(), "999.999.999" );
    EXPECT_TRUE( versionFromMaxString.asString().equals( EDF::Version::String("999.999.999") ) );
    EXPECT_EQ( versionFromMaxString.asNumber(), 999999999 );
    EXPECT_EQ( versionFromMaxString.getMajor(), 999 );
    EXPECT_EQ( versionFromMaxString.getMinor(), 999 );
    EXPECT_EQ( versionFromMaxString.getPatch(), 999 );

    EDF::Version versionFromNumber( 10020030 );
    EXPECT_STREQ( versionFromNumber.asCString(), "10.20.30" );
    EXPECT_TRUE( versionFromNumber.asString().equals( EDF::Version::String("10.20.30") ) );
    EXPECT_EQ( versionFromNumber.asNumber(), 10020030 );
    EXPECT_EQ( versionFromNumber.getMajor(), 10 );
    EXPECT_EQ( versionFromNumber.getMinor(), 20 );
    EXPECT_EQ( versionFromNumber.getPatch(), 30 );

    EDF::Version versionFromMaxNumber( 999999999 );
    EXPECT_STREQ( versionFromMaxNumber.asCString(), "999.999.999" );
    EXPECT_TRUE( versionFromMaxNumber.asString().equals( EDF::Version::String("999.999.999") ) );
    EXPECT_EQ( versionFromMaxNumber.asNumber(), 999999999 );
    EXPECT_EQ( versionFromMaxNumber.getMajor(), 999 );
    EXPECT_EQ( versionFromMaxNumber.getMinor(), 999 );
    EXPECT_EQ( versionFromMaxNumber.getPatch(), 999 );
}

TEST(Version, GetMajor) {
    EDF::Version version;
    EXPECT_EQ( version.getMajor(), 0 );

    version = "1.0.0";
    EXPECT_EQ( version.getMajor(), 1 );

    version = 2000000;
    EXPECT_EQ( version.getMajor(), 2 );

    version = "999.0.0";
    EXPECT_EQ( version.getMajor(), 999 );

    version = 999000000;
    EXPECT_EQ( version.getMajor(), 999 );
}

TEST(Version, GetMinor) {
    EDF::Version version;
    EXPECT_EQ( version.getMinor(), 0 );

    version = "0.1.0";
    EXPECT_EQ( version.getMinor(), 1 );

    version = 2000;
    EXPECT_EQ( version.getMinor(), 2 );

    version = "0.999.0";
    EXPECT_EQ( version.getMinor(), 999 );

    version = 999000;
    EXPECT_EQ( version.getMinor(), 999 );
}

TEST(Version, GetPatch) {
    EDF::Version version;
    EXPECT_EQ( version.getPatch(), 0 );

    version = "0.0.1";
    EXPECT_EQ( version.getPatch(), 1 );

    version = 2;
    EXPECT_EQ( version.getPatch(), 2 );

    version = "0.0.999";
    EXPECT_EQ( version.getPatch(), 999 );

    version = 999;
    EXPECT_EQ( version.getPatch(), 999 );
}

TEST(Version, AsNumber) {
    EDF::Version version;
    EXPECT_EQ( version.asNumber(), 0 );

    version = "1.1.1";
    EXPECT_EQ( version.asNumber(), 1001001 );

    version = 2002002;
    EXPECT_EQ( version.asNumber(), 2002002 );

    version = "999.999.999";
    EXPECT_EQ( version.asNumber(), 999999999 );

    version = 999999999;
    EXPECT_EQ( version.asNumber(), 999999999 );
}

TEST(Version, AsString) {
    using String = EDF::Version::String;
    EDF::Version version;
    EXPECT_TRUE( version.asString().equals( String( "0.0.0" ) ) );

    version = "1.1.1";
    EXPECT_TRUE( version.asString().equals( String( "1.1.1" ) ) );

    version = 2002002;
    EXPECT_TRUE( version.asString().equals( String( "2.2.2" ) ) );

    version = "999.999.999";
    EXPECT_TRUE( version.asString().equals( String( "999.999.999" ) ) );

    version = 999999999;
    EXPECT_TRUE( version.asString().equals( String( "999.999.999" ) ) );
}

TEST(Version, AsCString) {
    EDF::Version version;
    EXPECT_STREQ( version.asCString(), "0.0.0" );

    version = "1.1.1";
    EXPECT_STREQ( version.asCString(), "1.1.1" );

    version = 2002002;
    EXPECT_STREQ( version.asCString(), "2.2.2" );

    version = "999.999.999";
    EXPECT_STREQ( version.asCString(), "999.999.999" );

    version = 999999999;
    EXPECT_STREQ( version.asCString(), "999.999.999" );
}

TEST(Version, ComparisonThisRHS) {
    EXPECT_TRUE( EDF::Version( "0.0.0" ) < EDF::Version( "0.0.1" ) );
    EXPECT_TRUE( EDF::Version( "0.0.1" ) > EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) >= EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) <= EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) == EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) != EDF::Version( "0.0.1" ) );

    EXPECT_TRUE( EDF::Version( "0.0.0" ) < "0.0.1" );
    EXPECT_TRUE( EDF::Version( "0.0.1" ) > "0.0.0" );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) >= "0.0.0" );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) <= "0.0.0" );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) == "0.0.0" );
    EXPECT_TRUE( EDF::Version( "0.0.0" ) != "0.0.1" );
}

TEST(Version, ComparisonLHSThis) {
    EXPECT_TRUE( "0.0.0" < EDF::Version( "0.0.1" ) );
    EXPECT_TRUE( "0.0.1" > EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( "0.0.0" >= EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( "0.0.0" <= EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( "0.0.0" == EDF::Version( "0.0.0" ) );
    EXPECT_TRUE( "0.0.1" != EDF::Version( "0.0.0" ) );
}