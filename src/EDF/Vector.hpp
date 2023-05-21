/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#pragma once

#include <EDF/Array.hpp>

#include <vector>

namespace EDF {

template<typename T, std::size_t N>
class Vector final{
private:
    std::size_t n;
    Array<T, N> buffer;
public:
    Vector() : n(0), buffer{} {} 
    template<typename... I>
    Vector( I... initializerList ) : buffer{initializerList...}, n(sizeof...(I)) {}
    ~Vector() = default;
    
    using Iterator = T*;
    using ConstIterator = const T*;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

     /* Current state */
    inline bool isEmpty()                                       const { return n == 0; }
    inline bool isFull()                                        const { return n == N; }

     /* Capacity */
    inline const std::size_t& length()                          const { return n; }
    inline std::size_t maxLength()                              const { return N; }

    /* Element access */
    inline constexpr T& at( std::size_t index )                       { return buffer.at( index ); }
    inline constexpr const T& at( std::size_t index )           const { return buffer.at( index ); }

    inline constexpr T& operator[]( std::size_t index )               { return buffer[index]; }
    inline constexpr const T& operator[]( std::size_t index )   const { return buffer[index]; }
    
    inline constexpr T& front()                                       { return at( 0 ); }
    inline constexpr const T& front()                           const { return at( 0 ); }
    
    inline constexpr T& back()                                        { return at( n - 1 ); }
    inline constexpr const T& back()                            const { return at( n - 1 ); }
    
    inline constexpr T* data()                                        { return buffer.data(); }
    inline constexpr const T* data()                            const { return buffer.data(); }

    /* Operations */
    inline void clear() { n = 0; }
    inline void pushBack( const T& value )                            { EDF_ASSERTD(!isFull()); buffer[n++] = value; }
    inline const T& popBack()                                         { EDF_ASSERTD(!isEmpty()); return buffer[--n]; }
    inline void insert( std::size_t index, const T& value )           { insert( Iterator(data() + index), value ); }
    inline void erase( std::size_t index )                            { erase( Iterator(data() + index) ); }
    void insert( Iterator pos, const T& value );
    void erase( Iterator pos );
    
    template<typename... Args>
    void emplaceBack(Args&&... args);

    /* Iterators */
    
    inline Iterator begin()                                           { return Iterator( data() ); }
    inline ConstIterator begin()                                const { return ConstIterator( data() ); }
    inline ConstIterator cbegin()                               const { return ConstIterator( data() ); }

    inline Iterator end()                                             { return Iterator( data() + n ); }
    inline ConstIterator end()                                  const { return ConstIterator( data() + n ); }
    inline ConstIterator cend()                                 const { return ConstIterator( data() + n ); }

    inline ReverseIterator rbegin()                                   { return ReverseIterator( end() ); }
    inline ConstReverseIterator rbegin()                        const { return ConstReverseIterator( end() ); }
    inline ConstReverseIterator crbegin()                       const { return ConstReverseIterator( end() ); }

    inline ReverseIterator rend()                                     { return ReverseIterator( begin() ); }
    inline ConstReverseIterator rend()                          const { return ConstReverseIterator( begin() ); }
    inline ConstReverseIterator crend()                         const { return ConstReverseIterator( begin() ); }
};

} /* EDF */

#include "src/Vector.tpp"