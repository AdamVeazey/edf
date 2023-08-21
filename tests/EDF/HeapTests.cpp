/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Heap.hpp>

#include <gtest/gtest.h>

class CustomClass {
private:
    int variable;
    bool otherVariable;
public:
    constexpr CustomClass( int initialValue = 0, bool ov = false ) : variable(initialValue), otherVariable(ov) {}
    ~CustomClass() = default;
    constexpr auto getValue() const { return variable; }
    constexpr friend bool operator>( const CustomClass& lhs, const CustomClass& rhs ) {
        return lhs.variable > rhs.variable;
    }
    constexpr friend bool operator<( const CustomClass& lhs, const CustomClass& rhs ) {
        return lhs.variable < rhs.variable;
    }
};

TEST(Heap, InitializationInt) {
    EDF::Heap<int, 32, std::less<int>> heapInt;
    EXPECT_EQ( heapInt.maxLength(), 32 );
    EXPECT_EQ( heapInt.length(), 0 );

    EDF::HeapMin<int, 4> heapIntMin = { 3, 1, -2 };
    EXPECT_EQ( heapIntMin.maxLength(), 4 );
    EXPECT_EQ( heapIntMin.length(), 3 );
    EXPECT_EQ( heapIntMin.pop(), -2 );
    EXPECT_EQ( heapIntMin.pop(), 1 );
    EXPECT_EQ( heapIntMin.pop(), 3 );
}

TEST(Heap, InitializationCustomClass) {
    EDF::Heap<CustomClass, 32, std::less<CustomClass>> heapCustomClass;
    EXPECT_EQ( heapCustomClass.maxLength(), 32 );
    EXPECT_EQ( heapCustomClass.length(), 0 );

    // when N is a power of two, this test fails? Only occurs in gtest? This works if copy pasted to example code
    EDF::HeapMax<CustomClass, 4> heapCustomClassMax = {
        CustomClass( 1 ),
        CustomClass( 2 ),
        CustomClass( 3 ),
    };
    EXPECT_EQ( heapCustomClassMax.maxLength(), 4 );
    EXPECT_EQ( heapCustomClassMax.length(), 3 );
    EXPECT_EQ( heapCustomClassMax.pop().getValue(), 3 );
    EXPECT_EQ( heapCustomClassMax.pop().getValue(), 2 );
    EXPECT_EQ( heapCustomClassMax.pop().getValue(), 1 );
}

TEST(Heap, IsEmpty) {
    EDF::HeapMin<int, 4> heap;
    EXPECT_TRUE( heap.isEmpty() );

    heap.push( 10 );
    EXPECT_FALSE( heap.isEmpty() );
}

TEST(Heap, IsFull) {
    EDF::HeapMin<int, 4> heap;
    EXPECT_FALSE( heap.isFull() );

    heap.push( 10 );
    heap.push( 11 );
    heap.push( 12 );
    heap.push( 13 );
    EXPECT_TRUE( heap.isFull() );
}

TEST(Heap, LengthInt) {
    EDF::HeapMin<int, 4> heap;

    EXPECT_EQ( heap.length(), 0 );
    heap.push( 1 );

    EXPECT_EQ( heap.length(), 1 );

    while( !heap.isFull() ) {
        heap.push( heap.peek() - 1 );
    }
    EXPECT_EQ( heap.length(), 4 );
    EXPECT_EQ( heap.length(), heap.maxLength() );
}

TEST(Heap, LengthCustomClass) {
    EDF::HeapMax<CustomClass, 4> heap;

    EXPECT_EQ( heap.length(), 0 );
    heap.push( 1 );

    EXPECT_EQ( heap.length(), 1 );

    while( !heap.isFull() ) {
        heap.push( heap.peek().getValue() + 1 );
    }
    EXPECT_EQ( heap.length(), 4 );
    EXPECT_EQ( heap.length(), heap.maxLength() );
}

TEST(Heap, MaxLength) {
    EDF::HeapMax<int, 4> heapInt4;
    EXPECT_EQ( heapInt4.maxLength(), 4 );

    EDF::HeapMin<CustomClass, 50> heapCustomClass50;
    EXPECT_EQ( heapCustomClass50.maxLength(), 50 );
}

TEST(Heap, Peek) {
    EDF::HeapMax<int, 4> heap = { 10 };
    EXPECT_EQ( heap.peek(), 10 );

    heap.push( 20 );
    EXPECT_EQ( heap.peek(), 20 );

    heap.push( 15 );
    EXPECT_EQ( heap.peek(), 20 );

    heap.push( 30 );
    EXPECT_EQ( heap.peek(), 30 );
}

TEST(Heap, Push) {
    EDF::HeapMin<int, 20> heapMin;
    heapMin.push( 10 );
    EXPECT_EQ( heapMin.peek(), 10 );

    int value5 = 5;
    heapMin.push( value5 );
    EXPECT_EQ( heapMin.peek(), value5 );

    while( !heapMin.isFull() ) {
        heapMin.push( heapMin.peek() - 1 );
    }
    EXPECT_DEATH( heapMin.push( 1 ), "" );

    EDF::HeapMax<int, 20> heapMax;
    heapMax.push( 2 );
    EXPECT_EQ( heapMax.peek(), 2 );

    heapMax.push( value5 );
    EXPECT_EQ( heapMax.peek(), value5 );

    EDF::HeapMin<CustomClass, 10> heapCustomClass;

    heapCustomClass.push( 50 );
    EXPECT_EQ( heapCustomClass.peek().getValue(), 50 );

    heapCustomClass.push( CustomClass( 25, false ) );
    EXPECT_EQ( heapCustomClass.peek().getValue(), 25 );

    heapCustomClass.push( CustomClass() );
    EXPECT_EQ( heapCustomClass.peek().getValue(), 0 );
}

TEST(Heap, Emplace) {
    EDF::HeapMin<CustomClass, 10> heap;

    heap.emplace( 50 );
    EXPECT_EQ( heap.peek().getValue(), 50 );

    heap.emplace( 25, false );
    EXPECT_EQ( heap.peek().getValue(), 25 );

    heap.emplace();
    EXPECT_EQ( heap.peek().getValue(), 0 );
}

TEST(Heap, Pop) {
    EDF::HeapMin<int, 4> heap = { 5, 10, 8, 3 };

    EXPECT_EQ( heap.pop(), 3 );
    EXPECT_EQ( heap.pop(), 5 );
    EXPECT_EQ( heap.pop(), 8 );
    EXPECT_EQ( heap.pop(), 10 );
}

TEST(Heap, Clear) {
    EDF::HeapMax<int, 4> heap = { 1, 2, 3, 1 };

    heap.clear();
    EXPECT_EQ( heap.length(), 0 );
}