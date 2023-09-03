/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Vector.hpp"

#include <cstring> // for std::strlen, std::memcpy, and memcmp

namespace EDF {

template<std::size_t N>
class String final {
private:
    Vector<char, N> buffer;
private:
    constexpr void terminate() { *buffer.end() = '\0'; }
public:
    /* Constructors */
    constexpr String();

    constexpr String( const char* str );
    constexpr String( const uint8_t* str );

    constexpr String( const char* str, std::size_t n );
    constexpr String( const uint8_t* str, std::size_t n );

    template<std::size_t S>
    constexpr String( const char (&str)[S] );
    template<std::size_t S>
    constexpr String( const uint8_t (&str)[S] );

    constexpr String( char ch );

    constexpr String( int8_t value, std::size_t base = 10 );
    constexpr String( int16_t value, std::size_t base = 10 );
    constexpr String( int32_t value, std::size_t base = 10 );
    constexpr String( int64_t value, std::size_t base = 10 );
    constexpr String( uint8_t value, std::size_t base = 10 );
    constexpr String( uint16_t value, std::size_t base = 10 );
    constexpr String( uint32_t value, std::size_t base = 10 );
    constexpr String( uint64_t value, std::size_t base = 10 );

    template<std::size_t S>
    constexpr String( const String<S>& o );

    ~String() = default;

    using Iterator = typename Vector<char, N>::Iterator;
    using ConstIterator = typename Vector<char, N>::ConstIterator;
    using ReverseIterator = typename Vector<char, N>::ReverseIterator;
    using ConstReverseIterator = typename Vector<char, N>::ConstReverseIterator;

    /* Is Questions */
    constexpr bool isEmpty()                                                                const { return buffer.isEmpty(); }
    constexpr bool isFull()                                                                 const { return buffer.length() == (N-1); }

    /* Capacity */
    constexpr const std::size_t& length()                                                   const { return buffer.length(); }
    constexpr std::size_t maxLength()                                                       const { return buffer.maxLength()-1; }

    /* Element access */
    constexpr char& at( std::size_t index )                                                       { return buffer.at( index ); }
    constexpr const char& at( std::size_t index )                                           const { return buffer.at( index ); }

    constexpr char& operator[]( std::size_t index )                                               { return buffer[index]; }
    constexpr const char& operator[]( std::size_t index )                                   const { return buffer[index]; }

    constexpr char* asCString()                                                                   { return buffer.data(); }
    constexpr const char* asCString()                                                       const { return buffer.data(); }
    constexpr uint8_t* asByteData()                                                               { return reinterpret_cast<uint8_t*>(buffer.data()); }
    constexpr const uint8_t* asByteData()                                                   const { return reinterpret_cast<const uint8_t*>(buffer.data()); }

    /* Conversions: toX */
    constexpr int8_t toInt8_t( int base = 10 )                                              const { return toInt32_t( base ); }
    constexpr int16_t toInt16_t( int base = 10 )                                            const { return toInt32_t( base ); }
    constexpr int32_t toInt32_t( int base = 10 )                                            const;
    constexpr int64_t toInt64_t( int base = 10 )                                            const;
    constexpr uint8_t toUint8_t( int base = 10 )                                            const { return toUint32_t( base ); }
    constexpr uint16_t toUint16_t( int base = 10 )                                          const { return toUint32_t( base ); }
    constexpr uint32_t toUint32_t( int base = 10 )                                          const;
    constexpr uint64_t toUint64_t( int base = 10 )                                          const;

    /* Operations: In/Out-of-Place - append */
    constexpr String& append( const char* str )                                                   { insert( end(), str ); return *this; }
    constexpr String& append( const uint8_t* str )                                                { insert( end(), str ); return *this; }

    constexpr String& append( const char* str, std::size_t n )                                    { insert( end(), str, n ); return *this; }
    constexpr String& append( const uint8_t* str, std::size_t n )                                 { insert( end(), str, n ); return *this; }

    template<std::size_t S>
    constexpr String& append( const char (&str)[S] )                                              { insert( end(), str ); return *this; }
    template<std::size_t S>
    constexpr String& append( const uint8_t (&str)[S] )                                           { insert( end(), str ); return *this; }

    constexpr String& append( char ch )                                                           { insert( end(), ch ); return *this; }

