/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Assert.hpp"

#include <limits>
#include <type_traits>
#include <cstdint>

namespace EDF {

template<typename T>
class BitField {
    static_assert( std::is_unsigned_v<T>, "T must be unsigned" ); // implies integral type
private:
    T bits;
private:
    static constexpr T createMask( std::size_t startBit, std::size_t span ) {
        EDF_ASSERTD( (startBit + span) <= sizeof(T)*8, "must be a valid number of bits" );
        if( span == (sizeof(T)*8) ) {
            return std::numeric_limits<T>::max();
        }
        return static_cast<T>(((T{1} << span) - 1) << startBit);
    }
public:
    constexpr BitField( T initialValue = 0 ) : bits( initialValue ) {}

    constexpr void set( std::size_t startBit, std::size_t span, T value ) {
        EDF_ASSERTD( value < (1 << span), "value must fit within \"span\"" );
        const auto mask = createMask( startBit, span );
        bits = (bits & ~mask) | ((value << startBit) & mask);
    }
    constexpr T get( std::size_t startBit, std::size_t span ) const {
        return static_cast<T>((bits >> startBit) & createMask( 0, span ));
    }
};

// tag::uint8_t[]
using BitField8 = BitField<uint8_t>;
// end::uint8_t[]

// tag::uint16_t[]
using BitField16 = BitField<uint16_t>;
// end::uint16_t[]

// tag::uint32_t[]
using BitField32 = BitField<uint32_t>;
// end::uint32_t[]

// tag::uint64_t[]
using BitField64 = BitField<uint64_t>;
// end::uint64_t[]

} /* EDF */