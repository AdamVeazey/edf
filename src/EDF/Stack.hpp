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
    inline constexpr bool isEmpty()                 const { return buffer.isEmpty(); }
    inline constexpr bool isFull()                  const { return buffer.isFull(); }
    
    /* Capacity */
    inline constexpr const std::size_t& length()    const { return buffer.length(); }
    inline constexpr std::size_t maxLength()        const { return buffer.maxLength(); }

    /* Operations */
    inline constexpr T& peek()                            { return buffer.back(); }
    inline constexpr const T& peek()                const { return buffer.back(); }
    
    inline constexpr void push( const T& value )          { buffer.pushBack( value ); }
    inline constexpr void push( const T&& value )         { buffer.pushBack( value ); }
    
    template<typename... Args>
    inline constexpr T& emplace( Args&&... args )         { return buffer.emplaceBack(std::forward<Args>(args)...); }
    
    inline constexpr T pop()                              { return buffer.popBack(); }
    
    inline constexpr void clear()                         { buffer.clear(); }
};

} /* EDF */