    constexpr String& append( int8_t value, std::size_t base = 10 )                               { insert( end(), value, base ); return *this; }
    constexpr String& append( int16_t value, std::size_t base = 10 )                              { insert( end(), value, base ); return *this; }
    constexpr String& append( int32_t value, std::size_t base = 10 )                              { insert( end(), value, base ); return *this; }
    constexpr String& append( int64_t value, std::size_t base = 10 )                              { insert( end(), value, base ); return *this; }
    constexpr String& append( uint8_t value, std::size_t base = 10 )                              { insert( end(), value, base ); return *this; }
    constexpr String& append( uint16_t value, std::size_t base = 10 )                             { insert( end(), value, base ); return *this; }
    constexpr String& append( uint32_t value, std::size_t base = 10 )                             { insert( end(), value, base ); return *this; }
    constexpr String& append( uint64_t value, std::size_t base = 10 )                             { insert( end(), value, base ); return *this; }

    template<std::size_t S>
    constexpr String& append( const String<S>& str )                                              { insert( end(), str ); return *this; }

    constexpr String getAppended( const char* str )                                         const { return getInserted( end(), str ); }
    constexpr String getAppended( const uint8_t* str )                                      const { return getInserted( end(), str ); }

    constexpr String getAppended( const char* str, std::size_t n )                          const { return getInserted( end(), str, n ); }
    constexpr String getAppended( const uint8_t* str, std::size_t n )                       const { return getInserted( end(), str, n ); }

    template<std::size_t S>
    constexpr String getAppended( const char (&str)[S] )                                    const { return getInserted( end(), str ); }
    template<std::size_t S>
    constexpr String getAppended( const uint8_t (&str)[S] )                                 const { return getInserted( end(), str ); }

    constexpr String getAppended( char ch )                                                 const { return getInserted( end(), ch ); }

    constexpr String getAppended( int8_t value, std::size_t base = 10 )                     const { return getInserted( end(), value, base ); }
    constexpr String getAppended( int16_t value, std::size_t base = 10 )                    const { return getInserted( end(), value, base ); }
    constexpr String getAppended( int32_t value, std::size_t base = 10 )                    const { return getInserted( end(), value, base ); }
    constexpr String getAppended( int64_t value, std::size_t base = 10 )                    const { return getInserted( end(), value, base ); }
    constexpr String getAppended( uint8_t value, std::size_t base = 10 )                    const { return getInserted( end(), value, base ); }
    constexpr String getAppended( uint16_t value, std::size_t base = 10 )                   const { return getInserted( end(), value, base ); }
    constexpr String getAppended( uint32_t value, std::size_t base = 10 )                   const { return getInserted( end(), value, base ); }
    constexpr String getAppended( uint64_t value, std::size_t base = 10 )                   const { return getInserted( end(), value, base ); }

    template<std::size_t S>
    constexpr String getAppended( const String<S>& str )                                    const { return getInserted( end(), str ); }

    /* Operations: In/Out-of-Place - insert */
    constexpr void insert( std::size_t index, char value )                                        { insert( cbegin() + index, value ); }
    constexpr void insert( std::size_t index, std::size_t count, char value )                     { insert( cbegin() + index, count, value ); }
    constexpr void insert( std::size_t index, std::initializer_list<char> iList )                 { insert( cbegin() + index, iList ); }
    constexpr Iterator insert( ConstIterator pos, char value );
    constexpr Iterator insert( ConstIterator pos, std::size_t count, char value );
    constexpr Iterator insert( ConstIterator pos, std::initializer_list<char> iList );

    constexpr void insert( std::size_t index, const char* str )                                   { insert( cbegin() + index, str ); }
    constexpr void insert( std::size_t index, const uint8_t* str )                                { insert( cbegin() + index, str ); }
    constexpr Iterator insert( ConstIterator pos, const uint8_t* str )                            { return insert( pos, reinterpret_cast<const char*>(str) ); }
    constexpr Iterator insert( ConstIterator pos, const char* str )                               { return insert( pos, str, std::strlen(str) ); }

    constexpr void insert( std::size_t index, const char* str, std::size_t n )                    { insert( cbegin() + index, str, n ); }
    constexpr void insert( std::size_t index, const uint8_t* str, std::size_t n )                 { insert( cbegin() + index, str, n ); }
    constexpr Iterator insert( ConstIterator pos, const uint8_t* str, std::size_t n )             { return insert( pos, reinterpret_cast<const char*>(str), n ); }
    constexpr Iterator insert( ConstIterator pos, const char* str, std::size_t n );

