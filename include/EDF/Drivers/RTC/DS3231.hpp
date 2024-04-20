/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/I2CController.hpp"
#include "EDF/BitField.hpp"

#include <ctime>

namespace EDF {

namespace DS3231_Registers {

enum class Register : uint8_t {
    Seconds         = 0x00,
    Minutes         = 0x01,
    Hours           = 0x02,
    DayOfTheWeek    = 0x03,
    DayOfTheMonth   = 0x04,
    MonthCentury    = 0x05,
    Year            = 0x06,

    Alarm1Seconds   = 0x07,
    Alarm1Minutes   = 0x08,
    Alarm1Hours     = 0x09,
    Alarm1DayDate   = 0x0A,

    Alarm2Minutes   = 0x0B,
    Alarm2Hours     = 0x0C,
    Alarm2DayDate   = 0x0D,

    Control         = 0x0E,
    ControlStatus   = 0x0F,
    AgingOffset     = 0x10,
    TemperatureMSB  = 0x11,
    TemperatureLSB  = 0x12,
};

class Seconds : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr uint8_t getOnesPlace()                const { return get(0, 4); }
    constexpr void setOnesPlace( uint8_t ones )           { set(0, 4, ones); }

    constexpr uint8_t getTensPlace()                const { return get(4, 3); }
    constexpr void setTensPlace( uint8_t tens )           { set(4, 3, tens ); }
};

using Minutes = Seconds; // exact same register layout

class Hours : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr uint8_t getOnesPlace()                const { return get(0, 4); }
    constexpr void setOnesPlace( uint8_t ones )           { set(0, 4, ones); }

    constexpr uint8_t getTensPlace()                const {
        if( is12Hour() ) {
            return get(4, 1);
        }
        return get(4, 2);
    }
    constexpr void setTensPlace( uint8_t tens )           {
        if( is12Hour() )    set(4, 1, tens);
        else                set(4, 2, tens);
    }

    constexpr bool isPM()                           const { return !isAM(); }
    constexpr void setPM()                                { set(5, 1, true); }
    constexpr bool isAM()                           const {
        EDF_ASSERTD( is12Hour(), "Must be in 12 hour mode to check this bit");
        return !get(5, 1);
    }
    constexpr void setAM()                                { set(5, 1, false); }

    constexpr bool is12Hour()                       const { return get(6, 1); }
    constexpr void set12Hour()                            { set(6, 1, true); }
    constexpr void set24Hour()                            { set(6, 1, false); }
};

class DayOfTheWeek : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr uint8_t getDayOfTheWeek()             const { return get(0, 3); }
    constexpr void setDayOfTheWeek( uint8_t day )         { set(0, 3, day); }
};

class DayOfTheMonth : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr uint8_t getOnesPlace()                const { return get(0, 4); }
    constexpr void setOnesPlace( uint8_t ones )           { set(0, 4, ones); }

    constexpr uint8_t getTensPlace()                const { return get(5, 2); }
    constexpr void setTensPlace( uint8_t tens )           { set(5, 2, tens); }
};

class MonthCentury : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr uint8_t getOnesPlace()                const { return get(0, 4); }
    constexpr void setOnesPlace( uint8_t ones )           { set(0, 4, ones); }

    constexpr uint8_t getTensPlace()                const { return get(5, 1); }
    constexpr void setTensPlace( uint8_t tens )           { set(5, 1, tens); }

    constexpr bool is21stCentury()                  const { return get(7, 1); }
    constexpr void set21stCentury()                       { set(7, 1, true); }
    constexpr void set20thCentury()                       { set(7, 1, false); }
};

class Year : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr uint8_t getOnesPlace()                const { return get(0, 4); }
    constexpr void setOnesPlace( uint8_t ones )           { set(0, 4, ones); }

    constexpr uint8_t getTensPlace()                const { return get(5, 4); }
    constexpr void setTensPlace( uint8_t tens )           { set(5, 4, tens); }
};

class Alarm1Seconds : public Seconds {
public:
    using Seconds::Seconds;

    constexpr bool isA1M1Set()                      const { return get(7, 1); }
    constexpr void setA1M1( bool value )                  { set(7, 1, value); }
};

class Alarm1Minutes : public Minutes {
public:
    using Minutes::Minutes;

