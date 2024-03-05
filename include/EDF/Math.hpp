/*
 * Copyright (c) 2024, Adam Veazey
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
constexpr bool isPow2( std::size_t v ) { return (v != 0) && !(v&(v-1)); }
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
    return (Vin * static_cast<T>(R2)) / static_cast<T>(R1 + R2);
}

template<std::size_t R1, std::size_t R2, typename T>
constexpr T voltageDividerCalcVin( const T& Vout ){
    return (Vout * static_cast<T>(R1 + R2)) / static_cast<T>(R2);
}

template<typename T>
constexpr T temperatureCtoF( const T& temp_C ) {
    return ((temp_C * static_cast<T>(9)) / static_cast<T>(5)) + static_cast<T>(32);
}

template<typename T>
constexpr T temperatureFtoC( const T& temp_F ) {
    return ((temp_F - static_cast<T>(32)) * static_cast<T>(5)) / static_cast<T>(9);
}

} /* EDF */