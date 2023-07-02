/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Vector.hpp"

namespace EDF {

template<typename T, std::size_t N>
class Stack final{
private:
    Vector<T, N> buffer;
public:
    Stack() = default;
    template<typename... I>
    Stack( I... iList ) : buffer{iList...} {}
    ~Stack() = default;

    /* Is Questions */
    constexpr bool isEmpty()                const { return buffer.isEmpty(); }
    constexpr bool isFull()                 const { return buffer.isFull(); }
    
    /* Capacity */
    constexpr const std::size_t& length()   const { return buffer.length(); }
    constexpr std::size_t maxLength()       const { return buffer.maxLength(); }

    /* Operations */
    constexpr T& peek()                           { return buffer.back(); }
    constexpr const T& peek()               const { return buffer.back(); }
    
    constexpr void push( const T& value )         { buffer.pushBack( value ); }
    constexpr void push( const T&& value )        { buffer.pushBack( value ); }
    
    template<typename... Args>
    constexpr T& emplace( Args&&... args )        { return buffer.emplaceBack(std::forward<Args>(args)...); }
    
    constexpr T pop()                             { return buffer.popBack(); }
    
    constexpr void clear()                        { buffer.clear(); }
};

} /* EDF */