    constexpr bool isA1M2Set()                      const { return get(7, 1); }
    constexpr void setA1M2( bool value )                  { set(7, 1, value); }
};

class Alarm1Hours : public Hours {
public:
    using Hours::Hours;

    constexpr bool isA1M3Set()                      const { return get(7, 1); }
    constexpr void setA1M3( bool value )                  { set(7, 1, value); }
};

class Alarm1DayDate : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr uint8_t getOnesPlace()                const { return get(0, 4); }
    constexpr void setOnesPlace( uint8_t ones )           { set(0, 4, ones); }

    constexpr uint8_t getTensPlace()                const {
        if( isDayOfTheWeek() ) {
            return get(5, 1);
        }
        return get(5, 2);
    }
    constexpr void setTensPlace( uint8_t tens )           {
        if( isDayOfTheWeek() )  set(5, 1, tens);
        else                    set(5, 2, tens);
    }

    constexpr bool isDayOfTheWeek()                 const { return get(6, 1); }
    constexpr void setDayOfTheWeek()                      { set(6, 1, true); }
    constexpr bool isDayOfTheMonth()                const { return !isDayOfTheWeek(); }
    constexpr void setDayOfTheMonth()                     { set(6, 1, false); }

    constexpr bool isA1M4Set()                      const { return get(7, 1); }
    constexpr void setA1M4( bool value )                  { set(7, 1, value); }
};

class Alarm2Minutes : public Alarm1Minutes {
private: /* Hide these */
    constexpr bool isA1M2Set()                      const { return 0; }
    constexpr void setA1M2( bool value )                  { (void)value; }
public:
    using Alarm1Minutes::Alarm1Minutes;

    constexpr bool isA2M2Set()                      const { return Alarm1Minutes::isA1M2Set(); }
    constexpr void setA2M2( bool value )                  { Alarm1Minutes::setA1M2(value); }
};

class Alarm2Hours : public Alarm1Hours {
private: /* Hide these */
    constexpr bool isA1M3Set()                      const { return 0; }
    constexpr void setA1M3( bool value )                  { (void)value; }
public:
   using Alarm1Hours::Alarm1Hours;

    constexpr bool isA2M3Set()                      const { return Alarm1Hours::isA1M3Set(); }
    constexpr void setA2M3( bool value )                  { Alarm1Hours::setA1M3(value); }
};

class Alarm2DayDate : public Alarm1DayDate {
private: /* Hide these */
    constexpr bool isA1M4Set()                      const { return 0; }
    constexpr void setA1M4( bool value )                  { (void)value; }
public:
   using Alarm1DayDate::Alarm1DayDate;

    constexpr bool isA2M4Set()                      const { return Alarm1DayDate::isA1M4Set(); }
    constexpr void setA2M4( bool value )                  { Alarm1DayDate::setA1M4(value); }
};

class ControlStatus : public BitField16 {
public:
    enum class SWR : uint8_t { // SquareWaveRate
        R1_Hz       = 0x00, // 1      Hz
        R1_024_kHz  = 0x01, // 1.024 kHz
        R4_096_kHz  = 0x02, // 4.096 kHz
        R8_192_kHz  = 0x03, // 8.192 kHz
    };
public:
   using BitField16::BitField16;

    constexpr bool isA1InterruptEnabled()           const { return get(0, 1); }
    constexpr void setA1Interrupt( bool enable )          { set(0, 1, enable); }

    constexpr bool isA2InterruptEnabled()           const { return get(1, 1); }
    constexpr void setA2Interrupt( bool enable )          { set(1, 1, enable); }

    constexpr bool isAlarmInterruptEnabled()        const { return get(2, 1); }
    constexpr void setAlarmInterrupt( bool enable )       { set(2, 1, enable);  }

    constexpr SWR getSquareWaveRate()               const { return static_cast<SWR>(get(3, 2)); }
    constexpr void setSquareWaveRate( SWR r )             { set(3, 2, static_cast<uint8_t>(r)); }

    constexpr bool isTemperatureConverting()        const { return get(5, 1); }
    constexpr bool startTemperatureConversion()           { // returns false if busy doing a conversion
        if( !isTemperatureConverting() && !isBusy() ) {
            set(5, 1, true);
            return true;
        }
        return false;
    }

