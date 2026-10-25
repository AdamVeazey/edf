/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Array.hpp>

#include <cstddef>
#include <gtest/gtest.h>

class CustomClass {
private:
    int variable;
public:
    constexpr CustomClass( int initialValue = 0 ) : variable(initialValue) {}
    ~CustomClass() = default;
    constexpr auto getValue() const { return variable; }
    static constexpr auto max() { return std::numeric_limits<int>::max(); }
};

class CustomClassNoDefaultConstructor {
private:
    int variable;
public:
    constexpr CustomClassNoDefaultConstructor( int initialValue ) : variable(initialValue) {}
    ~CustomClassNoDefaultConstructor() = default;
    constexpr auto getValue() const { return variable; }
    static constexpr auto max() { return std::numeric_limits<int>::max(); }
};

template<typename T, std::size_t N>
void EDFArrayIsSameSizeAsCStyleArray() {
    EXPECT_EQ( sizeof(EDF::Array<T, N>), sizeof(T[N]) );
}

TEST(Array, ArraySizeIsTheSameInt) {
    EDFArrayIsSameSizeAsCStyleArray<int, 1>();
    EDFArrayIsSameSizeAsCStyleArray<int, std::numeric_limits<int>::max()>();
}

TEST(Array, ArraySizeIsTheSameCustomClass) {
    EDFArrayIsSameSizeAsCStyleArray<CustomClass, 1>();
    EDFArrayIsSameSizeAsCStyleArray<CustomClass, CustomClass::max()>();
}

TEST(Array, DefaultConstructor) {
    EDF::Array<int, 16> arrayInt;
    EXPECT_EQ(arrayInt.maxLength(), 16);
    EXPECT_EQ(arrayInt[0], int{});
    EXPECT_EQ(arrayInt[15], int{});

    EDF::Array<float, 16> arrayFloat;
    EXPECT_EQ(arrayFloat.maxLength(), 16);
    EXPECT_EQ(arrayFloat[0], float{});
    EXPECT_EQ(arrayFloat[15], float{});

    EDF::Array<CustomClass, 16> arrayCustomClass;
    EXPECT_EQ(arrayCustomClass.maxLength(), 16);
    EXPECT_EQ(arrayCustomClass[0].getValue(), CustomClass().getValue());
    EXPECT_EQ(arrayCustomClass[15].getValue(), CustomClass().getValue());

    // EDF::Array<CustomClassNoDefaultConstructor, 16> CustomClassNoDefaultConstructor;
    // without a default constructor defined for the class, Array cannot be default constructed
}

TEST(Array, InitializerList) {
    EDF::Array<int, 4> arrayFullListGiven{ 1, 2, 3, 4 };
    EXPECT_EQ(arrayFullListGiven.maxLength(), 4);
    EXPECT_EQ(arrayFullListGiven[0], int{1});
    EXPECT_EQ(arrayFullListGiven[1], int{2});
    EXPECT_EQ(arrayFullListGiven[2], int{3});
    EXPECT_EQ(arrayFullListGiven[3], int{4});

    EDF::Array<CustomClass, 4> arrayNotAFullListGiven{ 1, 2, 3 };
    EXPECT_EQ(arrayNotAFullListGiven.maxLength(), 4);
    EXPECT_EQ(arrayNotAFullListGiven[0].getValue(), CustomClass(1).getValue());
    EXPECT_EQ(arrayNotAFullListGiven[1].getValue(), CustomClass(2).getValue());
    EXPECT_EQ(arrayNotAFullListGiven[2].getValue(), CustomClass(3).getValue());
    EXPECT_EQ(arrayNotAFullListGiven[3].getValue(), CustomClass().getValue());

    EDF::Array<CustomClassNoDefaultConstructor, 4> arrayNoDefaultConstructor{ 1, 2, 3, 4 };
    EXPECT_EQ(arrayNoDefaultConstructor.maxLength(), 4);
    EXPECT_EQ(arrayNoDefaultConstructor[0].getValue(), CustomClassNoDefaultConstructor(1).getValue());
    EXPECT_EQ(arrayNoDefaultConstructor[1].getValue(), CustomClassNoDefaultConstructor(2).getValue());
    EXPECT_EQ(arrayNoDefaultConstructor[2].getValue(), CustomClassNoDefaultConstructor(3).getValue());
    EXPECT_EQ(arrayNoDefaultConstructor[3].getValue(), CustomClassNoDefaultConstructor(4).getValue());
}

TEST(Array, At_ValidIndex) {
    EDF::Array<int, 4> array = { 5, 6, 7, 8 };

    EXPECT_EQ( array.at(0), 5 );
    EXPECT_EQ( array.at(1), 6 );
    EXPECT_EQ( array.at(2), 7 );
    EXPECT_EQ( array.at(3), 8 );

    array.at( 2 ) = 10;
    EXPECT_EQ( array.at(2), 10 );

    int& ref = array.at( 2 );
    EXPECT_EQ( ref, 10 );

    ref = 20;
    EXPECT_EQ( array.at(2), 20 );

    const int& refConst = array.at( 2 );
    EXPECT_EQ( refConst, 20 );
}

