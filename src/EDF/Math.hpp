/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <cstddef>
#include <cmath>

// NOTE: This needs to be in the global namespace. EX: 0_uz == std::size_t literal
// tag::literal_size_t[]
constexpr std::size_t operator ""_uz( unsigned long long x ) { return x; }
// end::literal_size_t[]

namespace EDF {

template<typename T, std::size_t N>
constexpr std::size_t nElements( const T (&)[N] ) { return N; }

// tag::is_pow_2[]
constexpr bool isPow2( std::size_t v ) { return !(v&(v-1)); }
// end::is_pow_2[]

template<typename T>
constexpr const T& min( const T& lhs, const T& rhs ) {
    return (lhs < rhs) ? lhs : rhs;
}

template<typename T>
constexpr const T& max( const T& lhs, const T& rhs ) {
    return (lhs > rhs) ? lhs : rhs;
}

template<std::size_t R1, std::size_t R2, typename T>
constexpr T voltageDividerCalcVout( const T& Vin ){
    const auto Vout = (Vin * static_cast<T>(R2)) / static_cast<T>(R1 + R2);
    if constexpr( std::is_floating_point_v<T> ) {
        return std::round( Vout );
    }
    return Vout;
}

template<std::size_t R1, std::size_t R2, typename T>
constexpr T voltageDividerCalcVin( const T& Vout ){
    const auto Vin = (Vout * (R1 + R2)) / R2;
    if constexpr( std::is_floating_point_v<T> ) {
        return std::round( Vin );
    }
    return Vin;
}

template<typename T>
constexpr T temperatureCtoF( const T& temp_C ) {
    const auto f = ((temp_C * 9) / (5)) + 32;
    if constexpr( std::is_floating_point_v<T> ){
        return std::round(f);
    }
    return f;
}

template<typename T>
constexpr T temperatureFtoC( const T& temp_F ) {
    const auto c = ((temp_F - 32) * 5) / 9;
    if constexpr( std::is_floating_point_v<T> ) {
        return std::round(c);
    }
    return c;
}

} /* EDF */