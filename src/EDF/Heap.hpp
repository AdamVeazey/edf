/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Vector.hpp"

#include <functional> // for std::less and std::greater

namespace EDF {

template<typename T, std::size_t N, typename Compare>
class Heap final {
private:
    Vector<T, N> heap;
private:
    void bubbleUp( std::size_t index );
    void bubbleDown( std::size_t index );
public:
    Heap() = default;
    template<typename... I>
    Heap( I... iList ) : heap{iList...} {}
    ~Heap() = default;

    /* Is Questions */
    inline constexpr bool isEmpty()                 const { return heap.isEmpty(); }
    inline constexpr bool isFull()                  const { return heap.isFull(); }

    /* Capacity */
    inline constexpr const std::size_t& length()    const { return heap.length(); }
    inline constexpr std::size_t maxLength()        const { return heap.maxLength(); }

    /* Operations */
    inline constexpr T& peek()                            { return heap.front(); }
    inline constexpr const T& peek()                const { return heap.front(); }

    inline constexpr void push( const T& value );
    inline constexpr void push( const T&& value );

    template<typename... Args>
    inline constexpr T& emplace( Args&&... args );

    inline constexpr T pop();

    inline constexpr void clear()                         { heap.clear(); }
};

// tag::declare_heap_max[]
template<typename T, std::size_t N>
using HeapMax = Heap<T, N, std::greater<T>>;
// end::declare_heap_max[]

// tag::declare_heap_min[]
template<typename T, std::size_t N>
using HeapMin = Heap<T, N, std::less<T>>;
// end::declare_heap_min[]

} /* EDF */

#include "EDF/src/Heap.tpp"