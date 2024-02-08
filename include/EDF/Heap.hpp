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
    constexpr void bubbleUp( std::size_t index );
    constexpr void bubbleDown( std::size_t index );
public:
    constexpr Heap() = default;
    template<typename... I>
    constexpr Heap( I... iList );
    ~Heap() = default;

    /* Is Questions */
    constexpr bool isEmpty()                const { return heap.isEmpty(); }
    constexpr bool isFull()                 const { return heap.isFull(); }

    /* Capacity */
    constexpr const std::size_t& length()   const { return heap.length(); }
    constexpr std::size_t maxLength()       const { return heap.maxLength(); }

    /* Operations */
    constexpr T& peek()                           { return heap.front(); }
    constexpr const T& peek()               const { return heap.front(); }

    constexpr void push( const T& value );
    constexpr void push( const T&& value );

    template<typename... Args>
    constexpr T& emplace( Args&&... args );

    constexpr T pop();

    constexpr void clear()                        { heap.clear(); }
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