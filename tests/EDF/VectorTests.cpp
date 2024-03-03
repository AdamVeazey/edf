/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Vector.hpp>

#include <gtest/gtest.h>

class CustomClass {
private:
    int variable;
    bool otherVariable;
public:
    constexpr CustomClass( int initialValue = 0, bool ov = false ) : variable(initialValue), otherVariable(ov) {}
    ~CustomClass() = default;
    constexpr int getValue() const { (void)otherVariable; return variable; }
};

TEST(Vector, InitializationInt) {
    EDF::Vector<int, 32> vectorInt;
    EXPECT_EQ( vectorInt.maxLength(), 32 );
    EXPECT_EQ( vectorInt.length(), 0 );

    EDF::Vector<int, 8> vectorIntIList = { 3, 2, 1 };
    EXPECT_EQ( vectorIntIList.maxLength(), 8 );
    EXPECT_EQ( vectorIntIList.length(), 3 );
    EXPECT_EQ( vectorIntIList[0], 3 );
    EXPECT_EQ( vectorIntIList[1], 2 );
    EXPECT_EQ( vectorIntIList[2], 1 );
}

TEST(Vector, InitializationCustomClass) {
    EDF::Vector<CustomClass, 32> vectorCustomClass;
    EXPECT_EQ( vectorCustomClass.maxLength(), 32 );
    EXPECT_EQ( vectorCustomClass.length(), 0 );

    EDF::Vector<CustomClass, 8> vectorIntIList = {
        CustomClass( 3 ),
        CustomClass( 2 ),
        CustomClass( 1 )
    };
    EXPECT_EQ( vectorIntIList.maxLength(), 8 );
    EXPECT_EQ( vectorIntIList.length(), 3 );
    EXPECT_EQ( vectorIntIList[0].getValue(), 3 );
    EXPECT_EQ( vectorIntIList[1].getValue(), 2 );
    EXPECT_EQ( vectorIntIList[2].getValue(), 1 );
}

TEST(Vector, IsEmpty) {
    EDF::Vector<int, 4> vector;
    EXPECT_TRUE( vector.isEmpty() );

    vector.pushBack( 0 );
    EXPECT_FALSE( vector.isEmpty() );
}

TEST(Vector, IsFull) {
    EDF::Vector<int, 4> vector;
    EXPECT_FALSE( vector.isFull() );

    vector.pushBack( 10 );
    vector.pushBack( 11 );
    vector.pushBack( 12 );
    vector.pushBack( 13 );
    EXPECT_TRUE( vector.isFull() );
}

TEST(Vector, LengthInt) {
    EDF::Vector<int, 4> vector;
    EXPECT_EQ( vector.length(), 0 );

    vector.pushBack( 1 );
    EXPECT_EQ( vector.length(), 1 );

    while( !vector.isFull() ) {
        vector.pushBack( vector.back() + 1 );
    }
    EXPECT_EQ( vector.length(), 4 );
    EXPECT_EQ( vector.length(), vector.maxLength() );
}

TEST(Vector, LengthCustomClass) {
    EDF::Vector<CustomClass, 4> vector;
    vector.pushBack( 1 );
    EXPECT_EQ( vector.length(), 1 );

    while( !vector.isFull() ) {
        vector.pushBack( vector.back().getValue() + 1 );
    }
    EXPECT_EQ( vector.length(), 4 );
    EXPECT_EQ( vector.length(), vector.maxLength() );
}

TEST(Vector, MaxLength) {
    EDF::Vector<int, 4> vectorInt;
    EXPECT_EQ( vectorInt.maxLength(), 4 );

    EDF::Vector<CustomClass, 4> vectorCustomClass;
    EXPECT_EQ( vectorCustomClass.maxLength(), 4 );
}

TEST(Vector, At) {
    EDF::Vector<int, 4> vector = { 1, 2, 3, 4 };
    EXPECT_EQ( vector.at( 0 ), 1 );
    EXPECT_EQ( vector.at( 1 ), 2 );
    EXPECT_EQ( vector.at( 2 ), 3 );
    EXPECT_EQ( vector.at( 3 ), 4 );

    EXPECT_DEATH( vector.at( 4 ), "" );

    vector.at( 0 ) = 10;
    EXPECT_EQ( vector.at( 0 ), 10 );
}

TEST(Vector, OperatorIndex) {
    EDF::Vector<int, 4> vector = { 1, 2, 3, 4 };
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 3 );
    EXPECT_EQ( vector[3], 4 );

    vector[0] = 10;
    EXPECT_EQ( vector[0], 10 );
}

TEST(Vector, Front) {
    EDF::Vector<int, 4> vector;
    EXPECT_DEATH( vector.front(), "" );

    vector.pushBack( 1 );
    EXPECT_EQ( vector.front(), 1 );

    vector.front() = 10;
    EXPECT_EQ( vector.front(), 10 );

    vector.pushBack( 20 );
    EXPECT_EQ( vector.front(), 10 );
}