TEST(Array, At_InvalidIndex) {
    EDF::Array<int, 4> array = { 5, 6, 7, 8 };

    EXPECT_DEATH( array.at(4), "" );
    EXPECT_DEATH( array.at(static_cast<std::size_t>(-1)), "" );
}

TEST(Array, IndexOperator_ValidIndex) {
    EDF::Array<int, 4> array = { 5, 6, 7, 8 };

    EXPECT_EQ( array[0], 5 );
    EXPECT_EQ( array[1], 6 );
    EXPECT_EQ( array[2], 7 );
    EXPECT_EQ( array[3], 8 );

    array[2] = 10;
    EXPECT_EQ( array[2], 10 );

    int& ref = array[2];
    EXPECT_EQ( ref, 10 );

    ref = 20;
    EXPECT_EQ( array[2], 20 );

    const int& refConst = array[2];
    EXPECT_EQ( refConst, 20 );
}

TEST(Array, IndexOperator_ValidIndexCustomClass) {
    EDF::Array<CustomClass, 4> array = {
        CustomClass( 10 ),
        CustomClass( 20 ),
        CustomClass( 30 ),
        CustomClass( 40 ),
    };

    EXPECT_EQ( array[0].getValue(), 10 );
    EXPECT_EQ( array[1].getValue(), 20 );
    EXPECT_EQ( array[2].getValue(), 30 );
    EXPECT_EQ( array[3].getValue(), 40 );

    array[2] = CustomClass( 1 );
    EXPECT_EQ( array[2].getValue(), 1 );

    CustomClass& ref = array[2];
    EXPECT_EQ( ref.getValue(), 1 );

    ref = CustomClass( 2 );
    EXPECT_EQ( array[2].getValue(), 2 );

    const CustomClass& refConst = array[2];
    EXPECT_EQ( refConst.getValue(), 2 );
}

TEST(Array, FrontSingleElement) {
    EDF::Array<int, 1> array{ 1 };

    EXPECT_EQ( array.front(), 1 );
    EXPECT_EQ( array.front(), array[0] );

    int& ref = array.front();
    EXPECT_EQ( ref, 1 );
    ref = 10;

    const int& refConst = array.front();
    EXPECT_EQ( refConst, 10 );
}

TEST(Array, FrontMultipleElements) {
    EDF::Array<int, 4> array{ 1, 2, 3, 4 };

    EXPECT_EQ( array.front(), 1 );
    EXPECT_EQ( array.front(), array[0] );

    int& ref = array.front();
    EXPECT_EQ( ref, 1 );
    ref = 10;

    const int& refConst = array.front();
    EXPECT_EQ( refConst, 10 );
}

TEST(Array, BackSingleElement) {
    EDF::Array<int, 1> array{ 1 };

    EXPECT_EQ( array.back(), 1 );
    EXPECT_EQ( array.back(), array[array.maxLength()-1] );

    int& ref = array.back();
    EXPECT_EQ( ref, 1 );
    ref = 10;

    const int& refConst = array.back();
    EXPECT_EQ( refConst, 10 );
}

TEST(Array, BackMultipleElements) {
    EDF::Array<int, 4> array{ 1, 2, 3, 4 };

    EXPECT_EQ( array.back(), 4 );
    EXPECT_EQ( array.back(), array[array.maxLength()-1] );

    int& ref = array.back();
    EXPECT_EQ( ref, 4 );
    ref = 40;

    const int& refConst = array.back();
    EXPECT_EQ( refConst, 40 );
}

TEST(Array, DataSingleElement) {
    EDF::Array<int, 1> array{ 1 };

    int* pointer = array.data();
    EXPECT_EQ( (void*)pointer, (void*)&array );
    EXPECT_EQ( *pointer, 1 );
    *pointer = 10;
    EXPECT_EQ( *pointer, 10 );

    const int* pointerToConst = array.data();
    EXPECT_EQ( (void*)pointerToConst, (void*)&array );
    EXPECT_EQ( *pointerToConst, 10 );
}

TEST(Array, DataMultipleElements) {
    EDF::Array<int, 4> array{ 1, 2, 3, 4 };

    const int* pointerToConst = array.data();
    for( std::size_t k = 0; k < array.maxLength(); ++k ) {
        EXPECT_EQ( *(pointerToConst + k), k + 1 );
    }
}

TEST(Array, MaxLengthInt) {
    EDF::Array<int, 4> array{ 1, 2, 3, 4 };

    EXPECT_EQ(array.maxLength(), 4);
}

TEST(Array, MaxLengthCustomClass) {
    EDF::Array<CustomClass, 4> array{ 1, 2, 3, 4 };

    EXPECT_EQ(array.maxLength(), 4);
}

TEST(Array, FillWithInts) {
    EDF::Array<int, 10> array;
    array.fill( 1 ); // rvalue
    for( auto&& element : array ) {
        EXPECT_EQ( element, 1 );
    }

    const int data = 2;
    array.fill( data ); // lvalue
    for( auto&& element : array ) {
        EXPECT_EQ( element, data );
    }
}

