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
    case HAL_ERROR:     return Response::Error;
    case HAL_OK:
    default:
        break;
    }
    switch( adcError ) {
    case HAL_ADC_ERROR_NONE:        return Response::Ok;
    case HAL_ADC_ERROR_OVR:         return Response::ErrorOverrun;
    case HAL_ADC_ERROR_INTERNAL:    return Response::ErrorInternal;
    case HAL_ADC_ERROR_DMA:         return Response::ErrorDMA;
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
configure( const ScanGroup& scanGroup ) {
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
pollConfigure( Channel channel ) {
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
pollStart() {
    if( busyFlags.isBusy() ) return Response::ErrorBusy;
    busyFlags.setPolling( true );
    return toResponse( HAL_ADC_Start( adc ), adc->ErrorCode );
}

ADC::Response ADC::
pollStop() {
    if( busyFlags.isPolling() ) {
        busyFlags.setPolling( false );
        return toResponse( HAL_ADC_Stop( adc ), adc->ErrorCode );
    }
    return Response::Error; // not polling
}

ADC::Response ADC::
pollForConversion() {
    auto r = toResponse(
        HAL_ADC_PollForConversion( adc, timeout_ticks ),
        adc->ErrorCode
    );
    return r;
}

ADC::Response ADC::
pollForEvent( Event event ) {
    return toResponse(
        HAL_ADC_PollForEvent( adc, static_cast<uint32_t>(event), timeout_ticks ),
        adc->ErrorCode
    );
}

ADC::Response ADC::
irqConfigure( ADCChannel* self, Channel channel ) {
    if( busyFlags.isBusy() ) return Response::ErrorBusy;
    auto r = pollConfigure( channel );
    if( r == Response::Ok ){
        irqChannel = self;      // used later for callback
        irqScanGroup = nullptr; // don't use this for callbacks later
    }
    return r;
}

ADC::Response ADC::
irqStart() {
    if( busyFlags.isBusy() ) return Response::ErrorBusy;
    busyFlags.setIRQChannel( true );
    return toResponse( HAL_ADC_Start_IT( adc ), adc->ErrorCode );
}

ADC::Response ADC::
irqStop() {
    if( busyFlags.isIRQChannelBusy() ) {
        busyFlags.setIRQChannel( false );
        return toResponse( HAL_ADC_Stop_IT( adc ), adc->ErrorCode );
    }
    return Response::Error; // not waiting on Interrupt
}

ADC::Response ADC::
dmaConfigure( ADCScanGroup* self, const ScanGroup& scanGroup ) {
    if( busyFlags.isBusy() ) return Response::ErrorBusy;
    auto r = configure( scanGroup );
    if( r == Response::Ok ) {
        irqScanGroup = self;    // used later for callback
        irqChannel = nullptr;   // don't use this for callbacks later
    }
    return r;
}

ADC::Response ADC::
dmaConfigure( ADCChannel* self, Channel channel ) {
    if( busyFlags.isBusy() ) return Response::ErrorBusy;
    auto r = pollConfigure( channel );
    if( r == Response::Ok ){
        irqChannel = self;      // used later for callback
        irqScanGroup = nullptr; // don't use this for callbacks later
    }
    return r;
}

ADC::Response ADC::
dmaStart( uint32_t* dmaBuffer, std::size_t n ) {
    if( busyFlags.isBusy() ) return Response::ErrorBusy;
    busyFlags.setIRQScanGroup( true );
    return toResponse( HAL_ADC_Start_DMA( adc, dmaBuffer, n ), adc->ErrorCode );
}

ADC::Response ADC::
dmaStop() {
    if( busyFlags.isIRQScanGroupBusy() ) {
        busyFlags.setIRQScanGroup( false );
        return toResponse( HAL_ADC_Stop_DMA( adc ), adc->ErrorCode );
    }
    return Response::Error; // not waiting on DMA
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
    // HAL_ADCEx_Calibration_Start( adc );
}

uint32_t ADC::
to_mV( int32_t adcValue ) {
    return (adcValue * 3300) / getMaxValue();
}

void ADC::
handleIRQs() {
    switch( irqType ) {
    case IRQType::ConvCplt:
        if( irqScanGroup )  { irqScanGroup->ConvCpltCallback(); irqScanGroup = nullptr; }
        if( irqChannel )    { irqChannel->ConvCpltCallback(); irqChannel = nullptr; }
        irqType = IRQType::None;
        break;
    case IRQType::ConvHalfCplt:
        if( irqScanGroup )  { irqScanGroup->ConvHalfCpltCallback(); irqScanGroup = nullptr; }
        if( irqChannel )    { irqChannel->ConvHalfCpltCallback(); irqChannel = nullptr; }
        irqType = IRQType::None;
        break;
    case IRQType::LevelOutOfWindow:
        if( irqScanGroup )  { irqScanGroup->LevelOutOfWindowCallback(); irqScanGroup = nullptr; }
        if( irqChannel )    { irqChannel->LevelOutOfWindowCallback(); irqChannel = nullptr; }
        irqType = IRQType::None;
        break;
    case IRQType::Error:
        if( irqScanGroup )  { irqScanGroup->ErrorCallback(); irqScanGroup = nullptr; }
        if( irqChannel )    { irqChannel->ErrorCallback(); irqChannel = nullptr; }
        irqType = IRQType::None;
        break;
    default:
        break;
    }
}

void ADC::
ConvCpltCallback( ADC_HandleTypeDef* hadc ) {
    if( hadc == adc ) {
        irqType = IRQType::ConvCplt;
        irqStop();
        dmaStop();
    }
}

void ADC::
ConvHalfCpltCallback( ADC_HandleTypeDef* hadc ) {
    if( hadc == adc ) {
        irqType = IRQType::ConvHalfCplt;
    }
}

void ADC::
LevelOutOfWindowCallback( ADC_HandleTypeDef* hadc ) {
    if( hadc == adc ) {
        irqType = IRQType::LevelOutOfWindow;
    }
}

void ADC::
ErrorCallback( ADC_HandleTypeDef* hadc ) {
    if( hadc == adc ) {
        irqType = IRQType::Error;
        irqStop();
        dmaStop();
    }
}

/*****************************************************************************/
/*******************************ADCChannel************************************/
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
    LUT{ ADC::Pin{ GPIOA, 0 }, ADC::Channel::IN0 },
    LUT{ ADC::Pin{ GPIOA, 1 }, ADC::Channel::IN1 },
    LUT{ ADC::Pin{ GPIOA, 2 }, ADC::Channel::IN2 },
    LUT{ ADC::Pin{ GPIOA, 3 }, ADC::Channel::IN3 },
    LUT{ ADC::Pin{ GPIOA, 4 }, ADC::Channel::IN4 },
    LUT{ ADC::Pin{ GPIOA, 5 }, ADC::Channel::IN5 },
    LUT{ ADC::Pin{ GPIOA, 6 }, ADC::Channel::IN6 },
    LUT{ ADC::Pin{ GPIOA, 7 }, ADC::Channel::IN7 },
    LUT{ ADC::Pin{ GPIOA, 8 }, ADC::Channel::IN8 },

    LUT{ ADC::Pin{ GPIOA, 13 }, ADC::Channel::IN13 },
    LUT{ ADC::Pin{ GPIOA, 14 }, ADC::Channel::IN14 },
};

ADCChannel::
ADCChannel( ADC& adc, const ADC::Pin& pin ) : adc(adc), cb(nullptr) {
    for( const auto& item : pinChannelLUT ) {
        if( item == pin ) {
            channel = item.channel;
        }
    }
}

void ADCChannel::
ConvCpltCallback() {
    if( cb ) {
        cb( ResponseData( Response::Ok, adc.getValue() ) );
    }
}

void ADCChannel::
ConvHalfCpltCallback() {
    if( cb ) {
        cb( Response::Error ); // half of a single conversion!?
    }
}

void ADCChannel::
LevelOutOfWindowCallback() {
    if( cb ) {
        cb( Response::Error ); // not setup yet, how??
    }
}

void ADCChannel::
ErrorCallback() {
    if( cb ) {
        cb( adc.toResponse(HAL_StatusTypeDef::HAL_ERROR, adc.adc->ErrorCode) );
    }
}

ADCChannel::Response ADCChannel::
start( const Callback& cb ) {
    Response r = adc.irqConfigure( this, channel );
    if( r != Response::Ok ) return r;

    if( cb ) {
        this->cb = cb;
    }
    return adc.irqStart();
}

ADCChannel::ResponseData ADCChannel::
getSingleConversion() {
    Response r = adc.pollConfigure( channel );
    if( r != Response::Ok ) return r;

    r = adc.pollStart();
    if( r != Response::Ok ) return r;

    r = adc.pollForConversion();
    return ResponseData( r, adc.getValue() );
}

/*****************************************************************************/
/*******************************ADCScanGroup**********************************/
/*****************************************************************************/

void ADCScanGroup::
ConvCpltCallback() {
    if( cb ) {
        cb( ResponseData( Response::Ok, values, scanGroup.length() ) );
        cb = nullptr;
    }
}

void ADCScanGroup::
ConvHalfCpltCallback() {
    if( cb ) {
        cb( Response::ErrorBusy );
        cb = nullptr;
    }
}

void ADCScanGroup::
LevelOutOfWindowCallback() {
    if( cb ) {
        cb( Response::Error ); // not setup yet, how??
        cb = nullptr;
    }
}

void ADCScanGroup::
ErrorCallback() {
    if( cb ) {
        cb( adc.toResponse(HAL_StatusTypeDef::HAL_ERROR, adc.adc->ErrorCode) );
        cb = nullptr;
    }
}

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
    return true;
}

ADCScanGroup::Response ADCScanGroup::
start( const Callback& cb ) {
    auto r = adc.dmaConfigure( this, scanGroup );
    if( r != Response::Ok ) return r;

    if( cb ) {
        this->cb = cb;
    }

    return adc.dmaStart( values, scanGroup.length() );
}

/*
Start here for ideas on how to create our own EDF::function<void(int)>;
Could even do something like EDF::function<void(int), sizeof(void*)>

can we use template deduction for size via constructors??

template <typename Functor>
auto make_small_function(Functor&& f) {
    // Deduce the size and alignment of the lambda capture
    constexpr size_t size = sizeof(std::decay_t<Functor>);
    constexpr size_t alignment = alignof(std::decay_t<Functor>);

    // Allocate memory for the functor and construct it
    alignas(alignment) unsigned char buffer[size];
    new (buffer) std::decay_t<Functor>(std::forward<Functor>(f));

    // Return a lambda that captures the buffer and calls the functor
    return [func = reinterpret_cast<std::decay_t<Functor>*>(buffer)](auto&&... args) -> decltype(auto) {
        return (*func)(std::forward<decltype(args)>(args)...);
    };
}
*/

/*

Notes on getting unstuck

Binary search learning
1. Is thing working?
2. What part am I pretty sure works? Test that
3. Was I wrong? choose a smaller piece to test
4. If it works, great move "up" the path

*/