    template<std::size_t S>
    constexpr void insert( std::size_t index, const char (&str)[S] )                              { insert( cbegin() + index, str ); }
    template<std::size_t S>
    constexpr void insert( std::size_t index, const uint8_t (&str)[S] )                           { insert( cbegin() + index, str ); }
    template<std::size_t S>
    constexpr Iterator insert( ConstIterator pos, const uint8_t (&str)[S] )                       { return insert( pos, reinterpret_cast<const char (&)[S]>(str) ); }
    template<std::size_t S>
    constexpr Iterator insert( ConstIterator pos, const char (&str)[S] )                          { return insert( pos, str, S ); }

    constexpr void insert( std::size_t index, int8_t value, std::size_t base = 10 )               { insert( cbegin() + index, value, base ); }
    constexpr void insert( std::size_t index, int16_t value, std::size_t base = 10 )              { insert( cbegin() + index, value, base ); }
    constexpr void insert( std::size_t index, int32_t value, std::size_t base = 10 )              { insert( cbegin() + index, value, base ); }
    constexpr void insert( std::size_t index, int64_t value, std::size_t base = 10 )              { insert( cbegin() + index, value, base ); }
    constexpr void insert( std::size_t index, uint8_t value, std::size_t base = 10 )              { insert( cbegin() + index, value, base ); }
    constexpr void insert( std::size_t index, uint16_t value, std::size_t base = 10 )             { insert( cbegin() + index, value, base ); }
    constexpr void insert( std::size_t index, uint32_t value, std::size_t base = 10 )             { insert( cbegin() + index, value, base ); }
    constexpr void insert( std::size_t index, uint64_t value, std::size_t base = 10 )             { insert( cbegin() + index, value, base ); }

    constexpr Iterator insert( ConstIterator pos, int8_t value, std::size_t base = 10 )           { return insert( pos, String<8+1>( value, base ) ); }
    constexpr Iterator insert( ConstIterator pos, int16_t value, std::size_t base = 10 )          { return insert( pos, String<16+1>( value, base ) ); }
    constexpr Iterator insert( ConstIterator pos, int32_t value, std::size_t base = 10 )          { return insert( pos, String<32+1>( value, base ) ); }
    constexpr Iterator insert( ConstIterator pos, int64_t value, std::size_t base = 10 )          { return insert( pos, String<64+1>( value, base ) ); }
    constexpr Iterator insert( ConstIterator pos, uint8_t value, std::size_t base = 10 )          { return insert( pos, String<8+1>( value, base ) ); }
    constexpr Iterator insert( ConstIterator pos, uint16_t value, std::size_t base = 10 )         { return insert( pos, String<16+1>( value, base ) ); }
    constexpr Iterator insert( ConstIterator pos, uint32_t value, std::size_t base = 10 )         { return insert( pos, String<32+1>( value, base ) ); }
    constexpr Iterator insert( ConstIterator pos, uint64_t value, std::size_t base = 10 )         { return insert( pos, String<64+1>( value, base ) ); }

    template<std::size_t S>
    constexpr void insert( std::size_t index, const String<S>& str )                              { insert( cbegin() + index, str ); }
    template<std::size_t S>
    constexpr Iterator insert( ConstIterator pos, const String<S>& str )                          { return insert( pos, str.asCString(), str.length() ); }

    constexpr String getInserted( std::size_t index, char value )                           const { String tmp(*this); tmp.insert( index, value ); return tmp; }
    constexpr String getInserted( std::size_t index, std::size_t count, char value )        const { String tmp(*this); tmp.insert( index, count, value ); return tmp; }
    constexpr String getInserted( std::size_t index, std::initializer_list<char> iList )    const { String tmp(*this); tmp.insert( index, iList ); return tmp; }
    constexpr String getInserted( ConstIterator pos, char value )                           const { String tmp(*this); tmp.insert( pos - begin(), value ); return tmp; }
    constexpr String getInserted( ConstIterator pos, std::size_t count, char value )        const { String tmp(*this); tmp.insert( pos - begin(), count, value ); return tmp; }
    constexpr String getInserted( ConstIterator pos, std::initializer_list<char> iList )    const { String tmp(*this); tmp.insert( pos - begin(), iList ); return tmp; }