TEST(Vector, Back) {
    EDF::Vector<int, 4> vector;
    EXPECT_DEATH( vector.back(), "" );

    vector.pushBack( 1 );
    EXPECT_EQ( vector.back(), 1 );

    vector.back() = 10;
    EXPECT_EQ( vector.back(), 10 );

    vector.pushBack( 20 );
    EXPECT_EQ( vector.back(), 20 );
}

TEST(Vector, Data) {
    EDF::Vector<int, 4> vector;
    EXPECT_EQ( vector.data(), &vector[0] );
    EXPECT_EQ( vector.data(), vector.begin() );
    EXPECT_EQ( vector.data(), vector.end() );

    vector.pushBack( 1 );
    EXPECT_EQ( *vector.data(), 1 );
    EXPECT_EQ( vector.data()[0], 1 );

    vector.pushBack( 2 );
    EXPECT_EQ( *(vector.data() + 1), 2 );
    EXPECT_EQ( vector.data()[1], 2 );
}

TEST(Vector, Clear) {
    EDF::Vector<int, 4> vector = { 1, 2, 3, 4 };
    EXPECT_EQ( vector.length(), 4 );

    vector.clear();
    EXPECT_EQ( vector.length(), 0 );
}

TEST(Vector, InsertValueByIndex) {
    EDF::Vector<int, 4> vector;

    vector.insert( 0_uz, 3 );
    vector.insert( 1_uz, 4 );
    vector.insert( 0_uz, 2 );
    int x = 1;
    vector.insert( 0_uz, x );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 3 );
    EXPECT_EQ( vector[3], 4 );
}

TEST(Vector, InsertXValuesByIndex) {
    EDF::Vector<int, 8> vector;

    vector.insert( 0_uz, 4, 1 );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 1 );
    EXPECT_EQ( vector[2], 1 );
    EXPECT_EQ( vector[3], 1 );

    vector.insert( 4_uz, 2, 2 );
    EXPECT_EQ( vector[4], 2 );
    EXPECT_EQ( vector[5], 2 );

    vector.insert( 2_uz, 2, 3 );
    EXPECT_EQ( vector[2], 3 );
    EXPECT_EQ( vector[3], 3 );
}

TEST(Vector, InsertInitializerListByIndex) {
    EDF::Vector<int, 8> vector;

    vector.insert( 0_uz, { 1, 7, 8 } );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 7 );
    EXPECT_EQ( vector[2], 8 );

    vector.insert( 1_uz, { 2, 3 } );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 3 );

    vector.insert( 3_uz, { 4, 5, 6 } );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 3 );
    EXPECT_EQ( vector[3], 4 );
    EXPECT_EQ( vector[4], 5 );
    EXPECT_EQ( vector[5], 6 );
    EXPECT_EQ( vector[6], 7 );
    EXPECT_EQ( vector[7], 8 );
}

TEST(Vector, InsertValueByIterator) {
    EDF::Vector<int, 4> vector;

    vector.insert( vector.begin(), 3 );
    vector.insert( vector.begin() + 1, 4 );
    vector.insert( vector.begin(), 2 );
    int x = 1;
    vector.insert( vector.begin(), x );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 3 );
    EXPECT_EQ( vector[3], 4 );
}

TEST(Vector, InsertXValuesByIterator) {
    EDF::Vector<int, 8> vector;

    vector.insert( vector.begin(), 4, 1 );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 1 );
    EXPECT_EQ( vector[2], 1 );
    EXPECT_EQ( vector[3], 1 );

    vector.insert( vector.begin() + 4, 2, 2 );
    EXPECT_EQ( vector[4], 2 );
    EXPECT_EQ( vector[5], 2 );

    vector.insert( vector.begin() + 2, 2, 3 );
    EXPECT_EQ( vector[2], 3 );
    EXPECT_EQ( vector[3], 3 );
}

TEST(Vector, InsertInitializerListByIterator) {
    EDF::Vector<int, 8> vector;

    vector.insert( vector.begin(), { 1, 7, 8 } );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 7 );
    EXPECT_EQ( vector[2], 8 );

    vector.insert( vector.begin() + 1, { 2, 3 } );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 3 );

    vector.insert( vector.begin() + 3, { 4, 5, 6 } );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 3 );
    EXPECT_EQ( vector[3], 4 );
    EXPECT_EQ( vector[4], 5 );
    EXPECT_EQ( vector[5], 6 );
    EXPECT_EQ( vector[6], 7 );
    EXPECT_EQ( vector[7], 8 );
}

TEST(Vector, Emplace) {
    EDF::Vector<int, 4> vectorInt;
    vectorInt.emplace( 0_uz, 1 );
    vectorInt.emplace( vectorInt.begin() + 1, 2 );
    EXPECT_EQ( vectorInt[0], 1 );
    EXPECT_EQ( vectorInt[1], 2 );

    EDF::Vector<CustomClass, 4> vectorCustomClass;
    vectorCustomClass.emplace( 0_uz, 1 );
    vectorCustomClass.emplace( vectorCustomClass.begin() + 1, 2, true );
    EXPECT_EQ( vectorCustomClass[0].getValue(), 1 );
    EXPECT_EQ( vectorCustomClass[1].getValue(), 2 );
}

