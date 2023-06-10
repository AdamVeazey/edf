/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#pragma once

#include <EDF/Array.hpp>

#include <algorithm>
#include <memory>

namespace EDF {

template<typename T, std::size_t N>
class Vector final{
private:
    std::size_t n;
    Array<T, N> buffer;
public:
    Vector() : n(0), buffer{} {} 
    template<typename... I>
    Vector( I... iList ) : buffer{iList...}, n(sizeof...(I)) {}
    ~Vector() = default;
    
    using Iterator = T*;
    using ConstIterator = const T*;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

     /* Current state */
    inline constexpr bool isEmpty()                                                         const { return n == 0; }
    inline constexpr bool isFull()                                                          const { return n == N; }

     /* Capacity */
    inline constexpr const std::size_t& length()                                            const { return n; }
    inline constexpr std::size_t maxLength()                                                const { return N; }

    /* Element access */
    inline constexpr T& at( std::size_t index )                                                   { return buffer.at( index ); }
    inline constexpr const T& at( std::size_t index )                                       const { return buffer.at( index ); }

    inline constexpr T& operator[]( std::size_t index )                                           { return buffer[index]; }
    inline constexpr const T& operator[]( std::size_t index )                               const { return buffer[index]; }
    
    inline constexpr T& front()                                                                   { return at( 0 ); }
    inline constexpr const T& front()                                                       const { return at( 0 ); }
    
    inline constexpr T& back()                                                                    { return at( n - 1 ); }
    inline constexpr const T& back()                                                        const { return at( n - 1 ); }
    
    inline constexpr T* data()                                                                    { return buffer.data(); }
    inline constexpr const T* data()                                                        const { return buffer.data(); }

    /* Operations */
    inline constexpr void clear()                                                           { std::destroy( begin(), end() ); n = 0; }

    inline constexpr void insert( std::size_t index, const T& value )                       { insert( ConstIterator(data() + index), value ); }
    inline constexpr void insert( std::size_t index, T&& value )                            { insert( ConstIterator(data() + index), value ); }
    inline constexpr void insert( std::size_t index, std::size_t count, const T& value )    { insert( ConstIterator(data() + index), count, value ); }
    inline constexpr void insert( std::size_t index, std::initializer_list<T> iList )       { insert( ConstIterator(data() + index), iList ); }
    inline constexpr Iterator insert( ConstIterator pos, const T& value )                   { return insert( pos, 1, value ); }
    constexpr Iterator insert( ConstIterator pos, T&& value);
    constexpr Iterator insert( ConstIterator pos, std::size_t count, const T& value );
    constexpr Iterator insert( ConstIterator pos, std::initializer_list<T> iList );

    template<typename... Args>
    inline constexpr void emplace( std::size_t index, Args&&... args )                      { emplace( ConstIterator(data() + index), std::forward<Args>(args)...); }
    template<typename... Args>
    constexpr Iterator emplace( ConstIterator pos, Args&&... args );
    
    inline constexpr void erase( std::size_t index )                                        { erase( ConstIterator(data() + index) ); }
    inline constexpr void erase( std::size_t first, std::size_t last )                      { erase( ConstIterator(data() + first), ConstIterator(data() + last) ); }
    constexpr Iterator erase( ConstIterator pos );
    constexpr Iterator erase( ConstIterator first, ConstIterator last );

    inline constexpr void pushBack( const T& value )                                        { insert( end(), value ); }
    inline constexpr void pushBack( T&& value )                                             { emplaceBack(std::move(value) ); }

    template<typename... Args>
    inline constexpr T& emplaceBack(Args&&... args)                                         { return *emplace(end(), args...); }

    inline constexpr T popBack()                                                            { EDF_ASSERTD(!isEmpty()); T v(std::move(back())); buffer[n--].~T(); return v; }


    /* Iterators */
    inline constexpr Iterator begin()                                                             { return Iterator( data() ); }
    inline constexpr ConstIterator begin()                                                  const { return ConstIterator( data() ); }
    inline constexpr ConstIterator cbegin()                                                 const { return ConstIterator( data() ); }

    inline constexpr Iterator end()                                                               { return Iterator( data() + n ); }
    inline constexpr ConstIterator end()                                                    const { return ConstIterator( data() + n ); }
    inline constexpr ConstIterator cend()                                                   const { return ConstIterator( data() + n ); }

    inline constexpr ReverseIterator rbegin()                                                     { return ReverseIterator( end() ); }
    inline constexpr ConstReverseIterator rbegin()                                          const { return ConstReverseIterator( end() ); }
    inline constexpr ConstReverseIterator crbegin()                                         const { return ConstReverseIterator( end() ); }

    inline constexpr ReverseIterator rend()                                                       { return ReverseIterator( begin() ); }
    inline constexpr ConstReverseIterator rend()                                            const { return ConstReverseIterator( begin() ); }
    inline constexpr ConstReverseIterator crend()                                           const { return ConstReverseIterator( begin() ); }
};

/* Non-member functions */

template<typename T, std::size_t N>
inline bool operator==( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) {
    return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
}

} /* EDF */

#include "src/Vector.tpp"