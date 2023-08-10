/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Queue.hpp>

#include <gtest/gtest.h>

class CustomClass {
private:
    int variable;
    bool otherVariable;
public:
    constexpr CustomClass( int initialValue = 0, bool ov = false ) : variable(initialValue), otherVariable(ov) {}
    ~CustomClass() = default;
    constexpr auto getValue() const { return variable; }
};

TEST(Queue, InitializationInt) {
    EDF::Queue<int, 32> queueInt;
    EXPECT_EQ( queueInt.maxLength(), 31 );
    EXPECT_EQ( queueInt.length(), 0 );

    EDF::Queue<int, 8> queueIntIList = { 3, 2, 1 };
    EXPECT_EQ( queueIntIList.maxLength(), 7 );
    EXPECT_EQ( queueIntIList.length(), 3 );
    EXPECT_EQ( queueIntIList.peek(), 3 );
}

TEST(Queue, InitializationCustomClass) {
    EDF::Queue<CustomClass, 32> queueCustomClass;
    EXPECT_EQ( queueCustomClass.maxLength(), 31 );
    EXPECT_EQ( queueCustomClass.length(), 0 );

    EDF::Queue<CustomClass, 4> queueCustomClassIList( 3, 1, -2 );
    EXPECT_EQ( queueCustomClassIList.maxLength(), 3 );
    EXPECT_EQ( queueCustomClassIList.length(), 3 );
    EXPECT_EQ( queueCustomClassIList.peek().getValue(), 3 );
}

TEST(Queue, IsEmpty) {
    EDF::Queue<int, 4> queue;
    EXPECT_TRUE( queue.isEmpty() );

    queue.push( 10 );
    EXPECT_FALSE( queue.isEmpty() );
}

TEST(Queue, IsFull) {
    EDF::Queue<int, 4> queue;
    EXPECT_FALSE( queue.isFull() );

    queue.push( 10 );
    queue.push( 11 );
    queue.push( 12 );
    EXPECT_TRUE( queue.isFull() );
}

TEST(Queue, LengthInt) {
    EDF::Queue<int, 4> queue;
    EXPECT_EQ( queue.length(), 0 );

    queue.push( 1 );
    EXPECT_EQ( queue.length(), 1 );

    while( !queue.isFull() ) {
        queue.push( queue.length() );
    }
    EXPECT_EQ( queue.length(), 3 );
    EXPECT_EQ( queue.length(), queue.maxLength() );
}

TEST(Queue, LengthCustomClass) {
    EDF::Queue<CustomClass, 4> queue;
    EXPECT_EQ( queue.length(), 0 );

    queue.push( 1 );
    EXPECT_EQ( queue.length(), 1 );

    while( !queue.isFull() ) {
        queue.push( CustomClass( queue.length(), true ) );
    }
    EXPECT_EQ( queue.length(), 3 );
    EXPECT_EQ( queue.length(), queue.maxLength() );
}

TEST(Queue, MaxLength) {
    EDF::Queue<int, 4>  queueInt;
    EXPECT_EQ( queueInt.maxLength(), 3 );

    EDF::Queue<CustomClass, 50> queueCustomClass;
    EXPECT_EQ( queueCustomClass.maxLength(), 49 );
}

TEST(Queue, Peek) {
    EDF::Queue<int, 4> queue = { 10 };
    EXPECT_EQ( queue.peek(), 10 );

    queue.push( 20 );
    EXPECT_EQ( queue.peek(), 10 );
}

TEST(Queue, Push) {
    const int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    EDF::Queue<int, 16> queueInt;
    for( auto&& d : data ) {
        queueInt.push( d );
    }
    for( std::size_t k = 0; !queueInt.isEmpty(); ++k ) {
        EXPECT_EQ( queueInt.pop(), data[k] );
    }

    EDF::Queue<CustomClass, 16> queueCustomClass;
    queueCustomClass.push( 1 );
    EXPECT_EQ( queueCustomClass.pop().getValue(), 1 );

    queueCustomClass.push( CustomClass( 10, true ) );
    EXPECT_EQ( queueCustomClass.pop().getValue(), 10 );

    for( int k = 0; k < 10; ++k ) {
        queueCustomClass.push( k * 10 );
    }
    for( int k = 0; k < 10; ++k ) {
        EXPECT_EQ( queueCustomClass.pop().getValue(), k * 10 );
    }

    while( !queueCustomClass.isFull() ) {
        queueCustomClass.push( 0 );
    }
    EXPECT_DEATH( queueCustomClass.push( 0 ), "" );
}

TEST(Queue, Emplace) {
    EDF::Queue<CustomClass, 10> queue;

    queue.emplace( 50 );
    EXPECT_EQ( queue.pop().getValue(), 50 );

    queue.emplace( 25, false );
    EXPECT_EQ( queue.pop().getValue(), 25 );

    queue.emplace();
    EXPECT_EQ( queue.pop().getValue(), 0 );
}

TEST(Queue, Pop) {
    EDF::Queue<int, 8> queue = { 1, 2, 3, 4, 5 };

    EXPECT_EQ( queue.pop(), 1 );
    EXPECT_EQ( queue.pop(), 2 );
    EXPECT_EQ( queue.pop(), 3 );
    EXPECT_EQ( queue.pop(), 4 );
    EXPECT_EQ( queue.pop(), 5 );

    queue.push( 6 );
    queue.push( 7 );
    queue.push( 8 );
    queue.push( 9 );

    EXPECT_EQ( queue.pop(), 6 );
    EXPECT_EQ( queue.pop(), 7 );
    EXPECT_EQ( queue.pop(), 8 );
    EXPECT_EQ( queue.pop(), 9 );
}

TEST(Queue, Clear) {
    EDF::Queue<int, 4> queue = { 10, 20, 30 };

    queue.clear();
    EXPECT_EQ( queue.length(), 0 );
}

/* uint8_t specialized member functions */

TEST(Queue, PopBigEndian) {
    EDF::Queue<uint8_t, 17> queue = {
        (uint8_t)0x12,

        (uint8_t)0x12, (uint8_t)0x34,

        (uint8_t)0x12, (uint8_t)0x34, (uint8_t)0x56, (uint8_t)0x78,

        (uint8_t)0x12, (uint8_t)0x34, (uint8_t)0x56, (uint8_t)0x78,
        (uint8_t)0x9A, (uint8_t)0xBC, (uint8_t)0xDE, (uint8_t)0xF0,
    };
    EXPECT_EQ( queue.pop8be(), 0x12 );
    EXPECT_EQ( queue.pop16be(), 0x1234 );
    EXPECT_EQ( queue.pop32be(), 0x12345678 );
    EXPECT_EQ( queue.pop64be(), 0x123456789ABCDEF0 );
}

TEST(Queue, PopLittleEndian) {
    EDF::Queue<uint8_t, 17> queue = {
        (uint8_t)0x12,

        (uint8_t)0x34, (uint8_t)0x12,

        (uint8_t)0x78, (uint8_t)0x56, (uint8_t)0x34, (uint8_t)0x12,

        (uint8_t)0xF0, (uint8_t)0xDE, (uint8_t)0xBC, (uint8_t)0x9A,
        (uint8_t)0x78, (uint8_t)0x56, (uint8_t)0x34, (uint8_t)0x12,
    };
    EXPECT_EQ( queue.pop8le(), 0x12 );
    EXPECT_EQ( queue.pop16le(), 0x1234 );
    EXPECT_EQ( queue.pop32le(), 0x12345678 );
    EXPECT_EQ( queue.pop64le(), 0x123456789ABCDEF0 );
}