TEST(Vector, EraseByIndex) {
    EDF::Vector<int, 4> vector = { 1, 2, 3, 4 };
    EXPECT_EQ( vector.length(), 4 );

    vector.erase( 2_uz );
    EXPECT_EQ( vector.length(), 3 );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 4 );

    vector.erase( 1_uz, vector.length() );
    EXPECT_EQ( vector.length(), 1 );
    EXPECT_EQ( vector[0], 1 );
}

TEST(Vector, EraseByIterator) {
    EDF::Vector<int, 4> vector = { 1, 2, 3, 4 };
    EXPECT_EQ( vector.length(), 4 );

    vector.erase( vector.begin() + 2 );
    EXPECT_EQ( vector.length(), 3 );
    EXPECT_EQ( vector[0], 1 );
    EXPECT_EQ( vector[1], 2 );
    EXPECT_EQ( vector[2], 4 );

    vector.erase( vector.begin() + 1, vector.end() );
    EXPECT_EQ( vector.length(), 1 );
    EXPECT_EQ( vector[0], 1 );
}

TEST(Vector, PushBack) {
    EDF::Vector<int, 4> vector;
    EXPECT_EQ( vector.length(), 0 );

    vector.pushBack( 1 );
    EXPECT_EQ( vector.length(), 1 );
    EXPECT_EQ( vector[0], 1 );

    vector.pushBack( 2 );
    EXPECT_EQ( vector.length(), 2 );
    EXPECT_EQ( vector[1], 2 );

    int x = 3;
    vector.pushBack( x );
    EXPECT_EQ( vector.length(), 3 );
    EXPECT_EQ( vector[2], 3 );
}

TEST(Vector, EmplaceBack) {
    EDF::Vector<int, 4> vectorInt;
    EXPECT_EQ( vectorInt.length(), 0 );

    vectorInt.emplaceBack( 1 );
    EXPECT_EQ( vectorInt.length(), 1 );
    EXPECT_EQ( vectorInt[0], 1 );

    vectorInt.emplaceBack( 2 );
    EXPECT_EQ( vectorInt.length(), 2 );
    EXPECT_EQ( vectorInt[1], 2 );

    int x = 3;
    vectorInt.emplaceBack( x );
    EXPECT_EQ( vectorInt.length(), 3 );
    EXPECT_EQ( vectorInt[2], 3 );

    EDF::Vector<CustomClass, 4> vectorCustomClass;
    EXPECT_EQ( vectorCustomClass.length(), 0 );

    vectorCustomClass.emplaceBack( 1 );
    EXPECT_EQ( vectorCustomClass.length(), 1 );
    EXPECT_EQ( vectorCustomClass[0].getValue(), 1 );

    vectorCustomClass.emplaceBack( 2, true );
    EXPECT_EQ( vectorCustomClass.length(), 2 );
    EXPECT_EQ( vectorCustomClass[1].getValue(), 2 );

    CustomClass c( 3 );
    vectorCustomClass.emplaceBack( c );
    EXPECT_EQ( vectorCustomClass.length(), 3 );
    EXPECT_EQ( vectorCustomClass[2].getValue(), 3 );
}

TEST(Vector, PopBack) {
    EDF::Vector<int, 4> vector = { 1, 2, 3, 4 };

    EXPECT_EQ( vector.popBack(), 4 );
    EXPECT_EQ( vector.popBack(), 3 );
    EXPECT_EQ( vector.popBack(), 2 );

    vector.pushBack( 2 );
    EXPECT_EQ( vector.popBack(), 2 );
    EXPECT_EQ( vector.popBack(), 1 );
}

TEST(Vector, BeginEnd) {
    EDF::Vector<int, 4> array{ 1, 2, 3, 4 };

    auto begin = array.begin();
    auto end = array.end();
    EXPECT_EQ( *begin, 1 );
    EXPECT_EQ( *(end - 1), 4 );

    const auto& cbegin = array.cbegin();
    const auto& cend = array.cend();
    EXPECT_EQ( *cbegin, 1 );
    EXPECT_EQ( *(cend - 1), 4 );
}

TEST(Vector, ReverseBeginEnd) {
    EDF::Vector<int, 4> array{ 1, 2, 3, 4 };

    auto rbegin = array.rbegin();
    auto rend = array.rend();
    EXPECT_EQ( *rbegin, 4 );
    EXPECT_EQ( *(rend - 1), 1 );

    const auto& crbegin = array.crbegin();
    const auto& crend = array.crend();
    EXPECT_EQ( *crbegin, 4 );
    EXPECT_EQ( *(crend - 1), 1 );
}