    constexpr String getInserted( std::size_t index, const char* str )                      const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    constexpr String getInserted( std::size_t index, const uint8_t* str )                   const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    constexpr String getInserted( ConstIterator pos, const uint8_t* str )                   const { String tmp(*this); tmp.insert( pos - begin(), str ); return tmp; }
    constexpr String getInserted( ConstIterator pos, const char* str )                      const { String tmp(*this); tmp.insert( pos - begin(), str ); return tmp; }

    constexpr String getInserted( std::size_t index, const char* str, std::size_t n )       const { String tmp(*this); tmp.insert( index, str, n ); return tmp; }
    constexpr String getInserted( std::size_t index, const uint8_t* str, std::size_t n )    const { String tmp(*this); tmp.insert( index, str, n ); return tmp; }
    constexpr String getInserted( ConstIterator pos, const uint8_t* str, std::size_t n )    const { String tmp(*this); tmp.insert( pos - begin(), str, n ); return tmp; }
    constexpr String getInserted( ConstIterator pos, const char* str, std::size_t n )       const { String tmp(*this); tmp.insert( pos - begin(), str, n ); return tmp; }

    template<std::size_t S>
    constexpr String getInserted( std::size_t index, const char (&str)[S] )                 const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    template<std::size_t S>
    constexpr String getInserted( std::size_t index, const uint8_t (&str)[S] )              const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    template<std::size_t S>
    constexpr String getInserted( ConstIterator pos, const uint8_t (&str)[S] )              const { String tmp(*this); tmp.insert( pos - begin(), str ); return tmp; }
    template<std::size_t S>
    constexpr String getInserted( ConstIterator pos, const char (&str)[S] )                 const { String tmp(*this); tmp.insert( pos - begin(), str ); return tmp; }

