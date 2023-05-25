/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "../Vector.hpp"

namespace EDF {

template<typename T, std::size_t N> constexpr typename Vector<T, N>::Iterator Vector<T, N>::
insert( ConstIterator pos, T&& value ) { 
    EDF_ASSERTD(pos >= begin());    // position must be valid
    EDF_ASSERTD(pos < end());       // position must be valid
    EDF_ASSERTD(!isFull());         // must have enough space for new element

    Iterator position = begin() + (pos - begin());
    std::move_backward( position, end(), end() + 1 );
    *position = std::move(value);   // insert new element at pos
    ++n;
    return position;                // iterator pointing to the inserted value
}

template<typename T, std::size_t N> constexpr typename Vector<T, N>::Iterator Vector<T, N>::
insert( ConstIterator pos, std::size_t count, const T& value ) {
    EDF_ASSERTD(pos >= begin());                // position must be valid
    EDF_ASSERTD(pos <= end());                  // position must be valid
    EDF_ASSERTD((end() + count) <= (begin() + maxLength())); // new values must be able to fit
    
    Iterator position = begin() + (pos - begin());
    std::move_backward( position, end(), end() + count );
    std::fill_n( position, count, value );
    n += count;
    return position;
}

template<typename T, std::size_t N> constexpr typename Vector<T, N>::Iterator Vector<T, N>::
insert( ConstIterator pos, std::initializer_list<T> iList ) {
    EDF_ASSERTD(pos >= begin());                // position must be valid
    EDF_ASSERTD(pos <= end());                  // position must be valid
    EDF_ASSERTD((end() + iList.size()) <= (begin() + maxLength())); // new values must be able to fit

    Iterator position = begin() + (pos - begin());
    std::move_backward( position, end(), end() + iList.size() );
    std::copy(iList.begin(), iList.end(), position);
    n += iList.size();
    return position;
}

template<typename T, std::size_t N>
template<typename... Args>
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
emplace( ConstIterator pos, Args&&... args ) {
    EDF_ASSERTD(pos >= begin());    // position must be valid
    EDF_ASSERTD(pos <= end());      // position must be valid
    EDF_ASSERTD(!isFull());         // must have enough space for new element
    
    Iterator position = begin() + (pos - begin());
    std::move_backward( position, end(), end() + 1 );
    new (position) T(std::forward<Args>(args)...);
    ++n;
    return position;
}

template<typename T, std::size_t N> 
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
erase( ConstIterator pos ) {
    EDF_ASSERTD(pos >= begin());    // position must be valid
    EDF_ASSERTD(pos < end());       // position must be valid

    Iterator position = begin() + (pos - begin());
    position->~T(); // destruct element being erase
    std::move_backward( position + 1, end(), end() - 1 );
    --n;            // decrement length by 1
    return position;
}

template<typename T, std::size_t N> 
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
erase( ConstIterator first, ConstIterator last ) {
    EDF_ASSERTD(first >= begin());  // first position must be valid
    EDF_ASSERTD(first <= last);     // first position must be less than last
    EDF_ASSERTD(first < end());     // first position must not include end()
    EDF_ASSERTD(last  >= first);    // last position must be valid
    EDF_ASSERTD(last  <= end());    // last position must be valid

    // "convert" const iterator to iterator
    Iterator s = begin() + (first - begin());
    Iterator e = begin() + (last - begin());
    
    // destruct elements to be erased
    std::destroy(s, e);

    // shift elements to the 'left'
    std::move_backward( e, end(), s + (end() - last) );

    // remove number of elements from container
    n -= (e - s);
    return s;
}

} /* EDF */