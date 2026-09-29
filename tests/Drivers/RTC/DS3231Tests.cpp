/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "EDF/Drivers/RTC/DS3231.hpp"
#include "I2CControllerMock.hpp"

#include <gtest/gtest.h>

TEST(DS3231, RegisterDefinitionSeconds) {
    EDF::DS3231_Registers::Seconds seconds( 0xFF );

    EXPECT_EQ( seconds.getOnesPlace(), 0xF );
    EXPECT_EQ( seconds.getTensPlace(), 0x7 );

    seconds = (5 << 4) | (9);
    EXPECT_EQ( seconds.getOnesPlace(), 9 );
    EXPECT_EQ( seconds.getTensPlace(), 5 );

    seconds.setOnesPlace( 0 );
    seconds.setTensPlace( 0 );
    EXPECT_EQ( seconds.getOnesPlace(), 0 );
    EXPECT_EQ( seconds.getTensPlace(), 0 );
}

TEST(DS3231, RegisterDefinitionMinutes) {
    EDF::DS3231_Registers::Minutes minutes( 0xFF );

    EXPECT_EQ( minutes.getOnesPlace(), 0xF );
    EXPECT_EQ( minutes.getTensPlace(), 0x7 );

    minutes = (5 << 4) | (9); // max valid value
    EXPECT_EQ( minutes.getOnesPlace(), 9 );
    EXPECT_EQ( minutes.getTensPlace(), 5 );

    minutes.setOnesPlace( 0 );
    minutes.setTensPlace( 0 );
    EXPECT_EQ( minutes.getOnesPlace(), 0 );
    EXPECT_EQ( minutes.getTensPlace(), 0 );
}

TEST(DS3231, RegisterDefinitionHours) {
    EDF::DS3231_Registers::Hours hours( 0xFF );

    EXPECT_TRUE( hours.is12Hour() );
    EXPECT_TRUE( hours.isPM() );
    EXPECT_FALSE( hours.isAM() );
    EXPECT_EQ( hours.getOnesPlace(), 0xF );
    EXPECT_EQ( hours.getTensPlace(), 0x1 );

    hours = (2 << 4) | (3);
    EXPECT_FALSE( hours.is12Hour() );
    EXPECT_EQ( hours.getOnesPlace(), 3 );
    EXPECT_EQ( hours.getTensPlace(), 2 );

    hours.set12Hour();
    hours.setTensPlace( 1 );
    hours.setOnesPlace( 2 );
    hours.setPM();
    EXPECT_TRUE( hours.is12Hour() );
    EXPECT_TRUE( hours.isPM() );
    EXPECT_FALSE( hours.isAM() );
    EXPECT_EQ( hours.getOnesPlace(), 2 );
    EXPECT_EQ( hours.getTensPlace(), 1 );

    hours.setAM();
    EXPECT_TRUE( hours.is12Hour() );
    EXPECT_FALSE( hours.isPM() );
    EXPECT_TRUE( hours.isAM() );
    EXPECT_EQ( hours.getOnesPlace(), 2 );
    EXPECT_EQ( hours.getTensPlace(), 1 );

    hours.set24Hour();
    EXPECT_FALSE( hours.is12Hour() );
    EXPECT_EQ( hours.getOnesPlace(), 2 );
    EXPECT_EQ( hours.getTensPlace(), 1 );
}

TEST(DS3231, RegisterDefinitionDayOfTheWeek) {
    EDF::DS3231_Registers::DayOfTheWeek dayOfTheWeek( 0xFF );

    EXPECT_EQ( dayOfTheWeek.getDayOfTheWeek(), 0x7 );

    dayOfTheWeek.setDayOfTheWeek( 5 );
    EXPECT_EQ( dayOfTheWeek.getDayOfTheWeek(), 5 );
}

TEST(DS3231, RegisterDefinitionDayOfTheMonth) {
    EDF::DS3231_Registers::DayOfTheMonth dayOfTheMonth( 0xFF );

    EXPECT_EQ( dayOfTheMonth.getOnesPlace(), 0xF );
    EXPECT_EQ( dayOfTheMonth.getTensPlace(), 0x3 );


    dayOfTheMonth.setTensPlace( 3 );
    dayOfTheMonth.setOnesPlace( 1 );
    EXPECT_EQ( dayOfTheMonth.getOnesPlace(), 1 );
    EXPECT_EQ( dayOfTheMonth.getTensPlace(), 3 );
}