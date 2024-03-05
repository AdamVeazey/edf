/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Assert.hpp"
#include "EDF/Math.hpp"
#include <cstring>
#include <cstdint>
#include <iterator>

namespace EDF {
namespace impl {
using Iterator = char*;
using ConstIterator = const char*;
using ReverseIterator = std::reverse_iterator<Iterator>;
using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
} /* impl */

template<std::size_t N>
class String final {
private:
    std::size_t size;
    char buffer[N];
public:
    /* Constructors */
    constexpr String();

    constexpr String( const char* str );
    constexpr String( const uint8_t* str );

    constexpr String( const char* str, std::size_t n );
    constexpr String( const uint8_t* str, std::size_t n );

    constexpr String( char ch );

    constexpr String( int8_t value, int base = 10 );
    constexpr String( int16_t value, int base = 10 );
    constexpr String( int32_t value, int base = 10 );
    constexpr String( int64_t value, int base = 10 );
    constexpr String( uint8_t value, int base = 10 );
    constexpr String( uint16_t value, int base = 10 );
    constexpr String( uint32_t value, int base = 10 );
    constexpr String( uint64_t value, int base = 10 );

    template<std::size_t S>
    constexpr String( const String<S>& o );

    ~String() = default;

    using Iterator = impl::Iterator;
    using ConstIterator = impl::ConstIterator;
    using ReverseIterator = impl::ReverseIterator;
    using ConstReverseIterator = impl::ConstReverseIterator;

    /* Is Questions */
    constexpr bool isEmpty() const;
    constexpr bool isFull() const;

    /* Capacity */
    constexpr const std::size_t& length() const;
    constexpr std::size_t maxLength() const;

    /* Element access */
    constexpr char& at( std::size_t index );
    constexpr const char& at( std::size_t index ) const;

    constexpr char& operator[]( std::size_t index );
    constexpr const char& operator[]( std::size_t index ) const;

    constexpr char* asCString();
    constexpr const char* asCString() const;
    constexpr uint8_t* asByteData();
    constexpr const uint8_t* asByteData() const;

    /* Conversions: toX */
    constexpr int8_t toInt8_t( int base = 10 ) const;
    constexpr int16_t toInt16_t( int base = 10 ) const;
    constexpr int32_t toInt32_t( int base = 10 ) const;
    constexpr int64_t toInt64_t( int base = 10 ) const;
    constexpr uint8_t toUint8_t( int base = 10 ) const;
    constexpr uint16_t toUint16_t( int base = 10 ) const;
    constexpr uint32_t toUint32_t( int base = 10 ) const;
    constexpr uint64_t toUint64_t( int base = 10 ) const;

    /* Operations: In/Out-of-Place - append */
    constexpr String& append( const char* str );
    constexpr String& append( const uint8_t* str );

    constexpr String& append( const char* str, std::size_t n );
    constexpr String& append( const uint8_t* str, std::size_t n );

    template<std::size_t S>
    constexpr String& append( const char (&str)[S] );
    template<std::size_t S>
    constexpr String& append( const uint8_t (&str)[S] );

    constexpr String& append( char ch );

    constexpr String& append( int8_t value, int base = 10 );
    constexpr String& append( int16_t value, int base = 10 );
    constexpr String& append( int32_t value, int base = 10 );
    constexpr String& append( int64_t value, int base = 10 );
    constexpr String& append( uint8_t value, int base = 10 );
    constexpr String& append( uint16_t value, int base = 10 );
    constexpr String& append( uint32_t value, int base = 10 );
    constexpr String& append( uint64_t value, int base = 10 );

    template<std::size_t S>
    constexpr String& append( const String<S>& str );

    constexpr String getAppended( const char* str ) const;
    constexpr String getAppended( const uint8_t* str ) const;

    constexpr String getAppended( const char* str, std::size_t n ) const;
    constexpr String getAppended( const uint8_t* str, std::size_t n ) const;

    constexpr String getAppended( char ch ) const;

    constexpr String getAppended( int8_t value, int base = 10 ) const;
    constexpr String getAppended( int16_t value, int base = 10 ) const;
    constexpr String getAppended( int32_t value, int base = 10 ) const;
    constexpr String getAppended( int64_t value, int base = 10 ) const;
    constexpr String getAppended( uint8_t value, int base = 10 ) const;
    constexpr String getAppended( uint16_t value, int base = 10 ) const;
    constexpr String getAppended( uint32_t value, int base = 10 ) const;
    constexpr String getAppended( uint64_t value, int base = 10 ) const;

