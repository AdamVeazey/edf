/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Assert.hpp"

#include <iterator>

namespace EDF {

template<typename T, std::size_t N>
class Array final {
private:
    T buff[N];
public:
    Array() : buff{} {} 
    template<typename... I>
    Array( I... initializerList ) : buff{initializerList...} {}
    ~Array() = default;

    /* Element access */
    constexpr T& at( std::size_t index )                      { EDF_ASSERTD(index < N); return buff[index]; }
    constexpr const T& at( std::size_t index )          const { EDF_ASSERTD(index < N); return buff[index]; }
    
    constexpr T& operator[]( std::size_t index )              { return buff[index]; }
    constexpr const T& operator[]( std::size_t index )  const { return buff[index]; }
    
    constexpr T& front()                                      { return at( 0 ); }
    constexpr const T& front()                          const { return at( 0 ); }
    
    constexpr T& back()                                       { return at( N - 1 ); }
    constexpr const T& back()                           const { return at( N - 1 ); }
    
    constexpr T* data()                                       { return buff; }
    constexpr const T* data()                           const { return buff; }

    /* Capacity */
    constexpr std::size_t maxLength()                   const { return N; }

    /* Operations */
    // template<typename t = std::enable_if_t<std::is_default_constructible<T>::value>>
    constexpr void clear() { 
        static_assert(std::is_default_constructible<T>::value, "T needs to be default constructable in order to use clear(). Use fill() instead");
        fill( T() );
    }

    constexpr void fill( const T& value )                     { std::fill( begin(), end(), value ); }
    constexpr void fill( const T&& value )                    { std::fill( begin(), end(), value ); }


    /* Iterators */
    using Iterator = T*;
    using ConstIterator = const T*;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
    
    constexpr Iterator begin()                                { return Iterator( data() ); }
    constexpr ConstIterator begin()                     const { return ConstIterator( data() ); }
    constexpr ConstIterator cbegin()                    const { return ConstIterator( data() ); }

    constexpr Iterator end()                                  { return Iterator( data() + N ); }
    constexpr ConstIterator end()                       const { return ConstIterator( data() + N ); }
    constexpr ConstIterator cend()                      const { return ConstIterator( data() + N ); }

    constexpr ReverseIterator rbegin()                        { return ReverseIterator( end() ); }
    constexpr ConstReverseIterator rbegin()             const { return ConstReverseIterator( end() ); }
    constexpr ConstReverseIterator crbegin()            const { return ConstReverseIterator( end() ); }

    constexpr ReverseIterator rend()                          { return ReverseIterator( begin() ); }
    constexpr ConstReverseIterator rend()               const { return ConstReverseIterator( begin() ); }
    constexpr ConstReverseIterator crend()              const { return ConstReverseIterator( begin() ); }
};

/* Non-member functions */

template<typename T, std::size_t N>
constexpr bool operator==( const Array<T, N>& lhs, const Array<T, N>& rhs ) {
    return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
}

} /* EDF */