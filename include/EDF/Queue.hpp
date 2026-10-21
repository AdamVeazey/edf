/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Assert.hpp"

#include <cstdint>
#include <utility>
#include <new>

namespace EDF {

template<typename T, std::size_t N>
class Queue final{
private:
    static constexpr std::size_t WRAP = N-1;
    std::size_t head;
    std::size_t tail;
    alignas(T) unsigned char buffer[sizeof(T) * N];

    constexpr T* data() { return reinterpret_cast<T*>(buffer); }
    constexpr const T* data() const { return reinterpret_cast<const T*>(buffer); }
public:
    constexpr Queue() : head(0), tail(0) {}
    template<typename... I>
    constexpr Queue( I... iList );

    ~Queue() { clear(); }

    /* Is Questions */
    constexpr bool isEmpty()            const { return head == tail; }
    constexpr bool isFull()             const;

    /* Capacity */
    constexpr std::size_t length()      const;
    constexpr std::size_t maxLength()   const { return WRAP; }

    /* Operations */
    constexpr T& peek()                       { return data()[head]; }
    constexpr const T& peek()           const { return data()[head]; }

    constexpr void push( const T& value );
    constexpr void push( T&& value );

    template<typename... Args>
    constexpr T& emplace( Args&&... args );

    constexpr T pop();

    constexpr void clear()                    { while( !isEmpty() ) { pop(); } }

    /* uint8_t specialized member functions */
    constexpr std::uint8_t pop8be();
    constexpr std::uint16_t pop16be();
    constexpr std::uint32_t pop32be();
    constexpr std::uint64_t pop64be();

    constexpr std::uint8_t pop8le();
    constexpr std::uint16_t pop16le();
    constexpr std::uint32_t pop32le();
    constexpr std::uint64_t pop64le();
};

} /* EDF */

#include "EDF/src/Queue.tpp"