    template<std::size_t S>
    constexpr String getAppended( const String<S>& str ) const;

    /* Operations: In/Out-of-Place - insert */
    constexpr void insert( std::size_t index, char value );
    constexpr void insert( std::size_t index, std::size_t count, char value );
    constexpr void insert( std::size_t index, std::initializer_list<char> iList );
    constexpr Iterator insert( ConstIterator pos, char value );
    constexpr Iterator insert( ConstIterator pos, std::size_t count, char value );
    constexpr Iterator insert( ConstIterator pos, std::initializer_list<char> iList );

    constexpr void insert( std::size_t index, const char* str );
    constexpr void insert( std::size_t index, const uint8_t* str );
    constexpr Iterator insert( ConstIterator pos, const uint8_t* str );
    constexpr Iterator insert( ConstIterator pos, const char* str );

    constexpr void insert( std::size_t index, const char* str, std::size_t n );
    constexpr void insert( std::size_t index, const uint8_t* str, std::size_t n );
    constexpr Iterator insert( ConstIterator pos, const uint8_t* str, std::size_t n );
    constexpr Iterator insert( ConstIterator pos, const char* str, std::size_t n );

    constexpr void insert( std::size_t index, int8_t value, int base = 10 );
    constexpr void insert( std::size_t index, int16_t value, int base = 10 );
    constexpr void insert( std::size_t index, int32_t value, int base = 10 );
    constexpr void insert( std::size_t index, int64_t value, int base = 10 );
    constexpr void insert( std::size_t index, uint8_t value, int base = 10 );
    constexpr void insert( std::size_t index, uint16_t value, int base = 10 );
    constexpr void insert( std::size_t index, uint32_t value, int base = 10 );
    constexpr void insert( std::size_t index, uint64_t value, int base = 10 );

    constexpr Iterator insert( ConstIterator pos, int8_t value, int base = 10 );
    constexpr Iterator insert( ConstIterator pos, int16_t value, int base = 10 );
    constexpr Iterator insert( ConstIterator pos, int32_t value, int base = 10 );
    constexpr Iterator insert( ConstIterator pos, int64_t value, int base = 10 );
    constexpr Iterator insert( ConstIterator pos, uint8_t value, int base = 10 );
    constexpr Iterator insert( ConstIterator pos, uint16_t value, int base = 10 );
    constexpr Iterator insert( ConstIterator pos, uint32_t value, int base = 10 );
    constexpr Iterator insert( ConstIterator pos, uint64_t value, int base = 10 );

    template<std::size_t S>
    constexpr void insert( std::size_t index, const String<S>& str );
    template<std::size_t S>
    constexpr Iterator insert( ConstIterator pos, const String<S>& str );

    constexpr String getInserted( std::size_t index, char value ) const;
    constexpr String getInserted( std::size_t index, std::size_t count, char value ) const;
    constexpr String getInserted( std::size_t index, std::initializer_list<char> iList ) const;
    constexpr String getInserted( ConstIterator pos, char value ) const;
    constexpr String getInserted( ConstIterator pos, std::size_t count, char value ) const;
    constexpr String getInserted( ConstIterator pos, std::initializer_list<char> iList ) const;

    constexpr String getInserted( std::size_t index, const char* str ) const;
    constexpr String getInserted( std::size_t index, const uint8_t* str ) const;
    constexpr String getInserted( ConstIterator pos, const uint8_t* str ) const;
    constexpr String getInserted( ConstIterator pos, const char* str ) const;

    constexpr String getInserted( std::size_t index, const char* str, std::size_t n ) const;
    constexpr String getInserted( std::size_t index, const uint8_t* str, std::size_t n ) const;
    constexpr String getInserted( ConstIterator pos, const uint8_t* str, std::size_t n ) const;
    constexpr String getInserted( ConstIterator pos, const char* str, std::size_t n ) const;

    constexpr String getInserted( std::size_t index, int8_t value, int base = 10 ) const;
    constexpr String getInserted( std::size_t index, int16_t value, int base = 10 ) const;
    constexpr String getInserted( std::size_t index, int32_t value, int base = 10 ) const;
    constexpr String getInserted( std::size_t index, int64_t value, int base = 10 ) const;
    constexpr String getInserted( std::size_t index, uint8_t value, int base = 10 ) const;
    constexpr String getInserted( std::size_t index, uint16_t value, int base = 10 ) const;
    constexpr String getInserted( std::size_t index, uint32_t value, int base = 10 ) const;
    constexpr String getInserted( std::size_t index, uint64_t value, int base = 10 ) const;