TEST(Array, FillWithCustomClass) {
    EDF::Array<CustomClass, 10> array;
    array.fill( CustomClass( 1 ) ); // rvalue
    for( auto&& element : array ) {
        EXPECT_EQ( element.getValue(), 1 );
    }

    const CustomClass data = 2;
    array.fill( data ); // lvalue
    for( auto&& element : array ) {
        EXPECT_EQ( element.getValue(), data.getValue() );
    }
}

TEST(Array, ClearInt) {
    EDF::Array<int, 4> array{ 1, 2, 3, 4 };

    array.clear();
    for( auto&& element : array ) {
        EXPECT_EQ( element, 0 );
    }
}

TEST(Array, ClearCustomClass) {
    EDF::Array<CustomClass, 4> array{ 1, 2, 3, 4 };

    array.clear();
    const CustomClass defaultValue;
    for( auto&& element : array ) {
        EXPECT_EQ( element.getValue(), defaultValue.getValue() );
    }
}

TEST(Array, BeginEnd) {
    EDF::Array<int, 4> array{ 1, 2, 3, 4 };

    auto begin = array.begin();
    auto end = array.end();
    EXPECT_EQ( *begin, 1 );
    EXPECT_EQ( *(end - 1), 4 );

    const auto& cbegin = array.cbegin();
    const auto& cend = array.cend();
    EXPECT_EQ( *cbegin, 1 );
    EXPECT_EQ( *(cend - 1), 4 );
}

TEST(Array, ReverseBeginEnd) {
    EDF::Array<int, 4> array{ 1, 2, 3, 4 };

    auto rbegin = array.rbegin();
    auto rend = array.rend();
    EXPECT_EQ( *rbegin, 4 );
    EXPECT_EQ( *(rend - 1), 1 );

    const auto& crbegin = array.crbegin();
    const auto& crend = array.crend();
    EXPECT_EQ( *crbegin, 4 );
    EXPECT_EQ( *(crend - 1), 1 );
}

TEST(Array, ConstexprCompileTimeEvaluation) {
    // 1. Default constructor and maxLength
    constexpr EDF::Array<int, 5> defaultArr{};
    static_assert( defaultArr.maxLength() == 5, "Constexpr maxLength failed" );
    static_assert( defaultArr[0] == 0, "Constexpr default element failed" );

    // 2. Initializer list and element access methods
    constexpr auto initArr = []() {
        EDF::Array<int, 4> a{ 10, 20, 30, 40 };
        return a;
    }();
    static_assert( initArr.maxLength() == 4, "Constexpr maxLength with list failed" );
    static_assert( initArr[0] == 10, "Constexpr operator[] index 0 failed" );
    static_assert( initArr.at( 1 ) == 20, "Constexpr at() index 1 failed" );
    static_assert( initArr.front() == 10, "Constexpr front() failed" );
    static_assert( initArr.back() == 40, "Constexpr back() failed" );

    // 3. Custom Class compile-time evaluation
    constexpr auto customArr = []() {
        EDF::Array<CustomClass, 2> a{ CustomClass(5), CustomClass(15) };
        return a;
    }();
    static_assert( customArr[0].getValue() == 5, "Constexpr custom class [0] failed" );
    static_assert( customArr[1].getValue() == 15, "Constexpr custom class [1] failed" );

    // 4. Mutation inside a constexpr lambda (fill and clear)
    constexpr auto filledArr = []() {
        EDF::Array<int, 3> a{ 1, 2, 3 };
        a.fill( 7 );
        return a;
    }();
    static_assert( filledArr[0] == 7, "Constexpr fill element 0 failed" );
    static_assert( filledArr[2] == 7, "Constexpr fill element 2 failed" );

    constexpr auto clearedArr = []() {
        EDF::Array<int, 3> a{ 5, 5, 5 };
        a.clear();
        return a;
    }();
    static_assert( clearedArr[0] == 0, "Constexpr clear failed" );
    static_assert( clearedArr[2] == 0, "Constexpr clear failed" );

    SUCCEED();
}

TEST(Array, EdgeCases_ZeroSizeAndConst) {
    EDF::Array<int, 0> emptyArray;
    EXPECT_EQ(emptyArray.maxLength(), 0);
    EXPECT_EQ(emptyArray.begin(), emptyArray.end());

    const EDF::Array<int, 3> constArray{ 1, 2, 3 };
    EXPECT_EQ(constArray[0], 1);
    EXPECT_EQ(constArray.at(1), 2);
    EXPECT_EQ(constArray.front(), 1);
    EXPECT_EQ(constArray.back(), 3);

    const int* p = constArray.data();
    EXPECT_EQ(*p, 1);
}

TEST(Array, MoveOnlyTypes) {
    EDF::Array<std::unique_ptr<int>, 2> moveArray;
    moveArray[0] = std::make_unique<int>(42);
    EXPECT_EQ(*moveArray[0], 42);
}
