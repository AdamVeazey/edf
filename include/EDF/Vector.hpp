/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#pragma once

#include "EDF/Array.hpp"
#include "EDF/Math.hpp"

#include <algorithm>
#include <memory>

namespace EDF {

template<typename T, std::size_t N>
class Vector final{
private:
    std::size_t n;
    Array<T, N> buffer;
public:
    constexpr Vector() : n(0), buffer{} {}
    template<typename... I>
    constexpr Vector( I... iList ) : buffer{iList...}, n(sizeof...(I)) {}
    ~Vector() = default;

    using Iterator = typename Array<T,N>::Iterator;
    using ConstIterator = typename Array<T,N>::ConstIterator;
    using ReverseIterator = typename Array<T,N>::ReverseIterator;
    using ConstReverseIterator = typename Array<T,N>::ConstReverseIterator;

     /* Current state */
    constexpr bool isEmpty()                                                        const { return n == 0; }
    constexpr bool isFull()                                                         const { return n == N; }

     /* Capacity */
    constexpr const std::size_t& length()                                           const { return n; }
    constexpr std::size_t maxLength()                                               const { return N; }

    /* Element access */
    constexpr T& at( std::size_t index )                                                  { EDF_ASSERTD(index < length()); return buffer.at( index ); }
    constexpr const T& at( std::size_t index )                                      const { EDF_ASSERTD(index < length()); return buffer.at( index ); }

    constexpr T& operator[]( std::size_t index )                                          { return buffer[index]; }
    constexpr const T& operator[]( std::size_t index )                              const { return buffer[index]; }

    constexpr T& front()                                                                  { return at( 0 ); }
    constexpr const T& front()                                                      const { return at( 0 ); }

    constexpr T& back()                                                                   { return at( n - 1 ); }
    constexpr const T& back()                                                       const { return at( n - 1 ); }

    constexpr T* data()                                                                   { return buffer.data(); }
    constexpr const T* data()                                                       const { return buffer.data(); }

    /* Operations */
    constexpr void clear()                                                                { std::destroy( begin(), end() ); n = 0; }

    constexpr void insert( std::size_t index, const T& value )                            { insert( ConstIterator(data() + index), value ); }
    constexpr void insert( std::size_t index, T&& value )                                 { insert( ConstIterator(data() + index), value ); }
    constexpr void insert( std::size_t index, std::size_t count, const T& value )         { insert( ConstIterator(data() + index), count, value ); }
    constexpr void insert( std::size_t index, std::initializer_list<T> iList )            { insert( ConstIterator(data() + index), iList ); }
    constexpr Iterator insert( ConstIterator pos, const T& value )                        { return insert( pos, 1, value ); }
    constexpr Iterator insert( ConstIterator pos, T&& value);
    constexpr Iterator insert( ConstIterator pos, std::size_t count, const T& value );
    constexpr Iterator insert( ConstIterator pos, std::initializer_list<T> iList );

    template<typename... Args>
    constexpr void emplace( std::size_t index, Args&&... args )                           { emplace( ConstIterator(data() + index), std::forward<Args>(args)...); }
    template<typename... Args>
    constexpr Iterator emplace( ConstIterator pos, Args&&... args );

    constexpr void erase( std::size_t index )                                             { erase( ConstIterator(data() + index) ); }
    constexpr void erase( std::size_t first, std::size_t last )                           { erase( ConstIterator(data() + first), ConstIterator(data() + last) ); }
    constexpr Iterator erase( ConstIterator pos );
    constexpr Iterator erase( ConstIterator first, ConstIterator last );

    constexpr void pushBack( const T& value )                                             { insert( end(), value ); }
    constexpr void pushBack( T&& value )                                                  { emplaceBack(std::move(value) ); }

    template<typename... Args>
    constexpr T& emplaceBack(Args&&... args)                                              { return *emplace(end(), args...); }

    constexpr T popBack()                                                                 { EDF_ASSERTD(!isEmpty()); T v(std::move(back())); --n; return v; }

    /* Iterators */
    constexpr Iterator begin()                                                            { return Iterator( data() ); }
    constexpr ConstIterator begin()                                                 const { return ConstIterator( data() ); }
    constexpr ConstIterator cbegin()                                                const { return ConstIterator( data() ); }

    constexpr Iterator end()                                                              { return Iterator( data() + n ); }
    constexpr ConstIterator end()                                                   const { return ConstIterator( data() + n ); }
    constexpr ConstIterator cend()                                                  const { return ConstIterator( data() + n ); }

    constexpr ReverseIterator rbegin()                                                    { return ReverseIterator( end() ); }
    constexpr ConstReverseIterator rbegin()                                         const { return ConstReverseIterator( end() ); }
    constexpr ConstReverseIterator crbegin()                                        const { return ConstReverseIterator( end() ); }

    constexpr ReverseIterator rend()                                                      { return ReverseIterator( begin() ); }
    constexpr ConstReverseIterator rend()                                           const { return ConstReverseIterator( begin() ); }
    constexpr ConstReverseIterator crend()                                          const { return ConstReverseIterator( begin() ); }
};

/* Non-member functions */

template<typename T, std::size_t N>
constexpr bool operator==( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) {
    return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
}

} /* EDF */

#include "EDF/src/Vector.tpp"