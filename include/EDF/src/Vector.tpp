/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Vector.hpp"

namespace EDF {

template<typename T, std::size_t N>
template<typename... I>
constexpr Vector<T, N>::
Vector( I... iList ) : n(sizeof...(I)) {
    static_assert(sizeof...(I) <= N, "Initializer list exceeds vector capacity");
    T init[] = { iList... };
    for( std::size_t k = 0; k < sizeof...(I); ++k ) {
        new (data() + k) T( std::move(init[k]) );
    }
}

template<typename T, std::size_t N>
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
insert( ConstIterator pos, std::size_t count, const T& value ) {
    EDF_ASSERTD(pos >= begin(), "position must be valid");
    EDF_ASSERTD(pos <= end(), "position must be valid");
    EDF_ASSERTD((end() + count) <= (begin() + maxLength()), "new values must be able to fit");

    Iterator position = begin() + (pos - begin());
    if( position != end() ) {
        for( std::size_t k = 0; k < count; ++k ) {
            emplace( position, value );
        }
    }
    else {
        for( std::size_t k = 0; k < count; ++k ) {
            new (end()) T(value);
            ++n;
        }
    }
    return position;
}

template<typename T, std::size_t N>
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
insert( ConstIterator pos, std::initializer_list<T> iList ) {
    EDF_ASSERTD(pos >= begin(), "position must be valid");
    EDF_ASSERTD(pos <= end(), "position must be valid");
    EDF_ASSERTD((end() + iList.size()) <= (begin() + maxLength()), "new values must be able to fit");

    Iterator position = begin() + (pos - begin());
    for( const auto& item : iList ) {
        position = emplace( position, item ) + 1;
    }
    return position - iList.size();
}

template<typename T, std::size_t N>
template<typename... Args>
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
emplace( ConstIterator pos, Args&&... args ) {
    EDF_ASSERTD(pos >= begin(), "position must be valid");
    EDF_ASSERTD(pos <= end(), "position must be valid");
    EDF_ASSERTD(!isFull(), "must have enough space for new element");

    Iterator position = begin() + (pos - begin());

    if (position == end()) {
        new (position) T( std::forward<Args>(args)... );
    }
    else {
        new (end()) T(std::move(*(end() - 1)));
        std::move_backward( position, end() - 1, end() );
        position->~T();
        new (position) T( std::forward<Args>(args)... );
    }

    ++n;
    return position;
}

template<typename T, std::size_t N>
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
erase( ConstIterator pos ) {
    EDF_ASSERTD(pos >= begin(), "position must be valid");
    EDF_ASSERTD(pos < end(), "position must be valid");

    Iterator position = begin() + (pos - begin());
    position->~T();

    // Safe left-shift loop for raw storage
    for( Iterator it = position; it + 1 < end(); ++it ) {
        new (it) T( std::move(*(it + 1)) );
        (it + 1)->~T();
    }

    --n;
    return position;
}

template<typename T, std::size_t N>
constexpr typename Vector<T, N>::Iterator Vector<T, N>::
erase( ConstIterator first, ConstIterator last ) {
    EDF_ASSERTD(first >= begin(), "first position must be valid");
    EDF_ASSERTD(first <= last, "first position must be less than last");
    EDF_ASSERTD(first < end(), "first position must not include end()");
    EDF_ASSERTD(last  >= first, "last position must be valid");
    EDF_ASSERTD(last  <= end(), "last position must be valid");

    Iterator s = begin() + (first - begin());
    Iterator e = begin() + (last - begin());

    std::size_t count = e - s;

    // Destruct elements to be erased
    std::destroy(s, e);

    // Shift remaining elements left safely
    Iterator dest = s;
    Iterator src = e;
    while (src != end()) {
        new (dest) T(std::move(*src));
        src->~T();
        ++dest;
        ++src;
    }

    n -= count;
    return s;
}

} /* EDF */