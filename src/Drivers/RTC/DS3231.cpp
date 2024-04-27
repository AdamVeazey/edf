/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/Drivers/RTC/DS3231.hpp"
#include "EDF/Vector.hpp"
#include "EDF/Math.hpp"

namespace EDF {

DS3231::CurrentTime::
CurrentTime( const std::tm& t ) {
    seconds.setOnesPlace( t.tm_sec / 10 );
    seconds.setTensPlace( t.tm_sec % 10 );

    minutes.setTensPlace( t.tm_min / 10 );
    minutes.setOnesPlace( t.tm_min % 10 );

    auto hour = t.tm_hour;
    if( hours.is12Hour() ) {
        if( hour > 12 ) {
            hour -= 12;
            hours.setPM();
        }
        else {
            hours.setAM();
        }
        hours.setTensPlace( hour / 10 );
        hours.setOnesPlace( hour % 10 );
    }
    else {
        hours.setTensPlace( hour / 10 );
        hours.setOnesPlace( hour % 10 );
    }

    dayOfTheWeek.setDayOfTheWeek( t.tm_wday + 1 );

    dayOfTheMonth.setTensPlace( t.tm_mday / 10 );
    dayOfTheMonth.setOnesPlace( t.tm_mday % 10 );

    auto yearTmp = t.tm_year + 1900;
    if( yearTmp > 1999 ) {
        monthCentury.set21stCentury();
    }
    else {
        monthCentury.set20thCentury();
    }
    auto month = t.tm_mon + 1;
    monthCentury.setTensPlace( month / 10 );
    monthCentury.setOnesPlace( month % 10 );

    yearTmp = yearTmp % 100;
    year.setTensPlace( yearTmp / 10 );
    year.setOnesPlace( yearTmp % 10 );
}

std::tm DS3231::CurrentTime::
toSTDTime() const {
    std::tm time;
    time.tm_sec = seconds.getTensPlace() * 10 + seconds.getOnesPlace();
    time.tm_min = minutes.getTensPlace() * 10 + minutes.getOnesPlace();
    time.tm_hour = hours.getTensPlace() * 10 + hours.getOnesPlace();
    if( hours.is12Hour() && hours.isPM() ) {
        time.tm_hour += 12;
    }
    time.tm_mday = dayOfTheMonth.getTensPlace() * 10 + dayOfTheMonth.getOnesPlace();
    time.tm_mon = monthCentury.getTensPlace() * 10 + monthCentury.getOnesPlace();
    --time.tm_mon;
    time.tm_year = year.getTensPlace() * 10 + year.getOnesPlace();
    time.tm_year += monthCentury.is21stCentury() * 100;
    time.tm_wday = dayOfTheWeek.getDayOfTheWeek() - 1;
    time.tm_yday = 0; // TODO: okay but what do I do about this?
    time.tm_isdst = -1;
    return time;
}

/************************************************************/

DS3231::Alarm1::
Alarm1( const std::tm& t, bool useDayOfWeek ) {
    CurrentTime tmp(t);
    seconds.set(0, 7, tmp.seconds.get(0, 7));
    minutes.set(0, 7, tmp.minutes.get(0, 7));
    hours.set(0, 7, tmp.hours.get(0, 7));
    if( useDayOfWeek ) {
        dayDate.setDayOfTheWeek();
        dayDate.set(0, 6, tmp.dayOfTheWeek.get(0, 6));
    }
    else {
        dayDate.setDayOfTheMonth();
        dayDate.set(0, 5, tmp.dayOfTheMonth.get(0, 5));
    }
}

std::tm DS3231::Alarm1::
toSTDTime() const {
    CurrentTime tmp;
    tmp.seconds.set(0, 7, seconds.get(0, 7));
    tmp.minutes.set(0, 7, minutes.get(0, 7));
    tmp.hours.set(0, 7, hours.get(0, 7));
    if( dayDate.isDayOfTheWeek() ) {
        tmp.dayOfTheWeek.set(0, 6, dayDate.get(0, 6));
    }
    else {
        tmp.dayOfTheMonth.set(0, 5, dayDate.get(0, 5));
    }
    return tmp.toSTDTime();
}

/************************************************************/

DS3231::Alarm2::
Alarm2( const std::tm& t, bool useDayOfWeek ) {
    Alarm1 tmp(t, useDayOfWeek);
    minutes.set(0, 7, tmp.minutes.get(0, 7));
    hours.set(0, 7, tmp.hours.get(0, 7));
    dayDate.set(0, 7, tmp.dayDate.get(0, 7));
}

std::tm DS3231::Alarm2::
toSTDTime() const {
    CurrentTime tmp;
    tmp.minutes.set(0, 7, minutes.get(0, 7));
    tmp.hours.set(0, 7, hours.get(0, 7));
    if( dayDate.isDayOfTheWeek() ) {
        tmp.dayOfTheWeek.set(0, 6, dayDate.get(0, 6));
    }
    else {
        tmp.dayOfTheMonth.set(0, 5, dayDate.get(0, 5));
    }
    return tmp.toSTDTime();
}

/************************************************************/

uint8_t DS3231::
readRegister( Register reg ) {
    uint8_t dataInOut = static_cast<uint8_t>(reg);
    i2c.transfer(
        address_7bit,
        &dataInOut, sizeof(dataInOut),
        &dataInOut, sizeof(dataInOut)
    );
    return dataInOut;
}

void DS3231::
writeRegister( Register reg, uint8_t value ) {
    uint8_t data[] = { static_cast<uint8_t>(reg), value };
    i2c.transfer( address_7bit, data, EDF::nElements(data) );
}

uint16_t DS3231::
readRegister16( Register reg ) {
    uint8_t data[2] = { static_cast<uint8_t>(reg), 0 };
    i2c.transfer( address_7bit, data, 1, data, EDF::nElements(data) );
    return (static_cast<uint16_t>(data[0]) << 8) | data[1];
}

void DS3231::
writeRegister16( Register reg, uint16_t value ) {
    uint8_t data[] = {
        static_cast<uint8_t>(reg),
        static_cast<uint8_t>(value >> 8),
        static_cast<uint8_t>(value),
    };
    i2c.transfer( address_7bit, data, EDF::nElements(data) );
}

DS3231::CurrentTime DS3231::
readCurrentTime() {
    CurrentTime time;
    uint8_t dataAddress = static_cast<uint8_t>(Register::Seconds);
    i2c.transfer(
        address_7bit,
        &dataAddress, sizeof( dataAddress ),
        reinterpret_cast<uint8_t*>( &time ), sizeof( time )
    );
    return time;
}

void DS3231::
writeCurrentTime( const CurrentTime& time ) {
    EDF::Vector<uint8_t, sizeof(CurrentTime)+1> data;
    data.pushBack( static_cast<uint8_t>(Register::Seconds) );
    for( std::size_t k = 0; k < sizeof(CurrentTime); ++k ){
        data.pushBack( (reinterpret_cast<const uint8_t*>(&time))[k] );
    }
    i2c.transfer( address_7bit, data.data(), data.length() );
}

DS3231::Alarm1 DS3231::
readAlarm1() {
    Alarm1 alarm1;
    uint8_t dataAddress = static_cast<uint8_t>(Register::Alarm1Seconds);
    i2c.transfer(
        address_7bit,
        &dataAddress, sizeof( dataAddress ),
        reinterpret_cast<uint8_t*>( &alarm1 ), sizeof( alarm1 )
    );
    return alarm1;
}

void DS3231::
writeAlarm1( const Alarm1& alarm ) {
    EDF::Vector<uint8_t, sizeof(Alarm1)+1> data;
    data.pushBack( static_cast<uint8_t>(Register::Alarm1Seconds) );
    for( std::size_t k = 0; k < sizeof(Alarm1); ++k ){
        data.pushBack( (reinterpret_cast<const uint8_t*>(&alarm))[k] );
    }
    i2c.transfer( address_7bit, data.data(), data.length() );

    ControlStatus ctrl = readControlStatus();
    ctrl.setA1Interrupt( true );
    writeControLStatus( ctrl );
}

void DS3231::
writeAlarm1Rate( Alarm1Rate rate ) {
    Alarm1 alarm = readAlarm1();
    switch( rate ) {
    case Alarm1Rate::DayOfTheWeek_Hours_Minutes_Seconds:
        alarm.seconds.setA1M1( false );
        alarm.minutes.setA1M2( false );
        alarm.hours.setA1M3( false );
        alarm.dayDate.setA1M4( false );
        alarm.dayDate.setDayOfTheWeek();
        break;
    case Alarm1Rate::DayOfTheMonth_Hours_Minutes_Seconds:
        alarm.seconds.setA1M1( false );
        alarm.minutes.setA1M2( false );
        alarm.hours.setA1M3( false );
        alarm.dayDate.setA1M4( false );
        alarm.dayDate.setDayOfTheMonth();
        break;
    case Alarm1Rate::Hours_Minutes_Seconds:
        alarm.seconds.setA1M1( false );
        alarm.minutes.setA1M2( false );
        alarm.hours.setA1M3( false );
        alarm.dayDate.setA1M4( true );
        break;
    case Alarm1Rate::Minutes_Seconds:
        alarm.seconds.setA1M1( false );
        alarm.minutes.setA1M2( false );
        alarm.hours.setA1M3( true );
        alarm.dayDate.setA1M4( true );
        break;
    case Alarm1Rate::Seconds:
        alarm.seconds.setA1M1( false );
        alarm.minutes.setA1M2( true );
        alarm.hours.setA1M3( true );
        alarm.dayDate.setA1M4( true );
        break;
    case Alarm1Rate::OncePerSecond:
        alarm.seconds.setA1M1( true );
        alarm.minutes.setA1M2( true );
        alarm.hours.setA1M3( true );
        alarm.dayDate.setA1M4( true );
        break;
    }
    writeAlarm1( alarm );
}

DS3231::Alarm2 DS3231::
readAlarm2() {
    Alarm2 alarm2;
    uint8_t dataAddress = static_cast<uint8_t>(Register::Alarm2Minutes);
    i2c.transfer(
        address_7bit,
        &dataAddress, sizeof( dataAddress ),
        reinterpret_cast<uint8_t*>( &alarm2 ), sizeof( alarm2 )
    );
    return alarm2;
}

void DS3231::
writeAlarm2( const Alarm2& alarm ) {
    EDF::Vector<uint8_t, sizeof(Alarm2)+1> data;
    data.pushBack( static_cast<uint8_t>(Register::Alarm2Minutes) );
    for( std::size_t k = 0; k < sizeof(Alarm2); ++k ){
        data.pushBack( (reinterpret_cast<const uint8_t*>(&alarm))[k] );
    }
    i2c.transfer( address_7bit, data.data(), data.length() );

    ControlStatus ctrl = readControlStatus();
    ctrl.setA2Interrupt( true );
    writeControLStatus( ctrl );
}

void DS3231::
writeAlarm2Rate( Alarm2Rate rate ) {
    Alarm2 alarm = readAlarm2();
    switch( rate ) {
    case Alarm2Rate::DayOfTheWeek_Hours_Minutes:
        alarm.minutes.setA2M2( false );
        alarm.hours.setA2M3( false );
        alarm.dayDate.setA2M4( false );
        alarm.dayDate.setDayOfTheWeek();
        break;
    case Alarm2Rate::DayOfTheMonth_Hours_Minutes:
        alarm.minutes.setA2M2( false );
        alarm.hours.setA2M3( false );
        alarm.dayDate.setA2M4( false );
        alarm.dayDate.setDayOfTheMonth();
        break;
    case Alarm2Rate::Hours_Minutes:
        alarm.minutes.setA2M2( false );
        alarm.hours.setA2M3( false );
        alarm.dayDate.setA2M4( true );
        break;
    case Alarm2Rate::Minutes:
        alarm.minutes.setA2M2( true );
        alarm.hours.setA2M3( true );
        alarm.dayDate.setA2M4( true );
        break;
    case Alarm2Rate::OncePerMinute:
        alarm.minutes.setA2M2( true );
        alarm.hours.setA2M3( true );
        alarm.dayDate.setA2M4( true );
        break;
    }
    writeAlarm2( alarm );
}

DS3231::ControlStatus DS3231::
readControlStatus() {
    return readRegister16( Register::Control );
}

void DS3231::
writeControLStatus( ControlStatus controlStatus ) {
    writeRegister16( Register::Control, controlStatus );
}

DS3231::AgingOffset DS3231::
readAgingOffset() {
    return readRegister( Register::AgingOffset );
}

void DS3231::
writeAgingOffset( AgingOffset agingOffset ) {
    writeRegister( Register::AgingOffset, agingOffset );
}

DS3231::Temperature DS3231::
readTemperature() {
    return readRegister16( Register::TemperatureMSB );
}

void DS3231::
init( const CFG& config ) {
    Hours hours = readRegister( Register::Hours );
    Alarm1Hours hoursAlarm1 = readRegister( Register::Alarm1Hours );
    Alarm2Hours hoursAlarm2 = readRegister( Register::Alarm2Hours );
    if( config.hourMode12 ) {
        hours.set12Hour();
        hoursAlarm1.set12Hour();
        hoursAlarm2.set12Hour();
        if( (hours.getTensPlace() * 10 + hours.getOnesPlace()) > 12 ) {
            hours.setPM();
        }
        if( (hoursAlarm1.getTensPlace() * 10 + hoursAlarm1.getOnesPlace()) > 12 ) {
            hoursAlarm1.setPM();
        }
        if( (hoursAlarm2.getTensPlace() * 10 + hoursAlarm2.getOnesPlace()) > 12 ) {
            hoursAlarm2.setPM();
        }
    }
    else {
        hours.set24Hour();
        hoursAlarm1.set24Hour();
        hoursAlarm2.set24Hour();
    }
    writeRegister( Register::Hours, hours );
    writeRegister( Register::Alarm1Hours, hoursAlarm1 );
    writeRegister( Register::Alarm2Hours, hoursAlarm2 );

    ControlStatus ctrl = readControlStatus();
    ctrl.setOscillator( config.oscillatorOnWhenVbat );
    ctrl.setSquareWave( config.outputSquareWaveWhenVbat );
    ctrl.setSquareWaveRate( config.squareWaveRate );
    ctrl.setAlarmInterrupt( config.enableAlarmInterrupts );
    ctrl.set32kHzOutput( config.enable32kHzOutput );
    writeControLStatus( ctrl );
}

void DS3231::
setAlarm1Interrupt( bool enable ) {
    ControlStatus ctrl = readControlStatus();
    ctrl.setA1Interrupt( enable );
    writeControLStatus( ctrl );
}

void DS3231::
setAlarm2Interrupt( bool enable ) {
    ControlStatus ctrl = readControlStatus();
    ctrl.setA2Interrupt( enable );
    writeControLStatus( ctrl );
}

void DS3231::
setAgingOffset( int8_t value ) {
    writeAgingOffset( value );
    getTemperature_C_x100( true );
}

int32_t DS3231::
getTemperature_C_x100( bool manualReading ) {
    if( manualReading ) {
        bool conversionStarted = false;
        for( size_t k = 0; k < 100; ++k ) { // TODO: arbitrary retry number
            ControlStatus status = readControlStatus();
            conversionStarted = status.startTemperatureConversion();
            if( conversionStarted ) {
                break;
            }
        }
        if( conversionStarted ) {
            // wait for reading to finish
            for( size_t k = 0; k < 100; ++k ) { // TODO: arbitrary retry number
                ControlStatus status = readControlStatus();
                if( !status.isTemperatureConverting() && !status.isBusy() ) {
                    break;
                }
            }
        }
    }
    Temperature temp = readTemperature();
    return temp.getWhole() * 100 + (temp.getFraction() * 25);
}

void DS3231::
set32KhzOutput( bool enable ) {
    ControlStatus ctrl = readControlStatus();
    ctrl.set32kHzOutput( enable );
    writeControLStatus( ctrl );
}

void DS3231::
setSquareWaveOutput( bool enable, CFG::SquareWaveRate rate ) {
    ControlStatus ctrl = readControlStatus();
    ctrl.setSquareWave( enable );
    ctrl.setSquareWaveRate( rate );
    writeControLStatus( ctrl );
}

void DS3231::
clearAlarmInterrupts() {
    ControlStatus status = readRegister16( Register::Control );
    if( status.isAlarm1Triggered() ) {
        status.clearAlarm1Triggered();
    }
    if( status.isAlarm2Triggered() ) {
        status.clearAlarm2Triggered();
    }
    writeRegister16( Register::Control, status );
}

} /* EDF */