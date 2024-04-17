/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/ADC.hpp"
#include "EDF/BitField.hpp"
#include "EDF/Vector.hpp"

#include "stm32c0xx_hal.h"

#undef ADC // ST defines this for legacy reasons. If you need this defined, refactor or don't use this.

class ADCChannel;
class ADCScanGroup;

class ADC : public EDF::ADC {
public:
    struct Pin {
        GPIO_TypeDef* port;
        uint16_t pin;
    };
    enum class Channel : uint32_t {
        IN0         = ADC_CHANNEL_0,
        IN1         = ADC_CHANNEL_1,
        IN2         = ADC_CHANNEL_2,
        IN3         = ADC_CHANNEL_3,
        IN4         = ADC_CHANNEL_4,
        IN5         = ADC_CHANNEL_5,
        IN6         = ADC_CHANNEL_6,
        IN7         = ADC_CHANNEL_7,
        IN8         = ADC_CHANNEL_8,
        IN9         = ADC_CHANNEL_9,
        IN10        = ADC_CHANNEL_10,
        IN11        = ADC_CHANNEL_11,
        IN12        = ADC_CHANNEL_12,
        IN13        = ADC_CHANNEL_13,
        IN14        = ADC_CHANNEL_14,
        IN15        = ADC_CHANNEL_15,
        IN16        = ADC_CHANNEL_16,
        IN17        = ADC_CHANNEL_17,
        IN18        = ADC_CHANNEL_18,
        IN19        = ADC_CHANNEL_19,
        IN20        = ADC_CHANNEL_20,
        IN21        = ADC_CHANNEL_21,
        IN22        = ADC_CHANNEL_22,
        VREFINT     = ADC_CHANNEL_VREFINT,
        TEMPSENSOR  = ADC_CHANNEL_TEMPSENSOR,
        VDDA        = ADC_CHANNEL_VDDA,
        VSSA        = ADC_CHANNEL_VSSA,
    };
    enum class Event {
        EndOfSample = ADC_EOSMP_EVENT,
        WD1         = ADC_AWD1_EVENT,
        WD2         = ADC_AWD2_EVENT,
        WD3         = ADC_AWD3_EVENT,
        Overrun     = ADC_OVR_EVENT,
    };
    // ADC_REGULAR_RANK_8 is the highest rank, 8 possible channels per scan group
    using ScanGroup = EDF::Vector<ADC::Channel, 8>;
    enum class IRQType {
        None,
        ConvCplt,
        ConvHalfCplt,
        LevelOutOfWindow,
        Error,
    };
private:
    class BusyFlags : public EDF::BitField8 {
    public:
        constexpr BusyFlags( uint8_t raw = 0x00 ) : EDF::BitField8(raw) {}

        constexpr bool isIRQChannelBusy()           const { return get(0, 1); }
        constexpr void setIRQChannel( bool busy )         { set(0, 1, busy); }

        constexpr bool isIRQScanGroupBusy()         const { return get(1, 1); }
        constexpr void setIRQScanGroup( bool busy )       { set(1, 1, busy); }

        constexpr bool isPolling()                  const { return get(2, 1); }
        constexpr void setPolling( bool busy )            { set(2, 1, busy); }

        constexpr bool isBusy()                     const { return isIRQChannelBusy() || isIRQScanGroupBusy() || isPolling(); }
    };
private:
    ADC_HandleTypeDef* adc;
    uint32_t timeout_ticks;
    BusyFlags busyFlags;
    ADCChannel* irqChannel;
    ADCScanGroup* irqScanGroup;
    IRQType irqType;
private:
    Response toResponse( HAL_StatusTypeDef status, uint32_t adcError );
    bool isSequencerAlreadySetup( const ScanGroup& scanGroup );
    bool isSequencerAlreadySetup( Channel channel );
protected:
    Response configure( const ScanGroup& scanGroup );
    Response pollConfigure( Channel channel );

    Response pollStart();
    Response pollStop();
    Response pollForConversion();
    Response pollForEvent( Event event );

    Response irqConfigure( ADCChannel* self, Channel channel );
    Response irqStart();
    Response irqStop();

    Response dmaConfigure( ADCScanGroup* self, const ScanGroup& scanGroup );
    Response dmaConfigure( ADCChannel* self, Channel channel );
    Response dmaStart( uint32_t* dmaBuffer, std::size_t n );
    Response dmaStop();

    uint32_t getValue();

    friend class ADCChannel;
    friend class ADCScanGroup;
public:
    ADC( ADC_HandleTypeDef* adc ) :
        adc(adc), timeout_ticks(0),
        irqChannel(nullptr), irqScanGroup(nullptr)
    {}
    inline void setTimeout( uint32_t ticks ) { timeout_ticks = ticks; }

    uint32_t getMaxValue();

    void calibrate();
    uint32_t to_mV( int32_t adcValue );

    void handleIRQs();

    void ConvCpltCallback( ADC_HandleTypeDef* hadc );
    void ConvHalfCpltCallback( ADC_HandleTypeDef* hadc );
    void LevelOutOfWindowCallback( ADC_HandleTypeDef* hadc );
    void ErrorCallback( ADC_HandleTypeDef* hadc );
};

class ADCChannel {
public:
    using Response = EDF::ADCChannel::Response;
    using ResponseData = EDF::ADCChannel::ResponseData;
    using Callback = EDF::ADCChannel::Callback;
private:
    ADC& adc;
    ADC::Channel channel;
    Callback cb;
protected:
    void ConvCpltCallback();
    void ConvHalfCpltCallback();
    void LevelOutOfWindowCallback();
    void ErrorCallback();
    friend class ADC;
public:
    ADCChannel( ADC& adc, const ADC::Pin& pin );
    ADCChannel( ADC& adc, ADC::Channel channel ) :
        adc(adc), channel(channel), cb(nullptr)
    {}
    virtual ~ADCChannel() = default;
    Response start( const Callback& cb = Callback() );
    ResponseData getSingleConversion();
};

class ADCScanGroup {
public:
    using Response = EDF::ADCScanGroup::Response;
    using ResponseData = EDF::ADCScanGroup::ResponseData;
    using Callback = EDF::ADCScanGroup::Callback;
private:
    ADC& adc;
    ADC::ScanGroup scanGroup;
    uint32_t values[8]; // max of 8 channels per scan group
    Callback cb;
protected:
    void ConvCpltCallback();
    void ConvHalfCpltCallback();
    void LevelOutOfWindowCallback();
    void ErrorCallback();
    friend class ADC;
public:
    ADCScanGroup( ADC& adc ) : adc(adc), scanGroup{}, values{}, cb(nullptr) {}
    ADCScanGroup( ADC& adc, const std::initializer_list<ADC::Pin>& list );
    ADCScanGroup( ADC& adc, const std::initializer_list<ADC::Channel>& list );

    bool addChannel( const ADC::Pin& pin );
    bool addChannel( ADC::Channel channel );
    bool removeChannel( const ADC::Pin& pin );
    bool removeChannel( ADC::Channel channel );
    bool removeChannel( std::size_t index );
    Response start( const Callback& cb = Callback() );
};
