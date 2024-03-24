/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/MCU/ST/STM32C011F6/ADC.hpp"

ADC::Response ADC::
toResponse( HAL_StatusTypeDef status, uint32_t adcError ) {
    switch( status ) {
    case HAL_BUSY:      return Response::ErrorBusy;
    case HAL_TIMEOUT:   return Response::ErrorTimeout;
    case HAL_OK:
    default:
        break;
    }
    switch( adcError ) {
    case HAL_ADC_ERROR_NONE:        return Response::Ok;
    case HAL_ADC_ERROR_OVR:         return Response::ErrorOverrun;
    case HAL_ADC_ERROR_INTERNAL:    return Response::Error;
    default:
        break;
    }
    return Response::Error;
}

bool ADC::
isSequencerAlreadySetup( const ScanGroup& scanGroup ) {
    EDF_ASSERTD(scanGroup.length() > 0, "scan group needs to contain at least 1 channel");
    for( const auto& channel : scanGroup ) {
        if( !isSequencerAlreadySetup( channel ) ) {
            return false;
        }
    }
    return true;
}

bool ADC::
isSequencerAlreadySetup( Channel channel ) {
    return (LL_ADC_REG_GetSequencerChannels( adc->Instance )
            & static_cast<uint32_t>(channel));
}

ADC::Response ADC::
configureScanGroup( const ScanGroup& scanGroup ) {
    auto& NbrOfConversion = adc->Init.NbrOfConversion;
    auto& ScanConvMode = adc->Init.ScanConvMode;
    Response r = Response::Ok;

    if( (NbrOfConversion != scanGroup.length())
        || (ScanConvMode != ADC_SCAN_ENABLE)
    ) {
        // reconfigure ADC
        NbrOfConversion = scanGroup.length();
        ScanConvMode = ADC_SCAN_ENABLE;
        r = toResponse( HAL_ADC_Init( adc ), adc->ErrorCode );
        if( r != Response::Ok ) return r;
    }

    if( !isSequencerAlreadySetup( scanGroup ) ) {
        // configure channels
        static constexpr uint32_t ranks[] = {
            ADC_REGULAR_RANK_1, ADC_REGULAR_RANK_2,
            ADC_REGULAR_RANK_3, ADC_REGULAR_RANK_4,
            ADC_REGULAR_RANK_5, ADC_REGULAR_RANK_6,
            ADC_REGULAR_RANK_7, ADC_REGULAR_RANK_8,
        };
        ADC_ChannelConfTypeDef cfg;
        cfg.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
        for( std::size_t k = 0; k < scanGroup.length(); ++k ) {
            cfg.Channel = static_cast<uint32_t>(scanGroup[k]);
            cfg.Rank = ranks[k];
            r = toResponse( HAL_ADC_ConfigChannel( adc, &cfg ), adc->ErrorCode );
            if( r != Response::Ok ) return r;
        }
    }
    return r;
}

ADC::Response ADC::
configureSingleConversion( Channel channel ) {
    // HAL_ADC_GetState( adc );
    // HAL_ADC_STATE_REG_BUSY;
    auto& NbrOfConversion = adc->Init.NbrOfConversion;
    auto& ScanConvMode = adc->Init.ScanConvMode;
    Response r = Response::Ok;
    if( (NbrOfConversion != 1)
        || (ScanConvMode != ADC_SCAN_DISABLE)
    ) {
        // reconfigure ADC
        NbrOfConversion = 1;
        ScanConvMode = ADC_SCAN_DISABLE;
        r = toResponse( HAL_ADC_Init( adc ), adc->ErrorCode );
        if( r != Response::Ok ) return r;
    }

    if( !isSequencerAlreadySetup( channel ) ) {
        ADC_ChannelConfTypeDef cfg;
        cfg.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
        cfg.Channel = static_cast<uint32_t>(channel);
        cfg.Rank = ADC_REGULAR_RANK_1;
        r = toResponse( HAL_ADC_ConfigChannel( adc, &cfg ), adc->ErrorCode );
        if( r != Response::Ok ) return r;
    }
    return r;
}

ADC::Response ADC::
start() {
    return toResponse( HAL_ADC_Start( adc ), adc->ErrorCode );
}

ADC::Response ADC::
stop() {
    return toResponse( HAL_ADC_Stop( adc ), adc->ErrorCode );
}

ADC::Response ADC::
pollForConversion() {
    return toResponse(
        HAL_ADC_PollForConversion( adc, timeout_ticks ),
        adc->ErrorCode
    );
}

ADC::Response ADC::
pollForEvent( Event event ) {
    return toResponse(
        HAL_ADC_PollForEvent( adc, static_cast<uint32_t>(event), timeout_ticks ),
        adc->ErrorCode
    );
}

uint32_t ADC::
getValue() {
    return HAL_ADC_GetValue( adc );
}

uint32_t ADC::
getMaxValue() {
    uint32_t total = (1 << 12) - 1;
    switch( adc->Init.Resolution ) {
    case ADC_RESOLUTION_12B:                            break;
    case ADC_RESOLUTION_10B: total = (1 << 10) - 1;     break;
    case ADC_RESOLUTION_8B:  total = (1 << 8) - 1;      break;
    case ADC_RESOLUTION_6B:  total = (1 << 6) - 1;      break;
    default: EDF_ASSERTD(false, "Invalid resolution!"); break;
    }
    return total;
}

