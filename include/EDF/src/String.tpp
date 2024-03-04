/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/String.hpp"
#include <cstddef>

namespace EDF {
namespace impl {

/* Constructors */
void make_string( char* buffer, std::size_t& size, std::size_t N );
void make_string( char* buffer, std::size_t& size, std::size_t N, const char* str, std::size_t n );
void make_string( char* buffer, std::size_t& size, std::size_t N, char ch );
void make_string( char* buffer, std::size_t& size, std::size_t N, int8_t value, int base );
void make_string( char* buffer, std::size_t& size, std::size_t N, int16_t value, int base );
void make_string( char* buffer, std::size_t& size, std::size_t N, int32_t value, int base );
void make_string( char* buffer, std::size_t& size, std::size_t N, int64_t value, int base );
void make_string( char* buffer, std::size_t& size, std::size_t N, uint32_t value, int base );
void make_string( char* buffer, std::size_t& size, std::size_t N, uint64_t value, int base );

/* Conversions: toX */
int32_t toInt32_t( const char* buffer, const std::size_t& size, int base );
int64_t toInt64_t( const char* buffer, const std::size_t& size, int base );
uint32_t toUint32_t( const char* buffer, const std::size_t& size, int base );
uint64_t toUint64_t( const char* buffer, const std::size_t& size, int base );

/* Operations: In/Out-of-Place - insert */
Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, char value );
Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, std::size_t count, char value );
Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, std::initializer_list<char> iList );
Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, const char* str, std::size_t n );

/* Operations: In/Out-of-Place - erase */
Iterator erase( char* buffer, std::size_t& size, std::size_t N, ConstIterator first, ConstIterator last );

/* Operations: Out-of-Place - copyTo */
void copyTo( const char* buffer, const std::size_t& size, std::size_t N, char* outputString, std::size_t maxBufferLength );

/* Operations: Out-of-Place - find and rfind */
Iterator find( const char* buffer, const std::size_t& size, std::size_t N, ConstIterator pos, char value );
Iterator find( const char* buffer, const std::size_t& size, std::size_t N, ConstIterator pos, const char* value, std::size_t n );
ReverseIterator rfind( const char* buffer, const std::size_t& size, std::size_t N, ConstReverseIterator pos, char value );
ReverseIterator rfind( const char* buffer, const std::size_t& size, std::size_t N, ConstReverseIterator pos, const char* value, std::size_t n );

/* Operations: Out-of-Place - equals */
bool equals( const char* buffer, const std::size_t& size, std::size_t N, const char* value, std::size_t n );

/* Operations: In/Out-of-Place - strip */
void strip( char* buffer, std::size_t& size, std::size_t N, char value );
void strip( char* buffer, std::size_t& size, std::size_t N, const char* values, std::size_t n );

/* Operations: In/Out-of-Place - trimLeft */
void trimLeft( char* buffer, std::size_t& size, std::size_t N, char value );
void trimLeft( char* buffer, std::size_t& size, std::size_t N, const char* values, std::size_t n );

/* Operations: In/Out-of-Place - trimRight */
void trimRight( char* buffer, std::size_t& size, std::size_t N, char value );
void trimRight( char* buffer, std::size_t& size, std::size_t N, const char* values, std::size_t n );

/* Operations: In/Out-of-Place - reverse */
void reverse( char* buffer, std::size_t& size, std::size_t N );

/* Operations: In/Out-of-Place - toLower */
void toLower( char* buffer, std::size_t& size, std::size_t N );

/* Operations: In/Out-of-Place - toUpper */
void toUpper( char* buffer, std::size_t& size, std::size_t N );

/* Operations: In/Out-of-Place - replace */
void replace(
    char* buffer, std::size_t& size, std::size_t N,
    const char* lookFor, std::size_t nLF,
    const char* replaceWith, std::size_t nRW
);

/* Operations: In/Out-of-Place - subString */
void subString( char* buffer, std::size_t& size, std::size_t N, ConstIterator start, ConstIterator end );

} /* impl */

/* Constructors */
template<std::size_t N>
constexpr String<N>::
String() {
    impl::make_string( buffer, size, N );
}

template<std::size_t N>
constexpr String<N>::
String( const char* str ) {
    impl::make_string( buffer, size, N, str, std::strlen(str) );
}

