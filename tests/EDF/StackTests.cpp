/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Stack.hpp>

#include <gtest/gtest.h>

class CustomClass {
private:
    int variable;
    bool otherVariable;
public:
    constexpr CustomClass( int initialValue = 0, bool ov = false ) : variable(initialValue), otherVariable(ov) {}
    ~CustomClass() = default;
    constexpr auto getValue() const { (void)otherVariable; return variable; }
};

TEST(Stack, InitializationInt) {
    EDF::Stack<int, 32> stackInt;
    EXPECT_EQ( stackInt.maxLength(), 32 );
    EXPECT_EQ( stackInt.length(), 0 );

    EDF::Stack<int, 8> stackIntIList = { 3, 2, 1 };
    EXPECT_EQ( stackIntIList.maxLength(), 8 );
    EXPECT_EQ( stackIntIList.length(), 3 );
    EXPECT_EQ( stackIntIList.peek(), 1 );
}

TEST(Stack, InitializationCustomClass) {
    EDF::Stack<CustomClass, 32> stackCustomClass;
    EXPECT_EQ( stackCustomClass.maxLength(), 32 );
    EXPECT_EQ( stackCustomClass.length(), 0 );

    EDF::Stack<CustomClass, 4> stackCustomClassIList = {
        CustomClass( 3 ),
        CustomClass( 1 ),
        CustomClass( -2 )
    };
    EXPECT_EQ( stackCustomClassIList.maxLength(), 4 );
    EXPECT_EQ( stackCustomClassIList.length(), 3 );
    EXPECT_EQ( stackCustomClassIList.peek().getValue(), -2 );
}

TEST(Stack, IsEmpty) {
    EDF::Stack<int, 4> stack;
    EXPECT_TRUE( stack.isEmpty() );

    stack.push( 0 );
    EXPECT_FALSE( stack.isEmpty() );
}

TEST(Stack, IsFull) {
    EDF::Stack<int, 4> stack;
    EXPECT_FALSE( stack.isFull() );

    stack.push( 10 );
    stack.push( 11 );
    stack.push( 12 );
    stack.push( 13 );
    EXPECT_TRUE( stack.isFull() );
}

TEST(Stack, LengthInt) {
    EDF::Stack<int, 4> stack;
    EXPECT_EQ( stack.length(), 0 );

    stack.push( 1 );
    EXPECT_EQ( stack.length(), 1 );

    while( !stack.isFull() ) {
        stack.push( stack.peek() + 1 );
    }
    EXPECT_EQ( stack.length(), 4 );
    EXPECT_EQ( stack.length(), stack.maxLength() );
}

TEST(Stack, LengthCustomClass) {
    EDF::Stack<CustomClass, 4> stack;
    EXPECT_EQ( stack.length(), 0 );

    stack.push( 1 );
    EXPECT_EQ( stack.length(), 1 );

    while( !stack.isFull() ) {
        stack.push( stack.peek().getValue() + 1 );
    }
    EXPECT_EQ( stack.length(), 4 );
    EXPECT_EQ( stack.length(), stack.maxLength() );
}

TEST(Stack, MaxLength) {
    EDF::Stack<int, 4> stackInt;
    EXPECT_EQ( stackInt.maxLength(), 4 );

    EDF::Stack<CustomClass, 4> stackCustomClass;
    EXPECT_EQ( stackCustomClass.maxLength(), 4 );
}

TEST(Stack, Peek) {
    EDF::Stack<int, 4> stack = { 10 };
    EXPECT_EQ( stack.peek(), 10 );

    stack.push( 20 );
    EXPECT_EQ( stack.peek(), 20 );

    stack.push( 15 );
    EXPECT_EQ( stack.peek(), 15 );

    stack.push( 30 );
    EXPECT_EQ( stack.peek(), 30 );
}

TEST(Stack, Push) {
    EDF::Stack<int, 20> stackInt;
    stackInt.push( 10 );
    EXPECT_EQ( stackInt.peek(), 10 );

    int value5 = 5;
    stackInt.push( value5 );
    EXPECT_EQ( stackInt.peek(), value5 );

    while( !stackInt.isFull() ) {
        stackInt.push( stackInt.peek() - 1 );
    }
    EXPECT_DEATH( stackInt.push( 1 ), "" );

    EDF::Stack<CustomClass, 10> stackCustomClass;

    stackCustomClass.push( 50 );
    EXPECT_EQ( stackCustomClass.peek().getValue(), 50 );

    stackCustomClass.push( CustomClass( 25, false ) );
    EXPECT_EQ( stackCustomClass.peek().getValue(), 25 );

    stackCustomClass.push( CustomClass() );
    EXPECT_EQ( stackCustomClass.peek().getValue(), 0 );
}

TEST(Stack, Emplace) {
    EDF::Stack<CustomClass, 10> stack;

    stack.emplace( 50 );
    EXPECT_EQ( stack.peek().getValue(), 50 );

    stack.emplace( 25, false );
    EXPECT_EQ( stack.peek().getValue(), 25 );

    stack.emplace();
    EXPECT_EQ( stack.peek().getValue(), 0 );
}

TEST(Stack, Pop) {
    EDF::Stack<int, 4> stack = { 5, 10, 8, 3 };

    EXPECT_EQ( stack.pop(), 3 );
    EXPECT_EQ( stack.pop(), 8 );
    EXPECT_EQ( stack.pop(), 10 );
    EXPECT_EQ( stack.pop(), 5 );
}

TEST(Stack, Clear) {
    EDF::Stack<int, 4> stack = { 1, 2, 3, 1 };

    stack.clear();
    EXPECT_EQ( stack.length(), 0 );
}