    constexpr String getInserted( ConstIterator pos, int8_t value, int base = 10 ) const;
    constexpr String getInserted( ConstIterator pos, int16_t value, int base = 10 ) const;
    constexpr String getInserted( ConstIterator pos, int32_t value, int base = 10 ) const;
    constexpr String getInserted( ConstIterator pos, int64_t value, int base = 10 ) const;
    constexpr String getInserted( ConstIterator pos, uint8_t value, int base = 10 ) const;
    constexpr String getInserted( ConstIterator pos, uint16_t value, int base = 10 ) const;
    constexpr String getInserted( ConstIterator pos, uint32_t value, int base = 10 ) const;
    constexpr String getInserted( ConstIterator pos, uint64_t value, int base = 10 ) const;

    template<std::size_t S>
    constexpr String getInserted( std::size_t index, const String<S>& str ) const;
    template<std::size_t S>
    constexpr String getInserted( ConstIterator pos, const String<S>& str ) const;

    /* Operations: In/Out-of-Place - erase */
    constexpr void erase( std::size_t index );
    constexpr void erase( std::size_t first, std::size_t last );
    constexpr Iterator erase( ConstIterator pos );
    constexpr Iterator erase( ConstIterator first, ConstIterator last );

    constexpr String getErased( std::size_t index ) const;
    constexpr String getErased( std::size_t first, std::size_t last ) const;
    constexpr String getErased( ConstIterator pos ) const;
    constexpr String getErased( ConstIterator first, ConstIterator last ) const;

    /* Operations: In-Place - clear */
    constexpr void clear();

    /* Operations: Out-of-Place - copyTo */
    constexpr void copyTo( char* outputString, std::size_t maxBufferLength ) const;
    constexpr void copyTo( uint8_t* outputString, std::size_t maxBufferLength ) const;

    template<std::size_t S>
    constexpr void copyTo( char (&outputString)[S] ) const;
    template<std::size_t S>
    constexpr void copyTo( uint8_t (&outputString)[S] ) const;

    /* Operations: Out-of-Place - find and rfind */
    constexpr Iterator find( char value ) const;
    constexpr Iterator find( const char* value ) const;
    constexpr Iterator find( const char* value, std::size_t n ) const;
    template<std::size_t S>
    constexpr Iterator find( const String<S>& value ) const;

    constexpr Iterator find( ConstIterator pos, char value ) const;
    constexpr Iterator find( ConstIterator pos, const char* value ) const;
    constexpr Iterator find( ConstIterator pos, const char* value, std::size_t n ) const;
    template<std::size_t S>
    constexpr Iterator find( ConstIterator pos, const String<S>& value ) const;

    constexpr ReverseIterator rfind( char value ) const;
    constexpr ReverseIterator rfind( const char* value ) const;
    constexpr ReverseIterator rfind( const char* value, std::size_t n ) const;
    template<std::size_t S>
    constexpr ReverseIterator rfind( const String<S>& value ) const;

    constexpr ReverseIterator rfind( ConstReverseIterator pos, char value ) const;
    constexpr ReverseIterator rfind( ConstReverseIterator pos, const char* value ) const;
    constexpr ReverseIterator rfind( ConstReverseIterator pos, const char* value, std::size_t n ) const;
    template<std::size_t S>
    constexpr ReverseIterator rfind( ConstReverseIterator pos, const String<S>& value ) const;

    /* Operations: Out-of-Place - contains */
    constexpr bool contains( char value ) const;
    constexpr bool contains( const char* value ) const;
    constexpr bool contains( const char* value, std::size_t n ) const;
    template<std::size_t S>
    constexpr bool contains( const String<S>& value ) const;

    /* Operations: Out-of-Place - equals */
    constexpr bool equals( char value ) const;
    constexpr bool equals( const char* value ) const;
    constexpr bool equals( const char* value, std::size_t n ) const;
    template<std::size_t S>
    constexpr bool equals( const String<S>& value ) const;

    /* Operations: In/Out-of-Place - strip */
    constexpr String& strip( char value = '\0' );
    constexpr String& strip( const char* values );
    constexpr String& strip( const char* values, std::size_t n );
    template<std::size_t S>
    constexpr String& strip( const String<S>& values );

    constexpr String getStripped( char value = '\0' ) const;
    constexpr String getStripped( const char* values ) const;
    constexpr String getStripped( const char* values, std::size_t n ) const;
    template<std::size_t S>
    constexpr String getStripped( const String<S>& values ) const;