template<std::size_t N>
constexpr String<N>::
String( const uint8_t* str ) {
    impl::make_string(
        buffer, size, N,
        reinterpret_cast<const char*>(str),
        std::strlen(reinterpret_cast<const char*>(str))
    );
}

template<std::size_t N>
constexpr String<N>::
String( const char* str, std::size_t n ) {
    impl::make_string( buffer, size, N, str, n );
}

template<std::size_t N>
constexpr String<N>::
String( const uint8_t* str, std::size_t n ) {
    impl::make_string( buffer, size, N, reinterpret_cast<const char*>(str), n );
}

template<std::size_t N>
constexpr String<N>::
String( char ch ) {
    impl::make_string( buffer, size, N, ch );
}

template<std::size_t N>
constexpr String<N>::
String( int8_t value, int base ) {
    // Attempting to cast this to an int32_t causes problems when base is not 10
    // Attempting to cast this to an int32_t & 0xFF causes problems when base is 10
    impl::make_string( buffer, size, N, value, base );
}

template<std::size_t N>
constexpr String<N>::
String( int16_t value, int base ) {
    // Attempting to cast this to an int32_t causes problems when base is not 10
    // Attempting to cast this to an int32_t & 0xFF causes problems when base is 10
    impl::make_string( buffer, size, N, value, base );
}

template<std::size_t N>
constexpr String<N>::
String( int32_t value, int base ) {
    impl::make_string( buffer, size, N, value, base );
}

template<std::size_t N>
constexpr String<N>::
String( int64_t value, int base ) {
    impl::make_string( buffer, size, N, value, base );
}

template<std::size_t N>
constexpr String<N>::
String( uint8_t value, int base ) {
    // to reduce the amount of template instantiations, cast the value to a uint32_t
    impl::make_string( buffer, size, N, static_cast<uint32_t>(value), base );
}

template<std::size_t N>
constexpr String<N>::
String( uint16_t value, int base ) {
    // to reduce the amount of template instantiations, cast the value to a uint32_t
    impl::make_string( buffer, size, N, static_cast<uint32_t>(value), base );
}

template<std::size_t N>
constexpr String<N>::
String( uint32_t value, int base ) {
    impl::make_string( buffer, size, N, value, base );
}

