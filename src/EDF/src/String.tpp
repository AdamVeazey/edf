/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/String.hpp"

namespace EDF {

/*
DOES check for '-' or '+' when T is signed and base == 10

Assumes 'str' only contains a number ONLY. No prefix for 0x, or 0b or anything else is
automatically checked. Specify a base between 2 and 36 if the str doesn't represent a
base 10 number.

Does not skip whitespace
*/
template<typename T>
static constexpr T string_to( const char* str, const std::size_t& len, int base ) {
    static_assert( std::is_integral_v<T>, "T must be an integer type!");
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    size_t k = 0;
    T result = 0;
    T sign = 1;
    if constexpr( std::is_signed_v<T> ) {
        if( base == 10 ) { // only check sign for base 10 values
            if( str[k] == '-' ) {
                sign = -1;
                ++k;
            }
            else if( str[k] == '+' ) {
                ++k;
            }
        }
    }
    const char limitNum = (base < 10) ? ('0' + base - 1) : '9';             // 0x30 - 0x39
    const char limitUpp = (base < 36) ? ('A' + base - 1 - 10) : 'Z';        // 0x41 - 0x5A
    const char limitLow = (base < 62) ? ('a' + base - 1 - 10 - 26) : 'z';   // 0x61 - 0x7A
    for( ; k < len; ++k ) {
        if( str[k] >= '0' && str[k] <= limitNum )
            result = result*base + str[k] - '0';
        else if( str[k] >= 'A' && str[k] <= limitUpp )
            result = result*base + str[k] - ('A' - 10);
        else if( str[k] >= 'a' && str[k] <= limitLow )
            result = result*base + str[k] - ('a' - 10 - 26);
        else {
            EDF_ASSERTD( str[k] <= limitLow ); // string contains invalid char for specified base
            break;
        }
    }
    return result * sign;
}

/*
str, len, and N are the pieces needed for a EDF::Vector, which is exactly what they represent.
*/
template<typename T>
static constexpr void string_from( char* str, const std::size_t& len, std::size_t N, T value, int base ) {
    static_assert(std::is_integral_v<T>, "This only works for integer types!");
    std::size_t& mutateLen = const_cast<std::size_t&>(len); // in this case, we need to make sure we're mutating len

    // handle edge case of 0
    if( value == 0 ){
        str[0] = '0';
        str[1] = '\0';
        mutateLen = 1;
        return;
    }

    std::size_t k = N - 1;                  // start the index at the end of the strings buffer
    bool negative = false;                  // only used for when T is signed. Probably optimized out when T is unsigned
    if constexpr( std::is_signed_v<T> ) {   // deal with sign if number is signed
        if( value < 0 ) {
            if( value == std::numeric_limits<T>::min() ) { // handle edge case when value = -value causes overflow
                string_from<std::make_unsigned_t<T>>( str, len, N, value, base );
                if( base == 10 ){
                    std::memmove( str + 1, str, ++mutateLen );
                    str[0] = '-';
                }
                return;
            }
            else if( base != 10 ) {
                string_from<std::make_unsigned_t<T>>( str, len, N, value, base );
                return;
            }
            negative = true;
            value = -value;      // turn back to positive, to treat it like it was unsigned
        }
    }
    /*
    Iterate backwards one digit at a time, right to left. To start at the 1's place, then 10's then 100's, etc..
    4321
       ^
      ^
     ^
    ^
    Building up the string backwards.
    */
    for( str[k--] = '\0'; value; --k, value /= base ) {
        EDF_ASSERTD( k < N ); // if k rolled over, not enough space in the string
        str[k] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[value % base];
    }
    if constexpr( std::is_signed_v<T> ) {
        if( negative && (base == 10) ) {
            EDF_ASSERTD( k < N ); // if k rolled over, not enough space in the string
            str[k--] = '-';  // if negative sign is needed, add it now
        }
    }
    std::size_t sizeUsed = N - (++k);  // find how the number of digits read in backwards
    mutateLen = sizeUsed - 1;          // calculate the new length, -1 for null
    std::memmove( str, str + k, sizeUsed ); // shift over the whole thing so it starts at index 0
}

template<std::size_t N>
constexpr String<N>::
String() {
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const char* str ) {
    EDF_ASSERTD( (std::strlen(str) + length()) <= maxLength() );// str can fit
    // while str is not null, and buffer has enough space for '\0'
    while( *str ) {
        buffer.pushBack( *str++ );
    }
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const uint8_t* str ) {
    EDF_ASSERTD( (std::strlen(reinterpret_cast<const char*>(str)) + length()) <= maxLength() );// str can fit
    // while str is not null, and buffer has enough space for '\0'
    while( *str ) {
        buffer.pushBack( *str++ );
    }
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const char* str, std::size_t n ) {
    EDF_ASSERTD( n == std::strlen(str) ); // n represents string length, not buffer size
    EDF_ASSERTD( ((str != nullptr) && (n > 0)) );   // if n is not 0, str can't be nullptr
    EDF_ASSERTD( (n + length()) <= maxLength() );   // str can fit
    for( std::size_t k = 0; k < n; ++k ) {
        buffer.pushBack( str[k] );
    }
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const uint8_t* str, std::size_t n ) {
    EDF_ASSERTD( n == std::strlen(reinterpret_cast<const char*>(str)) ); // n represents string length, not buffer size
    EDF_ASSERTD( ((str != nullptr) && (n > 0)) );   // if n is not 0, str can't be nullptr
    EDF_ASSERTD( (n + length()) <= maxLength() );   // str can fit
    for( std::size_t k = 0; k < n; ++k ) {
        buffer.pushBack( str[k] );
    }
    terminate();
}


template<std::size_t N>
template<std::size_t S>
constexpr String<N>::
String( const char (&str)[S] ) {
    std::size_t len = std::strlen( str );
    EDF_ASSERTD( len < S );                           // must be a valid string
    EDF_ASSERTD( (len + length()) <= maxLength() );   // str can fit
    for( std::size_t k = 0; k < len; ++k ) {
        buffer.pushBack( str[k] );
    }
    terminate();
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>::
String( const uint8_t (&str)[S] ) {
    std::size_t len = std::strlen( str );
    EDF_ASSERTD( len < S );                           // must be a valid string
    EDF_ASSERTD( (len + length()) <= maxLength() );   // str can fit
    for( std::size_t k = 0; k < len; ++k ) {
        buffer.pushBack( str[k] );
    }
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( char ch ) {
    EDF_ASSERTD( !isFull() );   // character can fit
    buffer.pushBack( ch );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const int8_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const int16_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const int32_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const int64_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const uint8_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const uint16_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const uint32_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
constexpr String<N>::
String( const uint64_t& value, std::size_t base ) {
    EDF_ASSERTD( base >= 2 );   // base has to be within the range [2,36]
    EDF_ASSERTD( base <= 36 );  // base has to be within the range [2,36]
    string_from(
        buffer.data(),
        buffer.length(),
        buffer.maxLength(),
        value,
        base
    );
    terminate();
}

template<std::size_t N>
template<std::size_t S>
constexpr String<N>::
String( const String<S>& o ) {
    EDF_ASSERTD( o.length() <= maxLength() ); // N must greater than or equal to length of o
    for( auto&& ch : o ) {
        buffer.pushBack( ch );
    }
    terminate();
}

template<std::size_t N>
constexpr int32_t String<N>::
toInt32_t( int base ) const {
    return string_to<int32_t>( buffer.data(), buffer.length(), base );
}

template<std::size_t N>
constexpr int64_t String<N>::
toInt64_t( int base ) const {
    return string_to<int64_t>( buffer.data(), buffer.length(), base );
}

template<std::size_t N>
constexpr uint32_t String<N>::
toUint32_t( int base ) const {
    return string_to<uint32_t>( buffer.data(), buffer.length(), base );
}

template<std::size_t N>
constexpr uint64_t String<N>::
toUint64_t( int base ) const {
    return string_to<uint64_t>( buffer.data(), buffer.length(), base );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, char&& value) {
    EDF_ASSERTD( pos >= cbegin() );  // position must be valid
    EDF_ASSERTD( pos <= cend() );    // position must be valid
    EDF_ASSERTD( !isFull() );      // must be able to fit value
    EDF_ASSERTD( value != '\0' );  // use erase() instead
    auto it = buffer.insert( pos, value );
    terminate();
    return it;
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, std::size_t count, const char& value ) {
    EDF_ASSERTD( pos >= cbegin() );  // position must be valid
    EDF_ASSERTD( pos <= cend() );    // position must be valid
    EDF_ASSERTD( (count + length()) <= maxLength() );    // must be able to fit value
    EDF_ASSERTD( value != '\0' );                       // use erase() instead
    auto it = buffer.insert( pos, count, value );
    terminate();
    return it;
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, std::initializer_list<char> iList ) {
    EDF_ASSERTD( pos >= cbegin() );  // position must be valid
    EDF_ASSERTD( pos <= cend() );    // position must be valid
    EDF_ASSERTD( (iList.size() + length()) <= maxLength() ); // must be able to fit value
    for( auto&& value : iList ){
        EDF_ASSERTD( value != '\0' );                       // no need to manually add null
    }
    auto it = buffer.insert( pos, iList );
    terminate();
    return it;
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
insert( ConstIterator pos, const char* str, std::size_t n ) {
    EDF_ASSERTD( str != nullptr );
    EDF_ASSERTD( pos >= cbegin() );  // position must be valid
    EDF_ASSERTD( pos <= cend() );    // position must be valid
    EDF_ASSERTD( (n + length()) <= maxLength() ); // must be able to fit value
    Iterator position = begin() + (pos - begin());
    std::move_backward(position, end(), end() + n );
    std::copy( str, str + n, position );
    std::size_t& mutateLen = const_cast<std::size_t&>(length()); // in this case, we need to make sure we're mutating len
    mutateLen += n;
    terminate();
    return position;
}

template<std::size_t N>
constexpr void String<N>::
copyTo( char* outputString, std::size_t maxBufferLength ) const {
    EDF_ASSERTD( outputString != nullptr ); // output buffer can't be nullptr
    EDF_ASSERTD( maxBufferLength >= (length() + 1) );     // output buffer is large enough
    std::copy( begin(), end() + 1, outputString );
}


template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( ConstIterator pos, const char& value ) const {
    EDF_ASSERTD( value != '\0' );    // simply use end() or a variation instead
    EDF_ASSERTD( pos >= cbegin() );  // position must be valid
    EDF_ASSERTD( pos <= cend() );    // position must be valid
    pos = std::find_if( pos, end(), [&value](char ch){
        return ch == value;
    });
    return Iterator( begin() + (pos - cbegin()) );
}

template<std::size_t N>
constexpr typename String<N>::Iterator String<N>::
find( ConstIterator pos, const char* value, std::size_t n ) const {
    EDF_ASSERTD( value != nullptr );
    EDF_ASSERTD( n == std::strlen(value) ); // n represents string length, not buffer size
    EDF_ASSERTD( pos >= cbegin() ); // position must be valid
    EDF_ASSERTD( pos <= cend() );   // position must be valid
    for(; pos != end(); ++pos ) {
        if( *pos == value[0] ) {    // first character matches
            bool match = true;
            for( std::size_t k = 1; k < n; ++k ) {
                if( *(pos + k) != value[k] ) {  // did any character not match?
                    match = false;
                    break;
                }
            }
            if( match ) {
                return Iterator( begin() + (pos - cbegin()) );
            }
        }
    }
    return Iterator( begin() + (pos - cbegin()) );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( ConstReverseIterator pos, const char& value ) const {
    EDF_ASSERTD( value != '\0' );    // simply use end() or a variation instead
    EDF_ASSERTD( pos >= crbegin() ); // position must be valid
    EDF_ASSERTD( pos <= crend() );   // position must be valid
    pos = std::find_if( pos, crend(), [&value](char ch){
        return ch == value;
    });
    return ReverseIterator( const_cast<Iterator>(pos.base()) );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( ConstReverseIterator pos, const char* value ) const {
    return rfind( pos, value, std::strlen( value ) );
}

template<std::size_t N>
constexpr typename String<N>::ReverseIterator String<N>::
rfind( ConstReverseIterator pos, const char* value, std::size_t n ) const {
    EDF_ASSERTD( value != nullptr );
    EDF_ASSERTD( pos >= crbegin() );    // position must be valid
    EDF_ASSERTD( pos < crend() );       // position must be valid
    pos = std::find_if( pos, crend(), [&value, &n](const char& ch) {
        if( ch == value[n-1] ) {        // last character matches
            return std::memcmp( &ch - (n-1), value, n ) == 0;
        }
        return false;
    });
    if( pos + n-1 < rend() ) { // match was found
        pos += n-1;
    }
    return ReverseIterator( const_cast<Iterator>(pos.base()) );
}

template<std::size_t N>
constexpr bool String<N>::
equals( const char* value ) const {
    return equals( value, std::strlen( value ) );
}

template<std::size_t N>
constexpr bool String<N>::
equals( const char* value, std::size_t n ) const {
    EDF_ASSERTD( value != nullptr );
    EDF_ASSERTD( n == std::strlen(value) ); // n represents string length, not buffer size
    if( length() != n ) return false; // lengths are not the same, so the strings are not equal
    for( std::size_t k = 0; k < length(); ++k ) {
        if( buffer[k] != value[k] ) return false; // character didn't match, not equal
    }
    return true; // strings are equal!
}

template<std::size_t N>
constexpr String<N>& String<N>::
strip( const char& value ) {
    constexpr auto isPrintable = []( const char& ch ) -> bool {
        return ch > ' ' && ch <= '~';
    };
    std::size_t& mutateLen = const_cast<std::size_t&>(length()); // in this case, we need to make sure we're mutating len
    std::size_t n = 0;
    for( std::size_t k = 0; k < length(); ++k ) {
        auto& ch = buffer[k];
        if( ((value == '\0') && isPrintable( ch )) ||
            ((value != '\0') && (value != ch))
        ) {
            buffer[n++] = ch; // shift left if whitespace
        }
    }
    mutateLen = n;
    terminate();
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
    EDF_ASSERTD( values != nullptr ); // values must not be nullptr
    for( std::size_t k = 0; k < n; ++k ) {
        strip( values[k] );
    }
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
trimLeft( const char& value ) {
    constexpr auto isNotMatch = [](const char& ch, const char& value) -> bool {
        return ( ((value == '\0') && (ch <= ' ' || ch > '~')) || // if value is default '\0', check if printable
                 ((value != '\0') && (value != ch))              // else, check if ch matches
        );
    };
    auto firstNonMatch = std::find_if( begin(), end(), [&value, &isNotMatch](char ch) {
        return isNotMatch(ch, value);
    });
    if( firstNonMatch != begin() ) {
        erase( begin(), firstNonMatch );
    }
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
    EDF_ASSERTD( values != nullptr ); // values must not be nullptr
    auto pos = std::find_if( begin(), end(), [values, n](char ch) {
        return std::none_of(values, values + n, [&](char value){
            return ch == value;
        });
    });
    if( pos != begin() ) {
        erase( begin(), pos );
    }
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
trimRight( const char& value ) {
    constexpr auto isNotMatch = [](const char& ch, const char& value) -> bool {
        return ( ((value == '\0') && (ch > ' ' && ch <= '~')) || // if value is default '\0', check if printable
                 ((value != '\0') && (value != ch)) // else, check if ch matches
        );
    };
    auto firstNonMatch = std::find_if( rbegin(), rend(), [&value, &isNotMatch](const char& ch) {
        return isNotMatch( ch, value );
    });
    if( firstNonMatch != rbegin() ) {
        erase( firstNonMatch.base(), end() );
    }
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
    EDF_ASSERTD( values != nullptr ); // values must not be nullptr
    auto firstNonMatch = std::find_if( rbegin(), rend(), [&values, &n](char ch) {
        return std::none_of(values, values + n, [&](char value){
            return ch == value;
        });
    });
    if( firstNonMatch != rbegin() ) {
        erase( firstNonMatch.base(), end() );
    }
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
reverse() {
    if( length() >= 2 ) { // needs at least 2 elements
        for( auto b = begin(), e = (end() - 1); b < e; ++b, --e ){
            std::swap( *b, *e );
        }
    }
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
toLower() {
    for( char& ch : buffer ) {
        if( ch >= 'A' && ch <= 'Z' ){ // is ch uppercase?
            ch += 'a' - 'A'; // change it to lower, by "jumping" from 'A' to 'a'
        }
    }
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
toUpper() {
    for( char& ch : buffer ) {
        if( ch >= 'a' && ch <= 'z' ){ // is ch lowercase?
            ch -= 'a' - 'A'; // change it to upper, by "jumping" from 'a' to 'A'
        }
    }
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
replace(
    const char* lookFor, std::size_t nLF,
    const char* replaceWith, std::size_t nRW
) {
    for( ReverseIterator posLookFor = rfind( crbegin(), lookFor, nLF ); posLookFor != crend(); ) {
        auto strBegin = (posLookFor + 1).base();
        auto strEnd = strBegin + nLF;
        if( (strBegin >= begin()) && (strEnd <= end()) ) {
            erase( strBegin, strEnd );
            insert( strBegin, replaceWith, nRW );
        }
        posLookFor = rfind( posLookFor, lookFor, nLF );
    }
    // for( ConstIterator posLookFor = find( begin(), lookFor, nLF ); posLookFor != end(); ) {
    //     auto posLookForEnd = posLookFor + nLF;
    //     if( posLookForEnd <= end() ) {
    //         erase( posLookFor, posLookForEnd ); // erased lookFor from buffer
    //         insert( posLookFor, replaceWith, nRW );
    //     }
    //     posLookFor = find( posLookForEnd, lookFor, nLF );
    // }
    return *this;
}

template<std::size_t N>
constexpr String<N>& String<N>::
subString( ConstIterator start, ConstIterator end ) {
    EDF_ASSERTD( start < end );             // start must be before end
    EDF_ASSERTD( end < this->end() );       // end must be within string
    EDF_ASSERTD( end >= this->begin() );    // end must be within string
    EDF_ASSERTD( start < this->end() );     // start must be within string
    EDF_ASSERTD( start >= this->begin() );  // end must be within string
    erase( end, this->end() );
    erase( begin(), start );
    return *this;
}

} /* EDF */