    /* Operations: In/Out-of-Place - trim */
    constexpr String& trim( char value = '\0' );
    constexpr String& trim( const char* values );
    constexpr String& trim( const char* values, std::size_t n );
    template<std::size_t S>
    constexpr String& trim( const String<S>& values );

    constexpr String getTrimmed( char value = '\0' ) const;
    constexpr String getTrimmed( const char* values ) const;
    constexpr String getTrimmed( const char* values, std::size_t n ) const;
    template<std::size_t S>
    constexpr String getTrimmed( const String<S>& values ) const;

    /* Operations: In/Out-of-Place - trimLeft */
    constexpr String& trimLeft( char value = '\0' );
    constexpr String& trimLeft( const char* values );
    constexpr String& trimLeft( const char* values, std::size_t n );
    template<std::size_t S>
    constexpr String& trimLeft( const String<S>& values );

    constexpr String getTrimmedLeft( char value = '\0' ) const;
    constexpr String getTrimmedLeft( const char* values ) const;
    constexpr String getTrimmedLeft( const char* values, std::size_t n ) const;
    template<std::size_t S>
    constexpr String getTrimmedLeft( const String<S>& values ) const;

    /* Operations: In/Out-of-Place - trimRight */
    constexpr String& trimRight( char value = '\0' );
    constexpr String& trimRight( const char* values );
    constexpr String& trimRight( const char* values, std::size_t n );
    template<std::size_t S>
    constexpr String& trimRight( const String<S>& values );

    constexpr String getTrimmedRight( char value = '\0' ) const;
    constexpr String getTrimmedRight( const char* values ) const;
    constexpr String getTrimmedRight( const char* values, std::size_t n ) const;
    template<std::size_t S>
    constexpr String getTrimmedRight( const String<S>& values ) const;

    /* Operations: In/Out-of-Place - reverse */
    constexpr String& reverse();
    constexpr String getReversed() const;

    /* Operations: In/Out-of-Place - toLower */
    constexpr String& toLower();
    constexpr String getToLower() const;

    /* Operations: In/Out-of-Place - toUpper */
    constexpr String& toUpper();
    constexpr String getToUpper() const;

    /* Operations: In/Out-of-Place - replace */
    constexpr String& replace( char lookFor, char replaceWith );
    constexpr String& replace( const char* lookFor, char replaceWith );
    constexpr String& replace( const char* lookFor, std::size_t nLF, char replaceWith );
    template<std::size_t S>
    constexpr String& replace( const String<S>& lookFor, char replaceWith );

    constexpr String& replace( char lookFor, const char* replaceWith );
    constexpr String& replace( const char* lookFor, const char* replaceWith );
    constexpr String& replace( const char* lookFor, std::size_t nLF, const char* replaceWith );
    template<std::size_t S>
    constexpr String& replace( const String<S>& lookFor, const char* replaceWith );

    constexpr String& replace( char lookFor, const char* replaceWith, std::size_t nRW );
    constexpr String& replace( const char* lookFor, const char* replaceWith, std::size_t nRW );
    constexpr String& replace(
        const char* lookFor, std::size_t nLF,
        const char* replaceWith, std::size_t nRW
    );
    template<std::size_t S>
    constexpr String& replace( const String<S>& lookFor, const char* replaceWith, std::size_t nRW );

    template<std::size_t S>
    constexpr String& replace( char lookFor, const String<S>& replaceWith );
    template<std::size_t S>
    constexpr String& replace( const char* lookFor, const String<S>& replaceWith );
    template<std::size_t S>
    constexpr String& replace(
        const char* lookFor, std::size_t nLF,
        const String<S>& replaceWith
    );
    template<std::size_t S1, std::size_t S2>
    constexpr String& replace( const String<S1>& lookFor, const String<S2>& replaceWith );

    constexpr String getReplaced( char lookFor, char replaceWith ) const;
    constexpr String getReplaced( const char* lookFor, char replaceWith ) const;
    constexpr String getReplaced( const char* lookFor, std::size_t nLF, char replaceWith ) const;
    template<std::size_t S>
    constexpr String getReplaced( const String<S>& lookFor, char replaceWith ) const;

    constexpr String getReplaced( char lookFor, const char* replaceWith ) const;
    constexpr String getReplaced( const char* lookFor, const char* replaceWith ) const;
    constexpr String getReplaced( const char* lookFor, std::size_t nLF, const char* replaceWith ) const;
    template<std::size_t S>
    constexpr String getReplaced( const String<S>& lookFor, const char* replaceWith ) const;