template<std::size_t N>
constexpr String<N>::
String( uint64_t value, int base ) {
    impl::make_string( buffer, size, N, value, base );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>::
String( const String<S>& o ) {
    impl::make_string( buffer, size, N, o.asCString(), o.length() );
}

/* Is Questions */
template<std::size_t N>
constexpr bool String<N>::
isEmpty() const {
    return length() == 0;
}

template<std::size_t N>
constexpr bool String<N>::
isFull() const {
    return length() == (N-1);
}

/* Capacity */
template<std::size_t N>
constexpr const std::size_t& String<N>::
length() const {
    return size;
}

template<std::size_t N>
constexpr std::size_t String<N>::
maxLength() const {
    return (N-1);
}

/* Element access */
template<std::size_t N>
constexpr char& String<N>::
at( std::size_t index ) {
    EDF_ASSERTD(index < length());
    EDF_ASSERTD(index < N);
    return buffer[index];
}

template<std::size_t N>
constexpr const char& String<N>::
at( std::size_t index ) const {
    EDF_ASSERTD(index < length());
    EDF_ASSERTD(index < N);
    return buffer[index];
}

template<std::size_t N>
constexpr char& String<N>::
operator[]( std::size_t index ) {
    return buffer[index];
}

template<std::size_t N>
constexpr const char& String<N>::
operator[]( std::size_t index ) const {
    return buffer[index];
}

template<std::size_t N>
constexpr char* String<N>::
asCString() {
    return buffer;
}

template<std::size_t N>
constexpr const char* String<N>::
asCString() const {
    return buffer;
}

template<std::size_t N>
constexpr uint8_t* String<N>::
asByteData() {
    return reinterpret_cast<uint8_t*>(buffer);
}

template<std::size_t N>
constexpr const uint8_t* String<N>::
asByteData() const {
    return reinterpret_cast<const uint8_t*>(buffer);
}

/* Conversions: toX */
template<std::size_t N>
constexpr int8_t String<N>::
toInt8_t( int base ) const {
    // reuse toInt32_t() to reduce # template instantiations
    return static_cast<int8_t>(toInt32_t( base ));
}

template<std::size_t N>
constexpr int16_t String<N>::
toInt16_t( int base ) const {
    // reuse toInt32_t() to reduce # template instantiations
    return static_cast<int16_t>(toInt32_t( base ));
}

template<std::size_t N>
constexpr int32_t String<N>::
toInt32_t( int base ) const {
    return impl::toInt32_t( buffer, size, base );
}

template<std::size_t N>
constexpr int64_t String<N>::
toInt64_t( int base ) const {
    return impl::toInt64_t( buffer, size, base );
}

template<std::size_t N>
constexpr uint8_t String<N>::
toUint8_t( int base ) const {
    // reuse toUint32_t() to reduce # template instantiations
    return static_cast<uint8_t>(toUint32_t( base ));
}

template<std::size_t N>
constexpr uint16_t String<N>::
toUint16_t( int base ) const {
    // reuse toUint32_t() to reduce # template instantiations
    return static_cast<uint16_t>(toUint32_t( base ));
}

template<std::size_t N>
constexpr uint32_t String<N>::
toUint32_t( int base ) const {
    return impl::toUint32_t( buffer, size, base );
}

template<std::size_t N>
constexpr uint64_t String<N>::
toUint64_t( int base ) const {
    return impl::toUint64_t( buffer, size, base );
}

/* Operations: In/Out-of-Place - append */
template<std::size_t N>
constexpr String<N>& String<N>::
append( const char* str ) {
    insert( end(), str );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( const uint8_t* str ) {
    insert( end(), str );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( const char* str, std::size_t n ) {
    insert( end(), str, n );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( const uint8_t* str, std::size_t n ) {
    insert( end(), str, n );
    return *this;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
append( const char (&str)[S] ) {
    insert( end(), str );
    return *this;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
append( const uint8_t (&str)[S] ) {
    insert( end(), str );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( char ch ) {
    insert( end(), ch );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( int8_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( int16_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( int32_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( int64_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( uint8_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( uint16_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( uint32_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
append( uint64_t value, int base ) {
    insert( end(), value, base );
    return *this;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
append( const String<S>& str ) {
    insert( end(), str );
    return *this;
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( const char* str ) const {
    return getInserted( end(), str );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( const uint8_t* str ) const {
    return getInserted( end(), str );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( const char* str, std::size_t n ) const {
    return getInserted( end(), str, n );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( const uint8_t* str, std::size_t n ) const {
    return getInserted( end(), str, n );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( char ch ) const {
    return getInserted( end(), ch );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( int8_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( int16_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( int32_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( int64_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( uint8_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( uint16_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( uint32_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
constexpr String<N> String<N>::
getAppended( uint64_t value, int base ) const {
    return getInserted( end(), value, base );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getAppended( const String<S>& str ) const {
    return getInserted( end(), str );
}

/* Operations: In/Out-of-Place - insert */
template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, char value ) {
    insert( cbegin() + index, value );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, std::size_t count, char value ) {
    insert( cbegin() + index, count, value );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, std::initializer_list<char> iList ) {
    insert( cbegin() + index, iList );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, char value ) {
    return impl::insert( buffer, size, N, pos, value );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, std::size_t count, char value ) {
    return impl::insert( buffer, size, N, pos, count, value );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, std::initializer_list<char> iList ) {
    return impl::insert( buffer, size, N, pos, iList );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, const char* str ) {
    insert( cbegin() + index, str );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, const uint8_t* str ) {
    insert( cbegin() + index, str );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, const uint8_t* str ) {
    return insert( pos, reinterpret_cast<const char*>(str) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, const char* str ) {
    return insert( pos, str, std::strlen(str) );
}


template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, const char* str, std::size_t n ) {
    insert( cbegin() + index, str, n );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, const uint8_t* str, std::size_t n ) {
    insert( cbegin() + index, str, n );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, const uint8_t* str, std::size_t n ) {
    return insert( pos, reinterpret_cast<const char*>(str), n );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, const char* str, std::size_t n ) {
    return impl::insert( buffer, size, N, pos, str, n );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, int8_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, int16_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, int32_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, int64_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, uint8_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, uint16_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, uint32_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr void String<N>::
insert( std::size_t index, uint64_t value, int base ) {
    insert( cbegin() + index, value, base );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, int8_t value, int base ) {
    return insert( pos, String<8+1>( value, base ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, int16_t value, int base ) {
    return insert( pos, String<16+1>( value, base ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, int32_t value, int base ) {
    return insert( pos, String<32+1>( value, base ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, int64_t value, int base ) {
    return insert( pos, String<64+1>( value, base ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, uint8_t value, int base ) {
    return insert( pos, String<8+1>( value, base ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, uint16_t value, int base ) {
    return insert( pos, String<16+1>( value, base ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, uint32_t value, int base ) {
    return insert( pos, String<32+1>( value, base ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, uint64_t value, int base ) {
    return insert( pos, String<64+1>( value, base ) );
}


template<std::size_t N>
template<std::size_t S>
constexpr void String<N>::
insert( std::size_t index, const String<S>& str ) {
    insert( cbegin() + index, str );
}

template<std::size_t N>
template<std::size_t S>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, const String<S>& str ) {
    return insert( pos, str.asCString(), str.length() );
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, char value ) const {
    String tmp(*this);
    tmp.insert( index, value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, std::size_t count, char value ) const {
    String tmp(*this);
    tmp.insert( index, count, value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, std::initializer_list<char> iList ) const {
    String tmp(*this);
    tmp.insert( index, iList );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, char value ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, std::size_t count, char value ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), count, value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, std::initializer_list<char> iList ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), iList );
    return tmp;
}


template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, const char* str ) const {
    String tmp(*this);
    tmp.insert( index, str );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, const uint8_t* str ) const {
    String tmp(*this);
    tmp.insert( index, str );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, const uint8_t* str ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), str );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, const char* str ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), str );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, const char* str, std::size_t n ) const {
    String tmp(*this);
    tmp.insert( index, str, n );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, const uint8_t* str, std::size_t n ) const {
    String tmp(*this);
    tmp.insert( index, str, n );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, const uint8_t* str, std::size_t n ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), str, n );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, const char* str, std::size_t n ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), str, n );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, int8_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, int16_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, int32_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, int64_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, uint8_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, uint16_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, uint32_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( std::size_t index, uint64_t value, int base ) const {
    String tmp(*this);
    tmp.insert( index, value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, int8_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, int16_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, int32_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, int64_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, uint8_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, uint16_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, uint32_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, uint64_t value, int base ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), value, base );
    return tmp;
}


template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getInserted( std::size_t index, const String<S>& str ) const {
    String tmp(*this);
    tmp.insert( index, str );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getInserted( ConstIterator pos, const String<S>& str ) const {
    String tmp(*this);
    tmp.insert( static_cast<std::size_t>(pos - begin()), str );
    return tmp;
}

/* Operations: In/Out-of-Place - erase */
template<std::size_t N>
constexpr void String<N>::
erase( std::size_t index ) {
    erase( ConstIterator(buffer + index) );
}

template<std::size_t N>
constexpr void String<N>::
erase( std::size_t first, std::size_t last ) {
    erase( ConstIterator(buffer + first), ConstIterator(buffer + last) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
erase( ConstIterator pos ) {
    return erase( pos, pos + 1 );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
erase( ConstIterator first, ConstIterator last ) {
    return impl::erase( buffer, size, N, first, last );
}

template<std::size_t N>
constexpr String<N> String<N>::
getErased( std::size_t index ) const {
    String tmp(*this);
    tmp.erase( index );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getErased( std::size_t first, std::size_t last ) const {
    String tmp(*this);
    tmp.erase( first, last );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getErased( ConstIterator pos ) const {
    String tmp(*this);
    tmp.erase( static_cast<std::size_t>(pos - begin()) );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getErased( ConstIterator first, ConstIterator last ) const {
    String tmp(*this);
    tmp.erase( static_cast<std::size_t>(first - begin()), static_cast<std::size_t>(last - begin()) );
    return tmp;
}

/* Operations: In-Place - clear */
template<std::size_t N>
constexpr void String<N>::
clear() {
    impl::make_string( buffer, size, N );
}

/* Operations: Out-of-Place - copyTo */
template<std::size_t N>
constexpr void String<N>::
copyTo( char* outputString, std::size_t maxBufferLength ) const {
    impl::copyTo( buffer, size, N, outputString, maxBufferLength );
}

template<std::size_t N>
constexpr void String<N>::
copyTo( uint8_t* outputString, std::size_t maxBufferLength ) const {
    copyTo( reinterpret_cast<char*>(outputString), maxBufferLength );
}

template<std::size_t N>
template<std::size_t S>
constexpr void String<N>::
copyTo( char (&outputString)[S] ) const {
    copyTo( outputString, S );
}

template<std::size_t N>
template<std::size_t S>
constexpr void String<N>::
copyTo( uint8_t (&outputString)[S] ) const {
    copyTo( reinterpret_cast<char(&)[S]>(outputString) );
}

/* Operations: Out-of-Place - find and rfind */
template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( char value ) const {
    return find( begin(), value );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( const char* value ) const {
    return find( begin(), value, std::strlen( value ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( const char* value, std::size_t n ) const {
    return find( begin(), value, n );
}

template<std::size_t N>
template<std::size_t S>
constexpr typename String<N>::Iterator String<N>::
find( const String<S>& value ) const {
    return find( begin(), value.asCString(), value.length() );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( ConstIterator pos, char value ) const {
    return impl::find( buffer, size, N, pos, value );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( ConstIterator pos, const char* value ) const {
    return find( pos, value, std::strlen( value ) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( ConstIterator pos, const char* value, std::size_t n ) const {
    return impl::find( buffer, size, N, pos, value, n );
}

template<std::size_t N>
template<std::size_t S>
constexpr typename String<N>::Iterator String<N>::
find( ConstIterator pos, const String<S>& value ) const {
    return find( pos, value.asCString(), value.length() );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( char value ) const {
    return rfind( rbegin(), value );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( const char* value ) const {
    return rfind( rbegin(), value );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( const char* value, std::size_t n ) const {
    return rfind( rbegin(), value, n );
}

template<std::size_t N>
template<std::size_t S>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( const String<S>& value ) const {
    return rfind( rbegin(), value.asCString(), value.length() );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( ConstReverseIterator pos, char value ) const {
    return impl::rfind( buffer, size, N, pos, value );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( ConstReverseIterator pos, const char* value ) const {
    return rfind( pos, value, std::strlen(value) );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( ConstReverseIterator pos, const char* value, std::size_t n ) const {
    return impl::rfind( buffer, size, N, pos, value, n );
}

template<std::size_t N>
template<std::size_t S>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( ConstReverseIterator pos, const String<S>& value ) const {
    return rfind( pos, value.asCString(), value.length() );
}

/* Operations: Out-of-Place - contains */
template<std::size_t N>
constexpr bool String<N>::
contains( char value ) const {
    return find( begin(), value ) != end();
}

template<std::size_t N>
constexpr bool String<N>::
contains( const char* value ) const {
    return find( begin(), value ) != end();
}

template<std::size_t N>
constexpr bool String<N>::
contains( const char* value, std::size_t n ) const {
    return find( begin(), value, n ) != end();
}

template<std::size_t N>
template<std::size_t S>
constexpr bool String<N>::
contains( const String<S>& value ) const {
    return find( begin(), value ) != end();
}

/* Operations: Out-of-Place - equals */
template<std::size_t N>
constexpr bool String<N>::
equals( char value ) const {
    return (length() == 1) && (*begin() == value);
}

template<std::size_t N>
constexpr bool String<N>::
equals( const char* value ) const {
    return equals( value, std::strlen( value ) );
}

template<std::size_t N>
constexpr bool String<N>::
equals( const char* value, std::size_t n ) const {
    return impl::equals( buffer, size, N, value, n );
}

template<std::size_t N>
template<std::size_t S>
constexpr bool String<N>::
equals( const String<S>& value ) const {
    return equals( value.asCString(), value.length() );
}

/* Operations: In/Out-of-Place - strip */
template<std::size_t N>
constexpr String<N>& String<N>::
strip( char value ) {
    impl::strip( buffer, size, N, value );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
strip( const char* values ) {
    return strip( values, std::strlen( values ) );
}

template<std::size_t N>
constexpr String<N>& String<N>::
strip( const char* values, std::size_t n ) {
    impl::strip( buffer, size, N, values, n );
    return *this;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
strip( const String<S>& values ) {
    return strip( values.asCString(), values.length() );
}

template<std::size_t N>
constexpr String<N> String<N>::
getStripped( char value ) const {
    String tmp(*this);
    tmp.strip( value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getStripped( const char* values ) const {
    String tmp(*this);
    tmp.strip( values );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getStripped( const char* values, std::size_t n ) const {
    String tmp(*this);
    tmp.strip( values, n );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getStripped( const String<S>& values ) const {
    String tmp(*this);
    tmp.strip( values );
    return tmp;
}

/* Operations: In/Out-of-Place - trim */
template<std::size_t N>
constexpr String<N>& String<N>::
trim( char value ) {
    return trimRight( value ).trimLeft( value );
}

template<std::size_t N>
constexpr String<N>& String<N>::
trim( const char* values ) {
    return trimRight( values ).trimLeft( values );
}

template<std::size_t N>
constexpr String<N>& String<N>::
trim( const char* values, std::size_t n ) {
    return trimRight( values, n ).trimLeft( values, n );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
trim( const String<S>& values ) {
    return trim( values.asCString(), values.length() );
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmed( char value ) const {
    String tmp(*this);
    tmp.trim( value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmed( const char* values ) const {
    String tmp(*this);
    tmp.trim( values );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmed( const char* values, std::size_t n ) const {
    String tmp(*this);
    tmp.trim( values, n );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getTrimmed( const String<S>& values ) const {
    String tmp(*this);
    tmp.trim( values );
    return tmp;
}

/* Operations: In/Out-of-Place - trimLeft */
template<std::size_t N>
constexpr String<N>& String<N>::
trimLeft( char value ) {
    impl::trimLeft( buffer, size, N, value );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
trimLeft( const char* values ) {
    return trimLeft( values, std::strlen( values ) );
}

template<std::size_t N>
constexpr String<N>& String<N>::
trimLeft( const char* values, std::size_t n ) {
    impl::trimLeft( buffer, size, N, values, n );
    return *this;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
trimLeft( const String<S>& values ) {
    return trimLeft( values.asCString(), values.length() );
}


template<std::size_t N>
constexpr String<N> String<N>::
getTrimmedLeft( char value ) const {
    String tmp(*this);
    tmp.trimLeft( value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmedLeft( const char* values ) const {
    String tmp(*this);
    tmp.trimLeft( values );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmedLeft( const char* values, std::size_t n ) const {
    String tmp(*this);
    tmp.trimLeft( values, n );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getTrimmedLeft( const String<S>& values ) const {
    String tmp(*this);
    tmp.trimLeft( values );
    return tmp;
}

/* Operations: In/Out-of-Place - trimRight */
template<std::size_t N>
constexpr String<N>& String<N>::
trimRight( char value ) {
    impl::trimRight( buffer, size, N, value );
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
trimRight( const char* values ) {
    return trimRight( values, std::strlen( values ) );
}

template<std::size_t N>
constexpr String<N>& String<N>::
trimRight( const char* values, std::size_t n ) {
    impl::trimRight( buffer, size, N, values, n );
    return *this;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
trimRight( const String<S>& values ) {
    return trimRight( values.asCString(), values.length() );
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmedRight( char value ) const {
    String tmp(*this);
    tmp.trimRight( value );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmedRight( const char* values ) const {
    String tmp(*this);
    tmp.trimRight( values );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getTrimmedRight( const char* values, std::size_t n ) const {
    String tmp(*this);
    tmp.trimRight( values, n );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getTrimmedRight( const String<S>& values ) const {
    String tmp(*this);
    tmp.trimRight( values );
    return tmp;
}

/* Operations: In/Out-of-Place - reverse */
template<std::size_t N>
constexpr String<N>& String<N>::
reverse() {
    impl::reverse( buffer, size, N );
    return *this;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReversed() const {
    String tmp(*this);
    tmp.reverse();
    return tmp;
}

/* Operations: In/Out-of-Place - toLower */
template<std::size_t N>
constexpr String<N>& String<N>::
toLower() {
    impl::toLower( buffer, size, N );
    return *this;
}

template<std::size_t N>
constexpr String<N> String<N>::
getToLower() const {
    String tmp(*this);
    tmp.toLower();
    return tmp;
}

/* Operations: In/Out-of-Place - toUpper */
template<std::size_t N>
constexpr String<N>& String<N>::
toUpper() {
    impl::toUpper( buffer, size, N );
    return *this;
}

template<std::size_t N>
constexpr String<N> String<N>::
getToUpper() const {
    String tmp(*this);
    tmp.toUpper();
    return tmp;
}

/* Operations: In/Out-of-Place - replace */
template<std::size_t N>
constexpr String<N>& String<N>::
replace( char lookFor, char replaceWith ) {
    return replace( &lookFor, 1_uz, &replaceWith, 1_uz );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( const char* lookFor, char replaceWith ) {
    return replace( lookFor, std::strlen(lookFor), &replaceWith, 1_uz );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( const char* lookFor, std::size_t nLF, char replaceWith ) {
    return replace( lookFor, nLF, &replaceWith, 1_uz );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
replace( const String<S>& lookFor, char replaceWith ) {
    return replace( lookFor.asCString(), lookFor.length(), &replaceWith, 1_uz );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( char lookFor, const char* replaceWith ) {
    return replace( &lookFor, 1_uz, replaceWith, std::strlen(replaceWith) );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( const char* lookFor, const char* replaceWith ) {
    return replace( lookFor, std::strlen(lookFor), replaceWith, std::strlen(replaceWith) );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( const char* lookFor, std::size_t nLF, const char* replaceWith ) {
    return replace( lookFor, nLF, replaceWith, std::strlen(replaceWith) );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
replace( const String<S>& lookFor, const char* replaceWith ) {
    return replace( lookFor.asCString(), lookFor.length(), replaceWith, std::strlen(replaceWith) );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( char lookFor, const char* replaceWith, std::size_t nRW ) {
    return replace( &lookFor, 1_uz, replaceWith, nRW );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( const char* lookFor, const char* replaceWith, std::size_t nRW ) {
    return replace( lookFor, std::strlen(lookFor), replaceWith, nRW );
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace( const char* lookFor, std::size_t nLF, const char* replaceWith, std::size_t nRW ) {
    impl::replace( buffer, size, N, lookFor, nLF, replaceWith, nRW );
    return *this;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
replace( const String<S>& lookFor, const char* replaceWith, std::size_t nRW ) {
    return replace( lookFor.asCString(), lookFor.length(), replaceWith, nRW );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
replace( char lookFor, const String<S>& replaceWith ) {
    return replace( &lookFor, 1_uz, replaceWith.asCString(), replaceWith.length() );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
replace( const char* lookFor, const String<S>& replaceWith ) {
    return replace( lookFor, std::strlen(lookFor), replaceWith.asCString(), replaceWith.length() );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
replace( const char* lookFor, std::size_t nLF, const String<S>& replaceWith ) {
    return replace( lookFor, nLF, replaceWith.asCString(), replaceWith.length() );
}

template<std::size_t N>
template<std::size_t S1, std::size_t S2>
constexpr String<N>& String<N>::
replace( const String<S1>& lookFor, const String<S2>& replaceWith ) {
    return replace( lookFor.asCString(), lookFor.length(), replaceWith.asCString(), replaceWith.length() );
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( char lookFor, char replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, char replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, std::size_t nLF, char replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, nLF, replaceWith );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getReplaced( const String<S>& lookFor, char replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( char lookFor, const char* replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, const char* replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, std::size_t nLF, const char* replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, nLF, replaceWith );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getReplaced( const String<S>& lookFor, const char* replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( char lookFor, const char* replaceWith, std::size_t nRW ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith, nRW );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, const char* replaceWith, std::size_t nRW ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith, nRW );
    return tmp;
}

template<std::size_t N>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, std::size_t nLF, const char* replaceWith, std::size_t nRW ) const {
    String tmp(*this);
    tmp.replace( lookFor, nLF, replaceWith, nRW );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getReplaced( const String<S>& lookFor, const char* replaceWith, std::size_t nRW ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith, nRW );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getReplaced( char lookFor, const String<S>& replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, const String<S>& replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N> String<N>::
getReplaced( const char* lookFor, std::size_t nLF, const String<S>& replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, nLF, replaceWith );
    return tmp;
}

template<std::size_t N>
template<std::size_t S1, std::size_t S2>
constexpr String<N> String<N>::
getReplaced( const String<S1>& lookFor, const String<S2>& replaceWith ) const {
    String tmp(*this);
    tmp.replace( lookFor, replaceWith );
    return tmp;
}

/* Operations: In/Out-of-Place - subString */
template<std::size_t N>
constexpr String<N>& String<N>::
subString( ConstIterator start, ConstIterator end ) {
    impl::subString( buffer, size, N, start, end );
    return *this;
}

template<std::size_t N>
constexpr String<N> String<N>::
getSubString( ConstIterator start, ConstIterator end ) const {
    String tmp;
    tmp.append( start, static_cast<std::size_t>(end - start) );
    return tmp;
}

/* Operations: Operator Overload - += */
template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( const char* rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( const uint8_t* rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( char rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( int8_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( int16_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( int32_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( int64_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( uint8_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( uint16_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( uint32_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
constexpr String<N>& String<N>::
operator+=( uint64_t rhs ) {
    return append( rhs );
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>& String<N>::
operator+=( const String<S>& rhs ) {
    return append( rhs );
}

/* Operations: Operator Overload - +(this, rhs) */
template<std::size_t N>
constexpr String<N> String<N>::
operator+( const char* rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const uint8_t* rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( char rhs ) const {
    return getAppended( rhs );
}


template<std::size_t N>
constexpr String<N> String<N>::
operator+( const int8_t& rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const int16_t& rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const int32_t& rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const int64_t& rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const uint8_t& rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const uint16_t& rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const uint32_t& rhs ) const {
    return getAppended( rhs );
}

template<std::size_t N>
constexpr String<N> String<N>::
operator+( const uint64_t& rhs ) const {
    return getAppended( rhs );
}

/* Operations: Operator Overload - +(lhs, String) */
// template<std::size_t N>
// constexpr String<N>
// operator+( const char* lhs, const String<N>& rhs ) { String<N> result(lhs); result.append(rhs); return result; }

// template<std::size_t N>
// constexpr String<N>
// operator+( const uint8_t* lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N, std::size_t S>
// constexpr String<EDF::max(N, S)>
// operator+( const char (&lhs)[S], const String<N>& rhs ) { String<EDF::max(N,S)> result(lhs); result.append(rhs); return result; }

// template<std::size_t N, std::size_t S>
// constexpr String<EDF::max(S,N)>
// operator+( const uint8_t (&lhs)[S], const String<N>& rhs ) {
//     String<EDF::max(S,N)> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( char lhs, const String<N>& rhs ) { String<N> result(lhs); result.append(rhs); return result; }

// template<std::size_t N>
// constexpr String<N>
// operator+( int8_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( int16_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( int32_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( int64_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( uint8_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( uint16_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( uint32_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N>
// constexpr String<N>
// operator+( uint64_t lhs, const String<N>& rhs ) {
//     String<N> result(lhs);
//     result.append(rhs);
//     return result;
// }

// template<std::size_t N, std::size_t S>
// constexpr String<EDF::max(N, S)>
// operator+( const String<S>& lhs, const String<N>& rhs ) {
//     String<EDF::max(N, S)> result(lhs);
//     result.append(rhs);
//     return result;
// }

/* Iterators */
template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
begin() {
    return Iterator( buffer );
}

template<std::size_t N>
constexpr typename String<N>::ConstIterator String<N>::
begin() const {
    return ConstIterator( buffer );
}

template<std::size_t N>
constexpr typename String<N>::ConstIterator String<N>::
cbegin() const {
    return ConstIterator( buffer );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
end() {
    return Iterator( buffer + length() );
}

template<std::size_t N>
constexpr typename String<N>::ConstIterator String<N>::
end() const {
    return ConstIterator( buffer + length() );
}

template<std::size_t N>
constexpr typename String<N>::ConstIterator String<N>::
cend() const {
    return ConstIterator( buffer + length() );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rbegin() {
    return ReverseIterator( end() );
}

template<std::size_t N>
constexpr typename String<N>::ConstReverseIterator String<N>::
rbegin() const {
    return ConstReverseIterator( end() );
}

template<std::size_t N>
constexpr typename String<N>::ConstReverseIterator String<N>::
crbegin() const {
    return ConstReverseIterator( end() );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rend() {
    return ReverseIterator( begin() );
}

template<std::size_t N>
constexpr typename String<N>::ConstReverseIterator String<N>::
rend() const {
    return ConstReverseIterator( begin() );
}

template<std::size_t N>
constexpr typename String<N>::ConstReverseIterator String<N>::
crend() const {
    return ConstReverseIterator( begin() );
}

} /* EDF */