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
    inline constexpr T& at( std::size_t index )                       { EDF_ASSERTD(index < N); return buff[index]; }
    inline constexpr const T& at( std::size_t index )           const { EDF_ASSERTD(index < N); return buff[index]; }
    
    inline constexpr T& operator[]( std::size_t index )               { return buff[index]; }
    inline constexpr const T& operator[]( std::size_t index )   const { return buff[index]; }
    
    inline constexpr T& front()                                       { return at( 0 ); }
    inline constexpr const T& front()                           const { return at( 0 ); }
    
    inline constexpr T& back()                                        { return at( N - 1 ); }
    inline constexpr const T& back()                            const { return at( N - 1 ); }
    
    inline constexpr T* data()                                        { return buff; }
    inline constexpr const T* data()                            const { return buff; }

    /* Capacity */
    inline constexpr std::size_t maxLength()                    const { return N; }

    /* Operations */
    // template<typename t = std::enable_if_t<std::is_default_constructible<T>::value>>
    inline void clear() { 
        static_assert(std::is_default_constructible<T>::value, "T needs to be default constructable in order to use clear(). Use fill() instead");
        fill( T() );
    }

    inline void fill( const T& value )  { std::fill( begin(), end(), value ); }
    inline void fill( const T&& value ) { std::fill( begin(), end(), value ); }


    /* Iterators */
    using Iterator = T*;
    using ConstIterator = const T*;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
    
    inline Iterator begin()                                           { return Iterator( data() ); }
    inline ConstIterator begin()                                const { return ConstIterator( data() ); }
    inline ConstIterator cbegin()                               const { return ConstIterator( data() ); }

    inline Iterator end()                                             { return Iterator( data() + N ); }
    inline ConstIterator end()                                  const { return ConstIterator( data() + N ); }
    inline ConstIterator cend()                                 const { return ConstIterator( data() + N ); }

    inline ReverseIterator rbegin()                                   { return ReverseIterator( end() ); }
    inline ConstReverseIterator rbegin()                        const { return ConstReverseIterator( end() ); }
    inline ConstReverseIterator crbegin()                       const { return ConstReverseIterator( end() ); }

    inline ReverseIterator rend()                                     { return ReverseIterator( begin() ); }
    inline ConstReverseIterator rend()                          const { return ConstReverseIterator( begin() ); }
    inline ConstReverseIterator crend()                         const { return ConstReverseIterator( begin() ); }
};

/* Non-member functions */

template<typename T, std::size_t N>
inline bool operator==( const Array<T, N>& lhs, const Array<T, N>& rhs ) {
    return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
}

} /* EDF */