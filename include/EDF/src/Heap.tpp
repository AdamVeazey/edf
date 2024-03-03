/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Heap.hpp"
#include "EDF/Assert.hpp"

namespace EDF {

template<typename T, std::size_t N, typename Compare>
constexpr void Heap<T, N, Compare>::
bubbleUp( std::size_t index ) {
    while( index != 0 ) {
        std::size_t parentIndex = (index - 1) / 2;
        if( !Compare()( heap[parentIndex], heap[index] ) ) {
            std::swap( heap[parentIndex], heap[index] );
            index = parentIndex;
        }
        else{
            break;
        }
    }
}

template<typename T, std::size_t N, typename Compare>
constexpr void Heap<T, N, Compare>::
bubbleDown( std::size_t index ) {
    while( true ) {
        std::size_t leftChild = 2 * index + 1;
        std::size_t rightChild = leftChild + 1;
        std::size_t topIndex = index;

        if( (leftChild < heap.length()) && Compare()(heap[leftChild], heap[topIndex]) ) {
            topIndex = leftChild;
        }
        if( (rightChild < heap.length()) && Compare()(heap[rightChild], heap[topIndex]) ) {
            topIndex = rightChild;
        }
        if( topIndex == index ) {
            break;
        }
        std::swap(heap[index], heap[topIndex]);
        index = topIndex;
    }
}

template<typename T, std::size_t N, typename Compare>
template<typename... I>
constexpr Heap<T,N,Compare>::
Heap( I... iList ) : heap{iList...} {
    for( std::size_t k = length() / 2; k > 0; --k ) {
        bubbleDown( k - 1 );
    }
}

template<typename T, std::size_t N, typename Compare>
constexpr void Heap<T, N, Compare>::
push( const T& value ) {
    EDF_ASSERTD( !isFull() );
    heap.pushBack( value );
    bubbleUp( heap.length() - 1 );
}

template<typename T, std::size_t N, typename Compare>
constexpr void Heap<T, N, Compare>::
push( const T&& value ) {
    EDF_ASSERTD( !isFull() );
    heap.pushBack( std::move(value) );
    bubbleUp( heap.length() - 1 );
}

template<typename T, std::size_t N, typename Compare>
template<typename... Args>
constexpr T& Heap<T, N, Compare>::
emplace( Args&&... args ) {
    EDF_ASSERTD( !isFull() );
    auto& value = heap.emplaceBack( std::forward<Args>(args)... );
    bubbleUp( heap.length() - 1 );
    return value;
}

template<typename T, std::size_t N, typename Compare>
constexpr T Heap<T, N, Compare>::
pop() {
    EDF_ASSERTD( !isEmpty() );
    T topValue = std::move(heap.front());
    heap.front() = std::move(heap.back());
    heap.popBack();
    bubbleDown( 0 );
    return topValue;
}

} /* EDF */