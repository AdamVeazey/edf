/*
 * Copyright (c) 2023, Adam Veazey
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
    // Starting from the last non-leaf node, perform bubbleDown to build the heap
    // Leaf nodes are already heaps, so we don't need to consider them (index < N/2)
    for( int k = sizeof...(I) / 2; k > 0; --k ){
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
    heap.pushBack( value );
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
    T topCopy = heap.front();
    heap.front() = heap.back();
    heap.popBack();
    bubbleDown( 0 );
    return topCopy;
}

} /* EDF */