    constexpr bool isSquareWaveEnabled()            const { return get(6, 1) && !isAlarmInterruptEnabled(); }
    constexpr void setSquareWave( bool enable )           { set(6, 1, enable); setAlarmInterrupt(!enable); }

    constexpr bool isOscillatorEnabled()            const { return get(7, 1); }
    constexpr void setOscillator( bool enable )           { set(7, 1, enable); if( enable ) clearOscillatorStopped(); }

    constexpr bool isAlarm1Triggered()              const { return get(8, 1); }
    constexpr void clearAlarm1Triggered()                 { set(8, 1, 0); }

    constexpr bool isAlarm2Triggered()              const { return get(9, 1); }
    constexpr void clearAlarm2Triggered()                 { set(9, 1, 0); }

    constexpr bool isBusy()                         const { return get(10, 1); }

    constexpr bool is32kHzOutputEnabled()           const { return get(11, 1); }
    constexpr void set32kHzOutput( bool enable )          { set(11, 1, enable); }

    constexpr bool isOscillatorStopped()            const { return get(15, 1); }
    constexpr void clearOscillatorStopped()               { set(15, 1, 0); }
};

class AgingOffset : public BitField8 {
public:
    using BitField8::BitField8;

    constexpr int8_t getOffset()                    const { return get(0, 8); }
    constexpr void setOffset( int8_t offset )             { set(0, 8, offset); }
};

class Temperature : public BitField16 {
public:
    using BitField16::BitField16;

    constexpr uint8_t getFraction()                 const { return get(6, 2); }
    constexpr int8_t getWhole()                     const { return get(8, 8); }
};

} /* DS3231_Registers */

class DS3231 {
private:
    static constexpr uint8_t address_7bit = 0x68;
private:
    using Register      = DS3231_Registers::Register;

    using Seconds       = DS3231_Registers::Seconds;
    using Minutes       = DS3231_Registers::Minutes;
    using Hours         = DS3231_Registers::Hours;
    using DayOfTheWeek  = DS3231_Registers::DayOfTheWeek;
    using DayOfTheMonth = DS3231_Registers::DayOfTheMonth;
    using MonthCentury  = DS3231_Registers::MonthCentury;
    using Year          = DS3231_Registers::Year;

    using Alarm1Seconds = DS3231_Registers::Alarm1Seconds;
    using Alarm1Minutes = DS3231_Registers::Alarm1Minutes;
    using Alarm1Hours   = DS3231_Registers::Alarm1Hours;
    using Alarm1DayDate = DS3231_Registers::Alarm1DayDate;

    using Alarm2Minutes = DS3231_Registers::Alarm2Minutes;
    using Alarm2Hours   = DS3231_Registers::Alarm2Hours;
    using Alarm2DayDate = DS3231_Registers::Alarm2DayDate;

    using ControlStatus = DS3231_Registers::ControlStatus;
    using AgingOffset   = DS3231_Registers::AgingOffset;
    using Temperature   = DS3231_Registers::Temperature;
    struct CurrentTime {
        Seconds         seconds;
        Minutes         minutes;
        Hours           hours;
        DayOfTheWeek    dayOfTheWeek;
        DayOfTheMonth   dayOfTheMonth;
        MonthCentury    monthCentury;
        Year            year;
        CurrentTime() = default;
        CurrentTime( const std::tm& t );
        std::tm toSTDTime() const;
    };
    struct Alarm1 {
        Alarm1Seconds   seconds;
        Alarm1Minutes   minutes;
        Alarm1Hours     hours;
        Alarm1DayDate   dayDate;
        Alarm1() = default;
        Alarm1( const std::tm& t, bool useDayOfWeek );
        std::tm toSTDTime() const;
    };
    struct Alarm2 {
        Alarm2Minutes   minutes;
        Alarm2Hours     hours;
        Alarm2DayDate   dayDate;
        Alarm2() = default;
        Alarm2( const std::tm& t, bool useDayOfWeek );
        std::tm toSTDTime() const;
    };
public:
    enum class Alarm1Rate {                //A1M1234DY/DT
        DayOfTheWeek_Hours_Minutes_Seconds  = 0b00000,
        DayOfTheMonth_Hours_Minutes_Seconds = 0b00001,
        Hours_Minutes_Seconds               = 0b00011,
        Minutes_Seconds                     = 0b00111,
        Seconds                             = 0b01111,
        OncePerSecond                       = 0b11111,
    };
    enum class Alarm2Rate {                //A2M234DY/DT
        DayOfTheWeek_Hours_Minutes          = 0b0000,
        DayOfTheMonth_Hours_Minutes         = 0b0001,
        Hours_Minutes                       = 0b0011,
        Minutes                             = 0b0111,
        OncePerMinute                       = 0b1111,
    };
    struct CFG{
        using SquareWaveRate = ControlStatus::SWR;