    constexpr String getInserted( std::size_t index, int8_t value, std::size_t base = 10 )  const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    constexpr String getInserted( std::size_t index, int16_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    constexpr String getInserted( std::size_t index, int32_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    constexpr String getInserted( std::size_t index, int64_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    constexpr String getInserted( std::size_t index, uint8_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    constexpr String getInserted( std::size_t index, uint16_t value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    constexpr String getInserted( std::size_t index, uint32_t value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    constexpr String getInserted( std::size_t index, uint64_t value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }

    constexpr String getInserted( ConstIterator pos, int8_t value, std::size_t base = 10 )  const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }
    constexpr String getInserted( ConstIterator pos, int16_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }
    constexpr String getInserted( ConstIterator pos, int32_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }
    constexpr String getInserted( ConstIterator pos, int64_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }
    constexpr String getInserted( ConstIterator pos, uint8_t value, std::size_t base = 10 ) const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }
    constexpr String getInserted( ConstIterator pos, uint16_t value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }
    constexpr String getInserted( ConstIterator pos, uint32_t value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }
    constexpr String getInserted( ConstIterator pos, uint64_t value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos - begin(), value, base ); return tmp; }

    template<std::size_t S>
    constexpr String getInserted( std::size_t index, const String<S>& str )                 const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    template<std::size_t S>
    constexpr String getInserted( ConstIterator pos, const String<S>& str )                 const { String tmp(*this); tmp.insert( pos - begin(), str ); return tmp; }

    /* Operations: In/Out-of-Place - erase */
    constexpr void erase( std::size_t index )                                                     { buffer.erase( index ); terminate(); }
    constexpr void erase( std::size_t first, std::size_t last )                                   { buffer.erase( first, last ); terminate(); }
    constexpr Iterator erase( ConstIterator pos )                                                 { auto it = buffer.erase( pos ); terminate(); return it; }
    constexpr Iterator erase( ConstIterator first, ConstIterator last )                           { auto it = buffer.erase( first, last ); terminate(); return it; }

    constexpr String getErased( std::size_t index )                                         const { String tmp(*this); tmp.erase( index ); return tmp; }
    constexpr String getErased( std::size_t first, std::size_t last )                       const { String tmp(*this); tmp.erase( first, last ); return tmp; }
    constexpr String getErased( ConstIterator pos )                                         const { String tmp(*this); tmp.erase( pos - begin() ); return tmp; }
    constexpr String getErased( ConstIterator first, ConstIterator last )                   const { String tmp(*this); tmp.erase( first - begin(), last - begin() ); return tmp; }

    /* Operations: In-Place - clear */
    constexpr void clear()                                                                        { buffer.clear(); terminate(); }

    /* Operations: Out-of-Place - copyTo */
    constexpr void copyTo( char* outputString, std::size_t maxBufferLength )                const;
    constexpr void copyTo( uint8_t* outputString, std::size_t maxBufferLength )             const { copyTo( reinterpret_cast<char*>(outputString), maxBufferLength ); }

    template<std::size_t S>
    constexpr void copyTo( char (&outputString)[S] )                                        const { copyTo( outputString, S ); }
    template<std::size_t S>
    constexpr void copyTo( uint8_t (&outputString)[S] )                                     const { copyTo( reinterpret_cast<char(&)[S]>(outputString) ); }

    /* Operations: Out-of-Place - find and rfind */
    constexpr Iterator find( char value )                                                   const { return find( begin(), value ); };
    constexpr Iterator find( const char* value )                                            const { return find( begin(), value, std::strlen( value ) ); }
    constexpr Iterator find( const char* value, std::size_t n )                             const { return find( begin(), value, n ); }
    template<std::size_t S>
    constexpr Iterator find( const String<S>& value )                                       const { return find( begin(), value.asCString(), value.length() ); }

    constexpr Iterator find( ConstIterator pos, char value )                                const;
    constexpr Iterator find( ConstIterator pos, const char* value )                         const { return find( pos, value, std::strlen( value ) ); }
    constexpr Iterator find( ConstIterator pos, const char* value, std::size_t n )          const;
    template<std::size_t S>
    constexpr Iterator find( ConstIterator pos, const String<S>& value )                    const { return find( pos, value.asCString(), value.length() ); }

    constexpr ReverseIterator rfind( char value )                                           const { return rfind( rbegin(), value ); }
    constexpr ReverseIterator rfind( const char* value )                                    const { return rfind( rbegin(), value ); }
    constexpr ReverseIterator rfind( const char* value, std::size_t n )                     const { return rfind( rbegin(), value, n ); }
    template<std::size_t S>
    constexpr ReverseIterator rfind( const String<S>& value )                               const { return rfind( rbegin(), value.asCString(), value.length() ); }

    constexpr ReverseIterator rfind( ConstReverseIterator pos, char value )                 const;
    constexpr ReverseIterator rfind( ConstReverseIterator pos, const char* value )          const;
    constexpr ReverseIterator rfind( ConstReverseIterator pos, const char* value, std::size_t n )  const;
    template<std::size_t S>
    constexpr ReverseIterator rfind( ConstReverseIterator pos, const String<S>& value )     const { return rfind( pos, value.asCString(), value.length() ); }

    /* Operations: Out-of-Place - contains */
    constexpr bool contains( char value )                                                   const { return find( begin(), value ) != end(); }
    constexpr bool contains( const char* value )                                            const { return find( begin(), value ) != end(); }
    constexpr bool contains( const char* value, std::size_t n )                             const { return find( begin(), value ) != end(); }
    template<std::size_t S>
    constexpr bool contains( const String<S>& value )                                       const { return find( begin(), value ) != end(); }

    /* Operations: Out-of-Place - equals */
    constexpr bool equals( char value )                                                     const { return contains( &value, 1 ); }
    constexpr bool equals( const char* value )                                              const { return equals( value, std::strlen( value ) ); }
    constexpr bool equals( const char* value, std::size_t n )                               const;
    template<std::size_t S>
    constexpr bool equals( const String<S>& value )                                         const { return equals( value.asCString(), value.length() ); }

    /* Operations: In/Out-of-Place - strip */
    constexpr String& strip( char value = '\0' );
    constexpr String& strip( const char* values );
    constexpr String& strip( const char* values, std::size_t n );
    template<std::size_t S>
    constexpr String& strip( const String<S>& values )                                            { return strip( values.asCString(), values.length() ); }

    constexpr String getStripped( char value = '\0' )                                       const { String tmp(*this); tmp.strip( value ); return tmp; }
    constexpr String getStripped( const char* values )                                      const { String tmp(*this); tmp.strip( values ); return tmp; }
    constexpr String getStripped( const char* values, std::size_t n )                       const { String tmp(*this); tmp.strip( values, n ); return tmp; }
    template<std::size_t S>
    constexpr String getStripped( const String<S>& values )                                 const { String tmp(*this); tmp.strip( values ); return tmp; }


    /* Operations: In/Out-of-Place - trim */
    constexpr String& trim( char value = '\0' )                                                   { return trimRight( value ).trimLeft( value ); }
    constexpr String& trim( const char* values )                                                  { return trimRight( values ).trimLeft( values ); }
    constexpr String& trim( const char* values, std::size_t n )                                   { return trimRight( values, n ).trimLeft( values, n ); }

    constexpr String getTrimmed( char value = '\0' )                                        const { String tmp(*this); tmp.trim( value ); return tmp; }
    constexpr String getTrimmed( const char* values )                                       const { String tmp(*this); tmp.trim( values ); return tmp; }
    constexpr String getTrimmed( const char* values, std::size_t n )                        const { String tmp(*this); tmp.trim( values, n ); return tmp; }

    /* Operations: In/Out-of-Place - trimLeft */
    constexpr String& trimLeft( char value = '\0' );
    constexpr String& trimLeft( const char* values );
    constexpr String& trimLeft( const char* values, std::size_t n );

    constexpr String getTrimmedLeft( char value = '\0' )                                    const { String tmp(*this); tmp.trimLeft( value ); return tmp; }
    constexpr String getTrimmedLeft( const char* values )                                   const { String tmp(*this); tmp.trimLeft( values ); return tmp; }
    constexpr String getTrimmedLeft( const char* values, std::size_t n )                    const { String tmp(*this); tmp.trimLeft( values, n ); return tmp; }

    /* Operations: In/Out-of-Place - trimRight */
    constexpr String& trimRight( char value = '\0' );
    constexpr String& trimRight( const char* values );
    constexpr String& trimRight( const char* values, std::size_t n );

    constexpr String getTrimmedRight( char value = '\0' )                                   const { String tmp(*this); tmp.trimRight( value ); return tmp; }
    constexpr String getTrimmedRight( const char* values )                                  const { String tmp(*this); tmp.trimRight( values ); return tmp; }
    constexpr String getTrimmedRight( const char* values, std::size_t n )                   const { String tmp(*this); tmp.trimRight( values, n ); return tmp; }

    /* Operations: In/Out-of-Place - reverse */
    constexpr String& reverse();
    constexpr String getReversed()                                                          const { String tmp(*this); tmp.reverse(); return tmp; }

    /* Operations: In/Out-of-Place - toLower */
    constexpr String& toLower();
    constexpr String getToLower()                                                           const { String tmp(*this); tmp.toLower(); return tmp; }

    /* Operations: In/Out-of-Place - toUpper */
    constexpr String& toUpper();
    constexpr String getToUpper()                                                           const { String tmp(*this); tmp.toUpper(); return tmp; }

    /* Operations: In/Out-of-Place - replace */
    constexpr String& replace( char lookFor, char replaceWith )                                   { return replace( &lookFor, 1_uz, &replaceWith, 1_uz ); }
    constexpr String& replace( const char* lookFor, char replaceWith )                            { return replace( lookFor, std::strlen(lookFor), &replaceWith, 1_uz ); }
    constexpr String& replace( const char* lookFor, std::size_t nLF, char replaceWith )           { return replace( lookFor, nLF, &replaceWith, 1_uz ); }
    template<std::size_t S>
    constexpr String& replace( const String<S>& lookFor, char replaceWith )                       { return replace( lookFor.asCString(), lookFor.length(), &replaceWith, 1_uz ); }

    constexpr String& replace( char lookFor, const char* replaceWith )                            { return replace( &lookFor, 1_uz, replaceWith, std::strlen(replaceWith) ); }
    constexpr String& replace( const char* lookFor, const char* replaceWith )                     { return replace( lookFor, std::strlen(lookFor), replaceWith, std::strlen(replaceWith) ); }
    constexpr String& replace( const char* lookFor, std::size_t nLF, const char* replaceWith )    { return replace( lookFor, nLF, replaceWith, std::strlen(replaceWith) ); }
    template<std::size_t S>
    constexpr String& replace( const String<S>& lookFor, const char* replaceWith )                { return replace( lookFor.asCString(), lookFor.length(), replaceWith, std::strlen(replaceWith) ); }

    constexpr String& replace( char lookFor, const char* replaceWith, std::size_t nRW )           { return replace( &lookFor, 1_uz, replaceWith, nRW ); }
    constexpr String& replace( const char* lookFor, const char* replaceWith, std::size_t nRW )    { return replace( lookFor, std::strlen(lookFor), replaceWith, nRW ); }
    constexpr String& replace(
        const char* lookFor, std::size_t nLF,
        const char* replaceWith, std::size_t nRW
    );
    template<std::size_t S>
    constexpr String& replace( const String<S>& lookFor, char replaceWith, std::size_t nRW )      { return replace( lookFor.asCString(), lookFor.length(), replaceWith, nRW ); }

    template<std::size_t S>
    constexpr String& replace( char lookFor, const String<S>& replaceWith )                       { return replace( &lookFor, 1_uz, replaceWith.asCString(), replaceWith.length() ); }
    template<std::size_t S>
    constexpr String& replace( const char* lookFor, const String<S>& replaceWith )                { return replace( lookFor, std::strlen(lookFor), replaceWith.asCString(), replaceWith.length() ); }
    template<std::size_t S>
    constexpr String& replace(
        const char* lookFor, std::size_t nLF,
        const String<S>& replaceWith
    )                                                                                             { return replace( lookFor, nLF, replaceWith.asCString(), replaceWith.length() ); }
    template<std::size_t S1, std::size_t S2>
    constexpr String& replace( const String<S1>& lookFor, const String<S2>& replaceWith )         { return replace( lookFor.asCString(), lookFor.length(), replaceWith.asCString(), replaceWith.length() ); }

    constexpr String getReplaced( char lookFor, char replaceWith )                          const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }
    constexpr String getReplaced( const char* lookFor, char replaceWith )                   const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }
    constexpr String getReplaced( const char* lookFor, std::size_t nLF, char replaceWith )  const { String tmp(*this); tmp.replace( lookFor, nLF, replaceWith ); return tmp; }
    template<std::size_t S>
    constexpr String& getReplaced( const String<S>& lookFor, char replaceWith )             const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }

    constexpr String getReplaced( char lookFor, const char* replaceWith )                   const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }
    constexpr String getReplaced( const char* lookFor, const char* replaceWith )            const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }
    constexpr String getReplaced( const char* lookFor, std::size_t nLF, const char* replaceWith )const { String tmp(*this); tmp.replace( lookFor, nLF, replaceWith ); return tmp; }
    template<std::size_t S>
    constexpr String& getReplaced( const String<S>& lookFor, const char* replaceWith )      const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }

    constexpr String getReplaced( char lookFor, const char* replaceWith, std::size_t nRW )  const { String tmp(*this); tmp.replace( lookFor, replaceWith, nRW ); return tmp; }
    constexpr String getReplaced( const char* lookFor, const char* replaceWith, std::size_t nRW )const { String tmp(*this); tmp.replace( lookFor, replaceWith, nRW ); return tmp; }
    constexpr String getReplaced(
        const char* lookFor, std::size_t nLF,
        const char* replaceWith, std::size_t nRW
    )                                                                                       const { String tmp(*this); tmp.replace( lookFor, nLF, replaceWith, nRW ); return tmp; }
    template<std::size_t S1, std::size_t S2>
    constexpr String& getReplaced( const String<S1>& lookFor, const String<S2>& replaceWith )const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }

    /* Operations: In/Out-of-Place - subString */
    constexpr String& subString( ConstIterator start, ConstIterator end );
    constexpr String getSubString( ConstIterator start, ConstIterator end )                 const { String tmp; tmp.append( start, end - start ); return tmp; }

    /* Operations: Operator Overload - += */
    constexpr String& operator+=( const char* rhs )                                               { return append( rhs ); }
    constexpr String& operator+=( const uint8_t* rhs )                                            { return append( rhs ); }

    template<std::size_t S>
    constexpr String& operator+=( const char (&rhs)[S] )                                          { return append( rhs ); }
    template<std::size_t S>
    constexpr String& operator+=( const uint8_t (&rhs)[S] )                                       { return append( rhs ); }

    constexpr String& operator+=( char rhs )                                                      { return append( rhs ); }

    constexpr String& operator+=( int8_t rhs )                                                    { return append( rhs ); }
    constexpr String& operator+=( int16_t rhs )                                                   { return append( rhs ); }
    constexpr String& operator+=( int32_t rhs )                                                   { return append( rhs ); }
    constexpr String& operator+=( int64_t rhs )                                                   { return append( rhs ); }
    constexpr String& operator+=( uint8_t rhs )                                                   { return append( rhs ); }
    constexpr String& operator+=( uint16_t rhs )                                                  { return append( rhs ); }
    constexpr String& operator+=( uint32_t rhs )                                                  { return append( rhs ); }
    constexpr String& operator+=( uint64_t rhs )                                                  { return append( rhs ); }

    template<std::size_t S>
    constexpr String& operator+=( const String<S>& rhs )                                          { return append( rhs ); }

    /* Operations: Operator Overload - +(this, rhs) */
    constexpr String operator+( const char* rhs )                                           const { return getAppended( rhs ); }
    constexpr String operator+( const uint8_t* rhs )                                        const { return getAppended( rhs ); }

    template<std::size_t S>
    constexpr String operator+( const char (&rhs)[S] )                                      const { return getAppended( rhs ); }
    template<std::size_t S>
    constexpr String operator+( const uint8_t (&rhs)[S] )                                   const { return getAppended( rhs ); }

    constexpr String operator+( char rhs )                                                  const { return getAppended( rhs ); }

    constexpr String operator+( const int8_t& rhs )                                         const { return getAppended( rhs ); }
    constexpr String operator+( const int16_t& rhs )                                        const { return getAppended( rhs ); }
    constexpr String operator+( const int32_t& rhs )                                        const { return getAppended( rhs ); }
    constexpr String operator+( const int64_t& rhs )                                        const { return getAppended( rhs ); }
    constexpr String operator+( const uint8_t& rhs )                                        const { return getAppended( rhs ); }
    constexpr String operator+( const uint16_t& rhs )                                       const { return getAppended( rhs ); }
    constexpr String operator+( const uint32_t& rhs )                                       const { return getAppended( rhs ); }
    constexpr String operator+( const uint64_t& rhs )                                       const { return getAppended( rhs ); }

    /* Operations: Operator Overload - +(lhs, String) */
    friend constexpr String operator+( const char* lhs, const String& rhs )                       { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( const uint8_t* lhs, const String& rhs )                    { String result(lhs); result.append(rhs); return result; }

    template<std::size_t S>
    friend constexpr String operator+( const char (&lhs)[S], const String& rhs )                  { String result(lhs); result.append(rhs); return result; }
    template<std::size_t S>
    friend constexpr String operator+( const uint8_t (&lhs)[S], const String& rhs )               { String result(lhs); result.append(rhs); return result; }

    friend constexpr String operator+( char lhs, const String& rhs )                              { String result(lhs); result.append(rhs); return result; }

    friend constexpr String operator+( int8_t lhs, const String& rhs )                            { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( int16_t lhs, const String& rhs )                           { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( int32_t lhs, const String& rhs )                           { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( int64_t lhs, const String& rhs )                           { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint8_t lhs, const String& rhs )                           { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint16_t lhs, const String& rhs )                          { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint32_t lhs, const String& rhs )                          { String result(lhs); result.append(rhs); return result; }
    friend constexpr String operator+( uint64_t lhs, const String& rhs )                          { String result(lhs); result.append(rhs); return result; }

    template<std::size_t S>
    friend constexpr auto operator+( const String<S>& lhs, const String& rhs )                    { String<EDF::max(N, S)> result(lhs); result.append(rhs); return result; }

    /* Iterators */
    constexpr Iterator begin()                                                                    { return buffer.begin(); }
    constexpr ConstIterator begin()                                                         const { return buffer.begin(); }
    constexpr ConstIterator cbegin()                                                        const { return buffer.cbegin(); }

    constexpr Iterator end()                                                                      { return buffer.end(); }
    constexpr ConstIterator end()                                                           const { return buffer.end(); }
    constexpr ConstIterator cend()                                                          const { return buffer.cend(); }

    constexpr ReverseIterator rbegin()                                                            { return buffer.rbegin(); }
    constexpr ConstReverseIterator rbegin()                                                 const { return buffer.rbegin(); }
    constexpr ConstReverseIterator crbegin()                                                const { return buffer.crbegin(); }

    constexpr ReverseIterator rend()                                                              { return buffer.rend(); }
    constexpr ConstReverseIterator rend()                                                   const { return buffer.rend(); }
    constexpr ConstReverseIterator crend()                                                  const { return buffer.crend(); }
};

} /* EDF */

#include "EDF/src/String.tpp"