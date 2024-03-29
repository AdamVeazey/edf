/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Queue.hpp"
#include "EDF/Math.hpp"

namespace EDF {

template<typename T, std::size_t N>
constexpr bool Queue<T, N>::
isFull() const {
    if constexpr( isPow2( N ) ) {
        return head == ((tail+1) & WRAP);
    }
    return head == ((tail+1) % N);
}

template<typename T, std::size_t N>
constexpr std::size_t Queue<T, N>::
length() const {
    if constexpr( isPow2( N ) ) {
        return (tail - head) & WRAP;
    }
    return (tail - head) % N;
}

template<typename T, std::size_t N>
constexpr void Queue<T, N>::
push( const T& value ) {
    EDF_ASSERTD( !isFull(), "Queue must not be full in order to use push()" );
    buffer[tail] = value;
    if constexpr( isPow2( N ) ) {
        tail = (tail+1) & WRAP;
    }
    else{
        tail = (tail+1) % N;
    }
}

template<typename T, std::size_t N>
constexpr void Queue<T, N>::
push( const T&& value ) {
    EDF_ASSERTD( !isFull(), "Queue must not be full in order to use push()" );
    buffer[tail] = std::move(value);
    if constexpr( isPow2( N ) ) {
        tail = (tail+1) & WRAP;
    }
    else{
        tail = (tail+1) % N;
    }
}

template<typename T, std::size_t N>
template<typename... Args>
constexpr T& Queue<T, N>::
emplace( Args&&... args ) {
    EDF_ASSERTD( !isFull(), "Queue must not be full in order to use emplace()" );
    new (&buffer[tail]) T(std::forward<Args>(args)...);
    if constexpr( isPow2( N ) ) {
        tail = (tail+1) & WRAP;
    }
    else{
        tail = (tail+1) % N;
    }
    return buffer[tail];
}

template<typename T, std::size_t N>
constexpr T Queue<T, N>::
pop() {
    EDF_ASSERTD( !isEmpty(), "Queue must not be empty in order to use pop()" );
    T tmp = buffer[head];
    if constexpr( isPow2( N ) ) {
        head = (head+1) & WRAP;
    }
    else {
        head = (head+1) % N;
    }
    return tmp;
}

/* uint8_t specialized memler functions */
template<typename T, std::size_t N>
constexpr std::uint8_t Queue<T,N>::
pop8be() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop8be() is only available if T is a 'std::uint8_t'");
    return pop();
}

template<typename T, std::size_t N>
constexpr std::uint16_t Queue<T, N>::
pop16be() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop16be() is only available if T is a 'std::uint8_t'");
    uint16_t result = static_cast<uint16_t>(static_cast<uint16_t>(pop8be()) << 8);
    result |= pop8be();
    return result;
}

template<typename T, std::size_t N>
constexpr std::uint32_t Queue<T,N>::
pop32be() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop32be() is only available if T is a 'std::uint8_t'");
    uint32_t result = static_cast<uint32_t>(pop16be()) << 16;
    result |= pop16be();
    return result;
}

template<typename T, std::size_t N>
constexpr std::uint64_t Queue<T,N>::
pop64be() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop64be() is only available if T is a 'std::uint8_t'");
    uint64_t result = static_cast<std::uint64_t>(pop32be()) << 32;
    result |= pop32be();
    return result;
}

template<typename T, std::size_t N>
constexpr std::uint8_t Queue<T,N>::
pop8le() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop8le() is only available if T is a 'std::uint8_t'");
    return pop();
}

template<typename T, std::size_t N>
constexpr std::uint16_t Queue<T, N>::
pop16le() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop16le() is only available if T is a 'std::uint8_t'");
    uint16_t result = pop8le();
    result |= pop8le() << 8;
    return result;
}

template<typename T, std::size_t N>
constexpr std::uint32_t Queue<T,N>::
pop32le() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop32le() is only available if T is a 'std::uint8_t'");
    uint32_t result = pop16le();
    result |= static_cast<uint32_t>(pop16le()) << 16;
    return result;
}

template<typename T, std::size_t N>
constexpr std::uint64_t Queue<T,N>::
pop64le() {
    static_assert( std::is_same_v<T, std::uint8_t>, "pop64le() is only available if T is a 'std::uint8_t'");
    uint64_t result = pop32le();
    result |= static_cast<std::uint64_t>(pop32le()) << 32;
    return result;
}

} /* EDF */