void ADC::
calibrate() {
    HAL_ADCEx_Calibration_Start( adc );
}

uint32_t ADC::
to_mV( int32_t adcValue ) {

}


/*****************************************************************************/

struct LUT {
    ADC::Pin pin;
    ADC::Channel channel;
};

constexpr bool operator==( const ADC::Pin& lhs, const ADC::Pin& rhs ) {
    return (lhs.pin == rhs.pin) && (lhs.port == rhs.port);
}

constexpr bool operator==( const LUT& lhs, const ADC::Pin& rhs ) {
    return lhs.pin == rhs;
}

constexpr bool operator==( const ADC::Pin& lhs, const LUT& rhs ) {
    return lhs == rhs.pin;
}

constexpr bool operator==( const LUT& lhs, const ADC::Channel& rhs ) {
    return lhs.channel == rhs;
}

constexpr bool operator==( const ADC::Channel& lhs, const LUT& rhs ) {
    return lhs == rhs.channel;
}

constexpr LUT pinChannelLUT[] = {
    LUT{ ADC::Pin{ GPIOA, (1 << 0) }, ADC::Channel::IN0 },
    LUT{ ADC::Pin{ GPIOA, (1 << 1) }, ADC::Channel::IN1 },
    LUT{ ADC::Pin{ GPIOA, (1 << 2) }, ADC::Channel::IN2 },
    LUT{ ADC::Pin{ GPIOA, (1 << 3) }, ADC::Channel::IN3 },
    LUT{ ADC::Pin{ GPIOA, (1 << 4) }, ADC::Channel::IN4 },
    LUT{ ADC::Pin{ GPIOA, (1 << 5) }, ADC::Channel::IN5 },
    LUT{ ADC::Pin{ GPIOA, (1 << 6) }, ADC::Channel::IN6 },
    LUT{ ADC::Pin{ GPIOA, (1 << 7) }, ADC::Channel::IN7 },
    LUT{ ADC::Pin{ GPIOA, (1 << 8) }, ADC::Channel::IN8 },

    LUT{ ADC::Pin{ GPIOA, (1 << 13) }, ADC::Channel::IN13 },
    LUT{ ADC::Pin{ GPIOA, (1 << 14) }, ADC::Channel::IN14 },
};

ADCChannel::
ADCChannel( ADC& adc, const ADC::Pin& pin ) : adc(adc), cb(nullptr) {
    for( const auto& item : pinChannelLUT ) {
        if( item == pin ) {
            channel = item.channel;
        }
    }
}

ADCChannel::Response ADCChannel::
start( const Callback& cb ) {
    if( cb ) {
        this->cb = cb;
    }
    return adc.start();
}

ADCChannel::ResponseData ADCChannel::
getSingleConversion() {
    Response r = adc.configureSingleConversion( channel );
    if( r != Response::Ok ) return r;

    r = adc.start();
    if( r != Response::Ok ) return r;

    r = adc.pollForConversion();
    return ResponseData( r, adc.getValue() );
}

/*****************************************************************************/

ADCScanGroup::
ADCScanGroup( ADC& adc, const std::initializer_list<ADC::Pin>& list ) :
    adc(adc), scanGroup{}, values{}, cb(nullptr)
{
    for( const auto& value : list ) {
        addChannel( value );
    }
}

ADCScanGroup::
ADCScanGroup( ADC& adc, const std::initializer_list<ADC::Channel>& list ) :
    adc(adc), scanGroup{}, values{}, cb(nullptr)
{
    for( const auto& value : list ) {
        addChannel( value );
    }
}

bool ADCScanGroup::
addChannel( const ADC::Pin& pin ) {
    if( scanGroup.isFull() ) return false;
    for( const auto& lutItem : pinChannelLUT ) {
        if( lutItem == pin ) {
            scanGroup.pushBack( lutItem.channel );
            return true;
        }
    }
    return false;
}

bool ADCScanGroup::
addChannel( ADC::Channel channel ) {
    if( scanGroup.isFull() ) return false;
    scanGroup.pushBack( channel );
    return true;
}

bool ADCScanGroup::
removeChannel( const ADC::Pin& pin ) {
    for( const auto& itemLUT : pinChannelLUT ) {
        if( itemLUT == pin ) {
            return removeChannel( itemLUT.channel );
        }
    }
    return false;
}

bool ADCScanGroup::
removeChannel( ADC::Channel channel ) {
    for( std::size_t k = 0; k < scanGroup.length(); ++k ) {
        if( scanGroup[k] == channel ) {
            return removeChannel(k);
        }
    }
    return false;
}

bool ADCScanGroup::
removeChannel( std::size_t index ) {
    if( scanGroup.isEmpty() ) return false;
    scanGroup.erase( index );
}

ADCScanGroup::ResponseData ADCScanGroup::
getSamples() {
    Response r = adc.configureScanGroup( scanGroup );
    if( r != Response::Ok ) return r;

    r = adc.start();
    if( r != Response::Ok ) return r;

    for( std::size_t k = 0; k < scanGroup.length(); ++k ) {
        r = adc.pollForConversion();
        if( r != Response::Ok ) return r;

        values[k] = adc.getValue();
    }
    return ResponseData( r, values, scanGroup.length() );
}