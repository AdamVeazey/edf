/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <EDF/Array.hpp>

#include <cstdint>

namespace EDF {

template<typename T, std::size_t N>
class Queue final{
private:
    static constexpr std::size_t WRAP = N-1;
    std::size_t head;
    std::size_t tail;
    EDF::Array<T, N> buffer;
public:
    Queue() : head(0), tail(0), buffer{} {}
    template<typename... I>
    Queue( I... iList ) : head(sizeof...(I)), tail(0), buffer{iList...} {}
    ~Queue() = default;

    /* Is Questions */
    inline constexpr bool isEmpty()             const { return head == tail; }
    inline constexpr bool isFull()              const;

    /* Capacity */
    inline constexpr std::size_t length()       const;
    inline constexpr std::size_t maxLength()    const { return WRAP; }

    /* Operations */
    inline constexpr T& peek()                        { return buffer[head]; }
    inline constexpr const T& peek()            const { return buffer[head]; }

    inline constexpr void push( const T& value );
    inline constexpr void push( const T&& value );

    template<typename... Args>
    inline constexpr T& emplace( Args&&... args );

    inline constexpr T pop();

    inline constexpr void clear()                     { while( !isEmpty() ) { pop(); } }

    /* uint8_t specialized member functions */
    inline constexpr std::uint8_t pop8be();
    inline constexpr std::uint16_t pop16be();
    inline constexpr std::uint32_t pop32be();
    inline constexpr std::uint64_t pop64be();

    inline constexpr std::uint8_t pop8le();
    inline constexpr std::uint16_t pop16le();
    inline constexpr std::uint32_t pop32le();
    inline constexpr std::uint64_t pop64le();
};


} /* EDF */

#include "src/Queue.tpp"