        bool hourMode12;                // 12 hour clock (true), 24 hour clock (false)
        bool oscillatorOnWhenVbat;      // oscillator still on while using Vbat (true)
        bool outputSquareWaveWhenVbat;  // use INT/SQW pin as square wave output
        SquareWaveRate squareWaveRate;  // ignored if outputSquareWave is false
        bool enableAlarmInterrupts;     // enable Alarm interrupt output pin
        bool enable32kHzOutput;         // Controls the 32kHz pin

        CFG() :
            hourMode12( true ),
            oscillatorOnWhenVbat( false ),
            outputSquareWaveWhenVbat( false ),
            squareWaveRate( SquareWaveRate::R8_192_kHz ),
            enableAlarmInterrupts( true ),
            enable32kHzOutput( true )
        {}
    };
private:
    uint8_t readRegister( Register reg );
    void writeRegister( Register reg, uint8_t value );
    uint16_t readRegister16( Register reg );
    void writeRegister16( Register reg, uint16_t value );

    CurrentTime readCurrentTime();
    void writeCurrentTime( const CurrentTime& time );

    Alarm1 readAlarm1();
    void writeAlarm1( const Alarm1& alarm );
    void writeAlarm1Rate( Alarm1Rate rate );

    Alarm2 readAlarm2();
    void writeAlarm2( const Alarm2& alarm );
    void writeAlarm2Rate( Alarm2Rate rate );

    ControlStatus readControlStatus();
    void writeControLStatus( ControlStatus controlStatus );

    AgingOffset readAgingOffset();
    void writeAgingOffset( AgingOffset agingOffset );

    Temperature readTemperature();
private:
    I2CController& i2c;
public:
    DS3231( I2CController& i2c ) : i2c(i2c) {}
    void init( const CFG& config = CFG() );

    std::tm getCurrentTime()                                    { return readCurrentTime().toSTDTime(); }
    void setCurrentTime( const std::tm& time )                  { writeCurrentTime( time ); }

    std::tm getAlarm1()                                         { return readAlarm1().toSTDTime(); }
    void setAlarm1( const std::tm& time, bool useDayOfWeek )    { writeAlarm1( Alarm1(time, useDayOfWeek) ); }
    void setAlarm1Rate( Alarm1Rate rate )                       { writeAlarm1Rate( rate ); }
    bool isAlarm1InterruptTriggered()                           { return readControlStatus().isAlarm1Triggered(); }
    bool isAlarm1InterruptEnabled()                             { return readControlStatus().isA1InterruptEnabled(); }
    void setAlarm1Interrupt( bool enable );

    std::tm getAlarm2()                                         { return readAlarm2().toSTDTime(); }
    void setAlarm2( const std::tm& time, bool useDayOfWeek  )   { writeAlarm2( Alarm2(time, useDayOfWeek) ); }
    void setAlarm2Rate( Alarm2Rate rate )                       { writeAlarm2Rate( rate ); }
    bool isAlarm2InterruptTriggered()                           { return readControlStatus().isAlarm2Triggered(); }
    bool isAlarm2InterruptEnabled()                             { return readControlStatus().isA2InterruptEnabled(); }
    void setAlarm2Interrupt( bool enable );

    int8_t getAgingOffset()                                     { return readAgingOffset().getOffset(); }
    void setAgingOffset( int8_t value );

    int32_t getTemperature_C_x100( bool manualReading = false );

    void set32KhzOutput( bool enable );
    void setSquareWaveOutput( bool enable, CFG::SquareWaveRate rate = CFG::SquareWaveRate::R8_192_kHz );

    void clearAlarmInterrupts();
};

} /* EDF */