    constexpr String getReplaced( char lookFor, const char* replaceWith, std::size_t nRW ) const;
    constexpr String getReplaced( const char* lookFor, const char* replaceWith, std::size_t nRW ) const;
    constexpr String getReplaced(
        const char* lookFor, std::size_t nLF,
        const char* replaceWith, std::size_t nRW
    ) const;
    template<std::size_t S>
    constexpr String getReplaced( const String<S>& lookFor, const char* replaceWith, std::size_t nRW ) const;

    template<std::size_t S>
    constexpr String getReplaced( char lookFor, const String<S>& replaceWith ) const;
    template<std::size_t S>
    constexpr String getReplaced( const char* lookFor, const String<S>& replaceWith ) const;
    template<std::size_t S>
    constexpr String getReplaced( const char* lookFor, std::size_t nLF, const String<S>& replaceWith ) const;
    template<std::size_t S1, std::size_t S2>
    constexpr String getReplaced( const String<S1>& lookFor, const String<S2>& replaceWith ) const;

    /* Operations: In/Out-of-Place - subString */
    constexpr String& subString( ConstIterator start, ConstIterator end );
    constexpr String getSubString( ConstIterator start, ConstIterator end ) const;

    /* Operations: Operator Overload - += */
    constexpr String& operator+=( const char* rhs );
    constexpr String& operator+=( const uint8_t* rhs );

    constexpr String& operator+=( char rhs );

    constexpr String& operator+=( int8_t rhs );
    constexpr String& operator+=( int16_t rhs );
    constexpr String& operator+=( int32_t rhs );
    constexpr String& operator+=( int64_t rhs );
    constexpr String& operator+=( uint8_t rhs );
    constexpr String& operator+=( uint16_t rhs );
    constexpr String& operator+=( uint32_t rhs );
    constexpr String& operator+=( uint64_t rhs );

    template<std::size_t S>
    constexpr String& operator+=( const String<S>& rhs );

    /* Operations: Operator Overload - +(this, rhs) */
    constexpr String operator+( const char* rhs ) const;
    constexpr String operator+( const uint8_t* rhs ) const;

    constexpr String operator+( char rhs ) const;

    constexpr String operator+( const int8_t& rhs ) const;
    constexpr String operator+( const int16_t& rhs ) const;
    constexpr String operator+( const int32_t& rhs ) const;
    constexpr String operator+( const int64_t& rhs ) const;
    constexpr String operator+( const uint8_t& rhs ) const;
    constexpr String operator+( const uint16_t& rhs ) const;
    constexpr String operator+( const uint32_t& rhs ) const;
    constexpr String operator+( const uint64_t& rhs ) const;

    /* Operations: Operator Overload - +(lhs, String) */
    friend constexpr String operator+( const char* lhs, const String& rhs )     { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( const uint8_t* lhs, const String& rhs )  { String<N> result(lhs); result.append(rhs); return result; }

    template<std::size_t S>
    friend constexpr String<EDF::max(S,N)> operator+( const char (&lhs)[S], const String& rhs ) { String<EDF::max(N,S)> result(lhs); result.append(rhs); return result; }
    template<std::size_t S>
    friend constexpr String<EDF::max(S,N)> operator+( const uint8_t (&lhs)[S], const String& rhs ) { String<EDF::max(N,S)> result(lhs); result.append(rhs); return result; }

    friend constexpr String operator+( char lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }

    friend constexpr String operator+( int8_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( int16_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( int32_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( int64_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint8_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint16_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint32_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint64_t lhs, const String& rhs ) { String<N> result(lhs); result.append(rhs); return result; }

    template<std::size_t S>
    friend constexpr String<EDF::max(S,N)> operator+( const String<S>& lhs, const String& rhs ) { String<EDF::max(N,S)> result(lhs); result.append(rhs); return result; }

    /* Iterators */
    constexpr Iterator begin();
    constexpr ConstIterator begin() const;
    constexpr ConstIterator cbegin() const;

    constexpr Iterator end();
    constexpr ConstIterator end() const;
    constexpr ConstIterator cend() const;

    constexpr ReverseIterator rbegin();
    constexpr ConstReverseIterator rbegin() const;
    constexpr ConstReverseIterator crbegin() const;

    constexpr ReverseIterator rend();
    constexpr ConstReverseIterator rend() const;
    constexpr ConstReverseIterator crend() const;
};

} /* EDF */

#include "EDF/src/String.tpp"