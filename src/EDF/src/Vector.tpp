/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "../Vector.hpp"

namespace EDF {

template<typename T, std::size_t N> void Vector<T, N>::
insert( Iterator pos, const T& value ) { 
    EDF_ASSERTD(pos >= begin());                // position must be valid
    EDF_ASSERTD(pos < end());                   // position must be valid
    EDF_ASSERTD(!isFull());                     // must have enough space for new element

    T elementAtEnd = back();                // copy last element to put back later
    for( ReverseIterator r = rbegin(); r != ReverseIterator(pos); ++r ){
        *r = *(r+1);                        // shift elements one by one
    }
    *pos = value;                           // insert new element at pos
    pushBack( elementAtEnd );        // put back last element
}

template<typename T, std::size_t N> void Vector<T, N>::
erase( Iterator pos ) {
    EDF_ASSERTD(pos >= begin());    // position must be valid
    EDF_ASSERTD(pos < end());       // position must be valid

    for( ; pos != end(); ++pos ){
        *pos = *(pos + 1);          // shift elements one by one
    }
    --n;                            // decrement length by 1
}

template<typename T, std::size_t N>
template<typename... Args> 
void Vector<T, N>::
emplaceBack(Args&&... args) {
    EDF_ASSERTD(!isFull()); // must have enough space for new element
    // use placement new
    new (end()) T(std::forward<Args>(args)...); 
    ++n;
}

} /* EDF */