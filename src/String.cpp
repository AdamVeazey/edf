/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/String.hpp"
#include "EDF/Assert.hpp"

#include <cstring>
#include <memory>
#include <cmath>
#include <algorithm>

namespace EDF {
namespace impl {

/* Helper functions */
static void terminate( char* buffer, std::size_t& size ) {
    buffer[size] = '\0';
}

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
    EDF_ASSERTD( base >= 2, "base has to be within the range [2,36]" );
    EDF_ASSERTD( base <= 36, "base has to be within the range [2,36]" );
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
    const char limitNum = (base < 10) ? ('0' + static_cast<char>(base) - 1) : '9';             // 0x30 - 0x39
    const char limitUpp = (base < 36) ? ('A' + static_cast<char>(base) - 1 - 10) : 'Z';        // 0x41 - 0x5A
    const char limitLow = (base < 62) ? ('a' + static_cast<char>(base) - 1 - 10 - 26) : 'z';   // 0x61 - 0x7A
    for( ; k < len; ++k ) {
        if( str[k] >= '0' && str[k] <= limitNum )
            result = result*static_cast<T>(base) + static_cast<T>(str[k]) - '0';
        else if( str[k] >= 'A' && str[k] <= limitUpp )
            result = result*static_cast<T>(base) + static_cast<T>(str[k]) - ('A' - 10);
        else if( str[k] >= 'a' && str[k] <= limitLow )
            result = result*static_cast<T>(base) + static_cast<T>(str[k]) - ('a' - 10 - 26);
        else {
            EDF_ASSERTD( str[k] <= limitLow, "string contains invalid char for specified base" );
            break;
        }
    }
    return result * sign;
}

/*
str, len, and N are the pieces needed for a EDF::Vector, which is exactly what they represent.
*/
template<typename T>
static constexpr void string_from( char* str, std::size_t& len, std::size_t N, T value, int base ) {
    static_assert(std::is_integral_v<T>, "This only works for integer types!");
    EDF_ASSERTD( base >= 2, "base has to be within the range [2,36]" );
    EDF_ASSERTD( base <= 36, "base has to be within the range [2,36]" );

    // handle edge case of 0
    if( value == 0 ){
        str[0] = '0';
        len = 1;
        terminate( str, len );
        return;
    }

    std::size_t k = N - 1;                  // start the index at the end of the strings buffer
    bool negative = false;                  // only used for when T is signed. Probably optimized out when T is unsigned
    if constexpr( std::is_signed_v<T> ) {   // deal with sign if number is signed
        if( value < 0 ) {
            if( value == std::numeric_limits<T>::min() ) { // handle edge case when value = -value causes overflow
                string_from<std::make_unsigned_t<T>>( str, len, N, std::make_unsigned_t<T>(value), base );
                if( base == 10 ){
                    std::memmove( str + 1, str, ++len );
                    str[0] = '-';
                    terminate( str, len );
                }
                return;
            }
            else if( base != 10 ) {
                string_from<std::make_unsigned_t<T>>( str, len, N, std::make_unsigned_t<T>(value), base );
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
    for( str[k--] = '\0'; value; --k, value /= static_cast<T>(base) ) {
        EDF_ASSERTD( k < N, "if k rolled over, not enough space in the string" );
        str[k] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[value % static_cast<T>(base)];
    }
    if constexpr( std::is_signed_v<T> ) {
        if( negative && (base == 10) ) {
            EDF_ASSERTD( k < N, "if k rolled over, not enough space in the string" );
            str[k--] = '-';  // if negative sign is needed, add it now
        }
    }
    std::size_t sizeUsed = N - (++k);   // find how the number of digits read in backwards
    len = sizeUsed - 1;                 // calculate the new length, -1 for null
    std::memmove( str, str + k, sizeUsed ); // shift over the whole thing so it starts at index 0
    terminate( str, len );
}

static Iterator begin( const char* buffer, const std::size_t& size, std::size_t N ) {
    (void)size;
    (void)N;
    return Iterator( buffer );
}

static ConstIterator cbegin( const char* buffer, const std::size_t& size, std::size_t N ) {
    (void)size;
    (void)N;
    return ConstIterator( buffer );
}

static Iterator end( const char* buffer, const std::size_t& size, std::size_t N ) {
    (void)N;
    return Iterator( buffer + size );
}

static ConstIterator cend( const char* buffer, const std::size_t& size, std::size_t N ) {
    (void)N;
    return ConstIterator( buffer + size );
}

static ReverseIterator rbegin( const char* buffer, const std::size_t& size, std::size_t N ) {
    return ReverseIterator( end( buffer, size, N ) );
}

static ConstReverseIterator const crbegin( const char* buffer, const std::size_t& size, std::size_t N ) {
    return ConstReverseIterator( cend( buffer, size, N ) );
}

static ReverseIterator rend( const char* buffer, const std::size_t& size, std::size_t N ) {
    return ReverseIterator( begin( buffer, size, N ) );
}

static ConstReverseIterator crend( const char* buffer, const std::size_t& size, std::size_t N ) {
    return ConstReverseIterator( cbegin( buffer, size, N ) );
}

static bool isFull( const char* buffer, const std::size_t& size, std::size_t N ) {
    (void)buffer;
    return size == (N-1);
}

static std::size_t maxLength( const char* buffer, const std::size_t& size, std::size_t N ) {
    (void)buffer;
    (void)size;
    return N-1;
}

/* Constructors */

void make_string( char* buffer, std::size_t& size, std::size_t N ) {
    EDF_ASSERTD( N > 0, "buffer must be large enough to contain a single character" );
    size = 0;
    terminate( buffer, size );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, const char* str, std::size_t n ) {
    EDF_ASSERTD( n == std::strlen(str), "n needs to represent string length, not buffer size" );
    EDF_ASSERTD( ((str != nullptr) && (n > 0)), "if n is not 0, str can't be nullptr" );
    size = 0;
    EDF_ASSERTD( (n + size) <= (maxLength(buffer, size, N)), "str can fit" );
    for( size = 0; size < n; ++size ) {
        buffer[size] = str[size];
    }
    terminate( buffer, size );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, char ch ) {
    size = 0;
    EDF_ASSERTD( size < (N-1), "character can fit" );
    buffer[size++] = ch;
    terminate( buffer, size );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, int8_t value, int base ) {
    string_from( buffer, size, N, value, base );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, int16_t value, int base ) {
    string_from( buffer, size, N, value, base );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, int32_t value, int base ) {
    string_from( buffer, size, N, value, base );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, int64_t value, int base ) {
    string_from( buffer, size, N, value, base );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, uint32_t value, int base ) {
    string_from( buffer, size, N, value, base );
}

void make_string( char* buffer, std::size_t& size, std::size_t N, uint64_t value, int base ) {
    string_from( buffer, size, N, value, base );
}

int32_t toInt32_t( const char* buffer, const std::size_t& size, int base ) {
    return string_to<int32_t>( buffer, size, base );
}

int64_t toInt64_t( const char* buffer, const std::size_t& size, int base ) {
    return string_to<int64_t>( buffer, size, base );
}

uint32_t toUint32_t( const char* buffer, const std::size_t& size, int base ) {
    return string_to<uint32_t>( buffer, size, base );
}

uint64_t toUint64_t( const char* buffer, const std::size_t& size, int base ) {
    return string_to<uint64_t>( buffer, size, base );
}

Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, char value ) {
    EDF_ASSERTD( pos >= cbegin( buffer, size, N ), "position must be valid" );
    EDF_ASSERTD( pos <= cend( buffer, size, N ), "position must be valid" );
    EDF_ASSERTD( !isFull( buffer, size, N ), "must be able to fit value" );
    EDF_ASSERTD( value != '\0', "use erase() instead" );

    Iterator position = begin(buffer, size, N) + (pos - begin(buffer, size, N));
    std::move_backward( position, end(buffer, size, N), end(buffer, size, N) + 1 );
    *position = value;   // insert new element at pos
    ++size;
    terminate( buffer, size );
    return position;
}

Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, std::size_t count, char value ) {
    EDF_ASSERTD( pos >= cbegin(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( pos <= cend(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( (count + size) <= maxLength(buffer, size, N), "must be able to fit value" );
    EDF_ASSERTD( value != '\0', "use erase() instead" );
    EDF_ASSERTD((cend(buffer, size, N) + count) <= (cbegin(buffer, size, N) + maxLength(buffer, size, N)), "new values must be able to fit");

    Iterator position = begin(buffer, size, N) + (pos - begin(buffer, size, N));
    std::move_backward( position, end(buffer, size, N), end(buffer, size, N) + count );
    std::fill_n( position, count, value );
    size += count;
    terminate( buffer, size );
    return position;
}

Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, std::initializer_list<char> iList ) {
    EDF_ASSERTD( pos >= cbegin(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( pos <= cend(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( (iList.size() + size) <= maxLength(buffer, size, N), "must be able to fit value" );
    for( auto&& value : iList ){
        EDF_ASSERTD( value != '\0', "no need to manually add null" );
    }
    EDF_ASSERTD((cend(buffer, size, N) + iList.size()) <= (cbegin(buffer, size, N) + maxLength(buffer, size, N)), "new values must be able to fit");

    Iterator position = begin(buffer, size, N) + (pos - begin(buffer, size, N));
    std::move_backward( position, end(buffer, size, N), end(buffer, size, N) + iList.size() );
    std::copy(iList.begin(), iList.end(), position);
    size += iList.size();
    terminate( buffer, size );
    return position;
}

Iterator insert( char* buffer, std::size_t& size, std::size_t N, ConstIterator pos, const char* str, std::size_t n ) {
    EDF_ASSERTD( str != nullptr, "incoming string may not be nullptr" );
    EDF_ASSERTD( pos >= cbegin(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( pos <= cend(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( (n + size) <= maxLength(buffer, size, N), "must be able to fit value" );
    Iterator position = begin(buffer, size, N) + (pos - begin(buffer, size, N));
    std::move_backward(position, end(buffer, size, N), end(buffer, size, N) + n );
    std::copy( str, str + n, position );
    size += n;
    terminate( buffer, size );
    return position;
}

Iterator erase( char* buffer, std::size_t& size, std::size_t N, ConstIterator first, ConstIterator last ) {
    EDF_ASSERTD(first >= cbegin(buffer, size, N), "first position must be valid");
    EDF_ASSERTD(first <= last, "first position must be less than last");
    EDF_ASSERTD(first < cend(buffer, size, N), "first position must not include end()");
    EDF_ASSERTD(last  >= first, "last position must be valid");
    EDF_ASSERTD(last  <= cend(buffer, size, N), "last position must be valid");

    // "convert" const iterator to iterator
    Iterator s = begin(buffer, size, N) + (first - begin(buffer, size, N));
    Iterator e = begin(buffer, size, N) + (last - begin(buffer, size, N));

    // shift elements to the 'left'
    std::move_backward( e, end(buffer, size, N), s + (end(buffer, size, N) - last) );

    // remove number of elements from container
    size -= static_cast<std::size_t>(e - s);
    terminate( buffer, size );
    return s;
}

void copyTo( const char* buffer, const std::size_t& size, std::size_t N, char* outputString, std::size_t maxBufferLength ) {
    EDF_ASSERTD( outputString != nullptr, "output buffer can't be nullptr" );
    EDF_ASSERTD( maxBufferLength >= (size + 1), "output buffer is large enough" );
    std::copy( begin(buffer, size, N), end(buffer, size, N) + 1, outputString );
}

Iterator find( const char* buffer, const std::size_t& size, std::size_t N, ConstIterator pos, char value ) {
    EDF_ASSERTD( value != '\0', "simply use end() or a variation instead" );
    EDF_ASSERTD( pos >= cbegin(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( pos <= cend(buffer, size, N), "position must be valid" );
    pos = std::find_if( pos, cend(buffer, size, N), [&value](char ch){
        return ch == value;
    });
    return Iterator( begin(buffer, size, N) + (pos - cbegin(buffer, size, N)) );
}

Iterator find( const char* buffer, const std::size_t& size, std::size_t N, ConstIterator pos, const char* value, std::size_t n ) {
    EDF_ASSERTD( value != nullptr, "value may not be nullptr" );
    EDF_ASSERTD( n == std::strlen(value), "n needs to represent string length, not buffer size" );
    EDF_ASSERTD( pos >= cbegin(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( pos <= cend(buffer, size, N), "position must be valid" );
    for(; pos != end(buffer, size, N); ++pos ) {
        if( *pos == value[0] ) {    // first character matches
            bool match = true;
            for( std::size_t k = 1; k < n; ++k ) {
                if( *(pos + k) != value[k] ) {  // did any character not match?
                    match = false;
                    break;
                }
            }
            if( match ) {
                return Iterator( begin(buffer, size, N) + (pos - cbegin(buffer, size, N)) );
            }
        }
    }
    return Iterator( begin(buffer, size, N) + (pos - cbegin(buffer, size, N)) );
}

ReverseIterator rfind( const char* buffer, const std::size_t& size, std::size_t N, ConstReverseIterator pos, char value ) {
    EDF_ASSERTD( value != '\0', "simply use end() or a variation instead" );
    EDF_ASSERTD( pos >= crbegin(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( pos <= crend(buffer, size, N), "position must be valid" );
    pos = std::find_if( pos, crend(buffer, size, N), [&value](char ch){
        return ch == value;
    });
    return ReverseIterator( const_cast<Iterator>(pos.base()) );
}

ReverseIterator rfind( const char* buffer, const std::size_t& size, std::size_t N, ConstReverseIterator pos, const char* value, std::size_t n ) {
    EDF_ASSERTD( value != nullptr, "value must not be nullptr" );
    EDF_ASSERTD( pos >= crbegin(buffer, size, N), "position must be valid" );
    EDF_ASSERTD( pos < crend(buffer, size, N), "position must be valid" );
    pos = std::find_if( pos, crend(buffer, size, N), [&value, &n](const char& ch) {
        if( ch == value[n-1] ) {        // last character matches
            return std::memcmp( &ch - (n-1), value, n ) == 0;
        }
        return false;
    });
    return ReverseIterator( const_cast<Iterator>(pos.base()) );
}

bool equals( const char* buffer, const std::size_t& size, std::size_t N, const char* value, std::size_t n ) {
    (void)N;
    EDF_ASSERTD( value != nullptr, "value must not be nullptr" );
    EDF_ASSERTD( n == std::strlen(value), "n needs to represent string length, not buffer size" );
    if( size != n ) return false; // lengths are not the same, so the strings are not equal
    for( std::size_t k = 0; k < size; ++k ) {
        if( buffer[k] != value[k] ) return false; // character didn't match, not equal
    }
    return true; // strings are equal!
}

void strip( char* buffer, std::size_t& size, std::size_t N, char value ) {
    (void)N;
    constexpr auto isPrintable = []( char ch ) -> bool {
        return ch > ' ' && ch <= '~';
    };
    std::size_t n = 0;
    for( std::size_t k = 0; k < size; ++k ) {
        auto& ch = buffer[k];
        if( ((value == '\0') && isPrintable( ch )) ||
            ((value != '\0') && (value != ch))
        ) {
            buffer[n++] = ch; // shift left if whitespace
        }
    }
    size = n;
    terminate( buffer, size );
}

void strip( char* buffer, std::size_t& size, std::size_t N, const char* values, std::size_t n ){
    EDF_ASSERTD( values != nullptr, "values must not be nullptr" );
    for( std::size_t k = 0; k < n; ++k ) {
        strip( buffer, size, N, values[k] );
    }
}

void trimLeft( char* buffer, std::size_t& size, std::size_t N, char value ) {
    constexpr auto isNotMatch = [](char ch, char value) -> bool {
        return ( ((value == '\0') && (ch > ' ' && ch <= '~')) || // if value is default '\0', check if printable
                 ((value != '\0') && (value != ch)) // else, check if ch matches
        );
    };
    auto firstNonMatch = std::find_if( begin(buffer, size, N), end(buffer, size, N), [&value, &isNotMatch](char ch) {
        return isNotMatch(ch, value);
    });
    if( firstNonMatch != begin(buffer, size, N) ) {
        erase( buffer, size, N, begin(buffer, size, N), firstNonMatch );
    }
}

void trimLeft( char* buffer, std::size_t& size, std::size_t N, const char* values, std::size_t n ) {
    EDF_ASSERTD( values != nullptr, "values must not be nullptr" );
    auto pos = std::find_if( begin(buffer, size, N), end(buffer, size, N), [values, n](char ch) {
        return std::none_of(values, values + n, [&](char value){
            return ch == value;
        });
    });
    if( pos != begin(buffer, size, N) ) {
        erase( buffer, size, N, begin(buffer, size, N), pos );
    }
}

void trimRight( char* buffer, std::size_t& size, std::size_t N, char value ) {
    constexpr auto isNotMatch = [](char ch, char value) -> bool {
        return ( ((value == '\0') && (ch > ' ' && ch <= '~')) || // if value is default '\0', check if printable
                 ((value != '\0') && (value != ch)) // else, check if ch matches
        );
    };
    auto firstNonMatch = std::find_if( rbegin(buffer, size, N), rend(buffer, size, N), [&value, &isNotMatch](char ch) {
        return isNotMatch( ch, value );
    });
    if( firstNonMatch != rbegin(buffer, size, N) ) {
        erase( buffer, size, N, firstNonMatch.base(), end(buffer, size, N) );
    }
}

void trimRight( char* buffer, std::size_t& size, std::size_t N, const char* values, std::size_t n ) {
    EDF_ASSERTD( values != nullptr, "values must not be nullptr" );
    auto firstNonMatch = std::find_if( rbegin(buffer, size, N), rend(buffer, size, N), [&values, &n](char ch) {
        return std::none_of(values, values + n, [&](char value){
            return ch == value;
        });
    });
    if( firstNonMatch != rbegin(buffer, size, N) ) {
        erase( buffer, size, N, firstNonMatch.base(), end(buffer, size, N) );
    }
}

void reverse( char* buffer, std::size_t& size, std::size_t N ) {
    if( size >= 2 ) { // needs at least 2 elements
        for( auto b = begin(buffer, size, N), e = (end(buffer, size, N) - 1); b < e; ++b, --e ){
            std::swap( *b, *e );
        }
    }
}

void toLower( char* buffer, std::size_t& size, std::size_t N ) {
    (void)N;
    for( size_t k = 0; k < size; ++k ) {
        char& ch = buffer[k];
        if( ch >= 'A' && ch <= 'Z' ){ // is ch uppercase?
            ch += 'a' - 'A'; // change it to lower, by "jumping" from 'A' to 'a'
        }
    }
}

void toUpper( char* buffer, std::size_t& size, std::size_t N ) {
    (void)N;
    for( size_t k = 0; k < size; ++k ) {
        char& ch = buffer[k];
        if( ch >= 'a' && ch <= 'z' ){ // is ch lowercase?
            ch -= 'a' - 'A'; // change it to upper, by "jumping" from 'a' to 'A'
        }
    }
}

void replace(
    char* buffer, std::size_t& size, std::size_t N,
    const char* lookFor, std::size_t nLF,
    const char* replaceWith, std::size_t nRW
) {
    for( ReverseIterator posLookFor = rfind( buffer, size, N, crbegin(buffer, size, N), lookFor, nLF ); posLookFor != crend(buffer, size, N); ) {
        auto strBegin = (posLookFor + static_cast<ReverseIterator::difference_type>(nLF)).base();
        auto strEnd = posLookFor.base();
        if( (strBegin >= begin(buffer, size, N)) && (strEnd <= end(buffer, size, N)) ) {
            erase( buffer, size, N, strBegin, strEnd );
            insert( buffer, size, N, strBegin, replaceWith, nRW );
        }
        if( (posLookFor + static_cast<ReverseIterator::difference_type>(nLF)) >= crend(buffer, size, N) ) {
            break;
        }
        posLookFor = rfind( buffer, size, N, posLookFor + static_cast<ReverseIterator::difference_type>(nLF), lookFor, nLF );
    }
}

void subString( char* buffer, std::size_t& size, std::size_t N, ConstIterator start, ConstIterator end ) {
    EDF_ASSERTD( start < end, "start must be before end" );
    EDF_ASSERTD( end < cend(buffer, size, N), "end must be within string" );
    EDF_ASSERTD( end >= cbegin(buffer, size, N), "end must be within string" );
    EDF_ASSERTD( start < cend(buffer, size, N), "start must be within string" );
    EDF_ASSERTD( start >= cbegin(buffer, size, N), "end must be within string" );
    erase( buffer, size, N, end, cend(buffer, size, N) );
    erase( buffer, size, N, begin(buffer, size, N), start );
}

} /* impl */
} /* EDF */