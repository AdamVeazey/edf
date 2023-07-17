/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Array.hpp>

#include <gtest/gtest.h>

class CustomClass {
private:
    int variable;
public:
    constexpr CustomClass( int initialValue = 0 ) : variable(initialValue) {}
    ~CustomClass() = default;
    static constexpr auto max() { return std::numeric_limits<int>::max(); }
};

/*****************************************************************************/

template<typename T, std::size_t N>
void EDFArrayIsSameSizeAsCStyleArray() {
    EXPECT_EQ( sizeof(EDF::Array<T, N>), sizeof(T[N]) );
}

TEST(Array, ArraySizeIsTheSameInt) {
    EDFArrayIsSameSizeAsCStyleArray<int, 0>();
    EDFArrayIsSameSizeAsCStyleArray<int, 1>();
    EDFArrayIsSameSizeAsCStyleArray<int, std::numeric_limits<int>::max()>();
}

TEST(Array, ArraySizeIsTheSameCustomClass) {
    EDFArrayIsSameSizeAsCStyleArray<CustomClass, 0>();
    EDFArrayIsSameSizeAsCStyleArray<CustomClass, 1>();
    EDFArrayIsSameSizeAsCStyleArray<CustomClass, CustomClass::max()>();
}

/*****************************************************************************/
