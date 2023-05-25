/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <EDF/Array.hpp>
#include <EDF/Assert.hpp>

#include <cstddef>

namespace EDF {

template<typename T, std::size_t N>
class Stack final{
private:
    std::size_t current;
    Array<T,N> buffer;
public:
    Stack() : current( static_cast<std::size_t>(-1) ) {}
    ~Stack() = default;

    inline bool isEmpty()               const { return current == static_cast<std::size_t>(-1); }
    inline bool isFull()                const { return current == N; }
    inline std::size_t length()         const { return current + 1; }
    inline std::size_t maxLength()      const { return N; }

    inline void push( const T& value )  { EDF_ASSERTD(!isFull()); buffer[++current] = value; }
    inline void push( const T&& value ) { EDF_ASSERTD(!isFull()); buffer[++current] = value; }
    inline const T& pop()               { EDF_ASSERTD(!isEmpty()); return buffer[current--]; }
    inline const T& peek()              { EDF_ASSERTD(!isEmpty()); return buffer[current]; }
    inline void clear()                 { current = static_cast<std::size_t>(-1); }
};

} /* EDF */