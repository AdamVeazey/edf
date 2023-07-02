/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Vector.hpp"

namespace EDF {

template<std::size_t N>
class String {
private:
    Vector<char, N> buffer;
private:
    inline constexpr void terminate() { *buffer.end() = '\0'; }
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
    
    constexpr String( const char& ch );
    
    constexpr String( const int8_t& value, std::size_t base = 10 );
    constexpr String( const int16_t& value, std::size_t base = 10 );
    constexpr String( const int32_t& value, std::size_t base = 10 );
    constexpr String( const int64_t& value, std::size_t base = 10 );
    constexpr String( const uint8_t& value, std::size_t base = 10 );
    constexpr String( const uint16_t& value, std::size_t base = 10 );
    constexpr String( const uint32_t& value, std::size_t base = 10 );
    constexpr String( const uint64_t& value, std::size_t base = 10 );

    template<std::size_t S>
    constexpr String( const String<S>& o );
    
    ~String() = default;

    using Iterator = typename Vector<char, N>::Iterator;
    using ConstIterator = typename Vector<char, N>::ConstIterator;
    using ReverseIterator = typename Vector<char, N>::ReverseIterator;
    using ConstReverseIterator = typename Vector<char, N>::ConstReverseIterator;

    /* Is Questions */
    inline constexpr bool isEmpty()                                                         const { return buffer.isEmpty(); }
    inline constexpr bool isFull()                                                          const { return buffer.length() == (N-1); }

    /* Capacity */
    inline constexpr const std::size_t& length()                                            const { return buffer.length(); }
    inline constexpr std::size_t maxLength()                                                const { return buffer.maxLength()-1; }

    /* Element access */
    inline constexpr char& at( std::size_t index )                                                { return buffer.at( index ); }
    inline constexpr const char& at( std::size_t index )                                    const { return buffer.at( index ); }

    inline constexpr char& operator[]( std::size_t index )                                        { return buffer[index]; }
    inline constexpr const char& operator[]( std::size_t index )                            const { return buffer[index]; }

    inline constexpr char* asCString()                                                            { return buffer.data(); }
    inline constexpr const char* asCString()                                                const { return buffer.data(); }
    inline constexpr uint8_t* asByteData()                                                        { return static_cast<uint8_t*>(buffer.data()); }
    inline constexpr const uint8_t* asByteData()                                            const { return static_cast<const uint8_t*>(buffer.data()); }

    /* Conversions: toX */    
    inline constexpr int8_t toInt8_t( int base = 10 )                                       const { return toInt32_t( base ); }
    inline constexpr int16_t toInt16_t( int base = 10 )                                     const { return toInt32_t( base ); }
    inline constexpr int32_t toInt32_t( int base = 10 )                                     const;
    inline constexpr int64_t toInt64_t( int base = 10 )                                     const;
    inline constexpr uint8_t toUint8_t( int base = 10 )                                     const { return toUint32_t( base ); }
    inline constexpr uint16_t toUint16_t( int base = 10 )                                   const { return toUint32_t( base ); }
    inline constexpr uint32_t toUint32_t( int base = 10 )                                   const;
    inline constexpr uint64_t toUint64_t( int base = 10 )                                   const;

    /* Operations: In/Out-of-Place - append */
    inline constexpr String& append( const char* str )                                            { insert( end(), str ); return *this; }
    inline constexpr String& append( const uint8_t* str )                                         { insert( end(), str ); return *this; }
    
    inline constexpr String& append( const char* str, std::size_t n )                             { insert( end(), str, n ); return *this; }
    inline constexpr String& append( const uint8_t* str, std::size_t n )                          { insert( end(), str, n ); return *this; }
    
    template<std::size_t S>
    inline constexpr String& append( const char (&str)[S] )                                       { insert( end(), str ); return *this; }
    template<std::size_t S>
    inline constexpr String& append( const uint8_t (&str)[S] )                                    { insert( end(), str ); return *this; }
    
    inline constexpr String& append( const char& ch )                                             { insert( end(), ch ); return *this; }
    inline constexpr String& append( char&& ch )                                                  { insert( end(), ch ); return *this; }
    
    inline constexpr String& append( const int8_t& value, std::size_t base = 10 )                 { insert( end(), value, base ); return *this; }
    inline constexpr String& append( const int16_t& value, std::size_t base = 10 )                { insert( end(), value, base ); return *this; }
    inline constexpr String& append( const int32_t& value, std::size_t base = 10 )                { insert( end(), value, base ); return *this; }
    inline constexpr String& append( const int64_t& value, std::size_t base = 10 )                { insert( end(), value, base ); return *this; }
    inline constexpr String& append( const uint8_t& value, std::size_t base = 10 )                { insert( end(), value, base ); return *this; }
    inline constexpr String& append( const uint16_t& value, std::size_t base = 10 )               { insert( end(), value, base ); return *this; }
    inline constexpr String& append( const uint32_t& value, std::size_t base = 10 )               { insert( end(), value, base ); return *this; }
    inline constexpr String& append( const uint64_t& value, std::size_t base = 10 )               { insert( end(), value, base ); return *this; }
    
    template<std::size_t S>
    inline constexpr String& append( const String<S>& str )                                       { insert( end(), str ); return *this; }

    inline constexpr String getAppended( const char* str )                                  const { String tmp(*this); tmp.append( str ); return tmp; }
    inline constexpr String getAppended( const uint8_t* str )                               const { String tmp(*this); tmp.append( str ); return tmp; }
    
    inline constexpr String getAppended( const char* str, std::size_t n )                   const { String tmp(*this); tmp.append( str, n ); return tmp; }
    inline constexpr String getAppended( const uint8_t* str, std::size_t n )                const { String tmp(*this); tmp.append( str, n ); return tmp; }
    
    template<std::size_t S>
    inline constexpr String getAppended( const char (&str)[S] )                             const { String tmp(*this); tmp.append( str ); return tmp; }
    template<std::size_t S>
    inline constexpr String getAppended( const uint8_t (&str)[S] )                          const { String tmp(*this); tmp.append( str ); return tmp; }
    
    inline constexpr String getAppended( const char& ch )                                   const { String tmp(*this); tmp.append( ch ); return tmp; }
    inline constexpr String getAppended( char&& ch )                                        const { String tmp(*this); tmp.append( ch ); return tmp; }
    
    inline constexpr String getAppended( const int8_t& value, std::size_t base = 10 )       const { String tmp(*this); tmp.append( value, base ); return tmp; }
    inline constexpr String getAppended( const int16_t& value, std::size_t base = 10 )      const { String tmp(*this); tmp.append( value, base ); return tmp; }
    inline constexpr String getAppended( const int32_t& value, std::size_t base = 10 )      const { String tmp(*this); tmp.append( value, base ); return tmp; }
    inline constexpr String getAppended( const int64_t& value, std::size_t base = 10 )      const { String tmp(*this); tmp.append( value, base ); return tmp; }
    inline constexpr String getAppended( const uint8_t& value, std::size_t base = 10 )      const { String tmp(*this); tmp.append( value, base ); return tmp; }
    inline constexpr String getAppended( const uint16_t& value, std::size_t base = 10 )     const { String tmp(*this); tmp.append( value, base ); return tmp; }
    inline constexpr String getAppended( const uint32_t& value, std::size_t base = 10 )     const { String tmp(*this); tmp.append( value, base ); return tmp; }
    inline constexpr String getAppended( const uint64_t& value, std::size_t base = 10 )     const { String tmp(*this); tmp.append( value, base ); return tmp; }
    
    template<std::size_t S>
    inline constexpr String getAppended( const String<S>& str )                             const { String tmp(*this); tmp.append( str ); return tmp; }

    /* Operations: In/Out-of-Place - insert */
    inline constexpr void insert( std::size_t index, const char& value )                          { insert( cbegin() + index, value ); }
    inline constexpr void insert( std::size_t index, char&& value )                               { insert( cbegin() + index, value ); }
    inline constexpr void insert( std::size_t index, std::size_t count, const char& value )       { insert( cbegin() + index, count, value ); }
    inline constexpr void insert( std::size_t index, std::initializer_list<char> iList )          { insert( cbegin() + index, iList ); }
    inline constexpr Iterator insert( ConstIterator pos, const char& value )                      { return insert( pos, 1, value ); }
    constexpr Iterator insert( ConstIterator pos, char&& value );
    constexpr Iterator insert( ConstIterator pos, std::size_t count, const char& value );
    constexpr Iterator insert( ConstIterator pos, std::initializer_list<char> iList );    

    inline constexpr void insert( std::size_t index, const char* str )                            { insert( cbegin() + index, str ); }
    inline constexpr void insert( std::size_t index, const uint8_t* str )                         { insert( cbegin() + index, str ); }
    inline constexpr Iterator insert( ConstIterator pos, const uint8_t* str )                     { return insert( pos, reinterpret_cast<const char*>(str) ); }
    inline constexpr Iterator insert( ConstIterator pos, const char* str );
    
    inline constexpr void insert( std::size_t index, const char* str, std::size_t n )             { insert( cbegin() + index, str, n ); }
    inline constexpr void insert( std::size_t index, const uint8_t* str, std::size_t n )          { insert( cbegin() + index, str, n ); }
    inline constexpr Iterator insert( ConstIterator pos, const uint8_t* str, std::size_t n )      { return insert( pos, reinterpret_cast<const char*>(str), n ); }
    constexpr Iterator insert( ConstIterator pos, const char* str, std::size_t n );

    template<std::size_t S>
    inline constexpr void insert( std::size_t index, const char (&str)[S] )                       { insert( cbegin() + index, str ); }
    template<std::size_t S>
    inline constexpr void insert( std::size_t index, const uint8_t (&str)[S] )                    { insert( cbegin() + index, str ); }
    template<std::size_t S>
    inline constexpr Iterator insert( ConstIterator pos, const uint8_t (&str)[S] )                { return insert( pos, reinterpret_cast<const char (&)[S]>(str) ); }
    template<std::size_t S>
    inline constexpr Iterator insert( ConstIterator pos, const char (&str)[S] )                   { return insert( pos, str, S ); }

    inline constexpr void insert( std::size_t index, const int8_t& value, std::size_t base = 10 ) { insert( cbegin() + index, value, base ); }
    inline constexpr void insert( std::size_t index, const int16_t& value, std::size_t base = 10 ){ insert( cbegin() + index, value, base ); }
    inline constexpr void insert( std::size_t index, const int32_t& value, std::size_t base = 10 ){ insert( cbegin() + index, value, base ); }
    inline constexpr void insert( std::size_t index, const int64_t& value, std::size_t base = 10 ){ insert( cbegin() + index, value, base ); }
    inline constexpr void insert( std::size_t index, const uint8_t& value, std::size_t base = 10 ){ insert( cbegin() + index, value, base ); }
    inline constexpr void insert( std::size_t index, const uint16_t& value, std::size_t base = 10 ){ insert( cbegin() + index, value, base ); }
    inline constexpr void insert( std::size_t index, const uint32_t& value, std::size_t base = 10 ){ insert( cbegin() + index, value, base ); }
    inline constexpr void insert( std::size_t index, const uint64_t& value, std::size_t base = 10 ){ insert( cbegin() + index, value, base ); }

    inline constexpr Iterator insert( ConstIterator pos, const int8_t& value, std::size_t base = 10 ){ return insert( pos, String<8+1>( value, base ) ); }
    inline constexpr Iterator insert( ConstIterator pos, const int16_t& value, std::size_t base = 10 ){ return insert( pos, String<16+1>( value, base ) ); }
    inline constexpr Iterator insert( ConstIterator pos, const int32_t& value, std::size_t base = 10 ){ return insert( pos, String<32+1>( value, base ) ); }
    inline constexpr Iterator insert( ConstIterator pos, const int64_t& value, std::size_t base = 10 ){ return insert( pos, String<64+1>( value, base ) ); }
    inline constexpr Iterator insert( ConstIterator pos, const uint8_t& value, std::size_t base = 10 ){ return insert( pos, String<8+1>( value, base ) ); }
    inline constexpr Iterator insert( ConstIterator pos, const uint16_t& value, std::size_t base = 10 ){ return insert( pos, String<16+1>( value, base ) ); }
    inline constexpr Iterator insert( ConstIterator pos, const uint32_t& value, std::size_t base = 10 ){ return insert( pos, String<32+1>( value, base ) ); }
    inline constexpr Iterator insert( ConstIterator pos, const uint64_t& value, std::size_t base = 10 ){ return insert( pos, String<64+1>( value, base ) ); }

    template<std::size_t S>
    inline constexpr void insert( std::size_t index, const String<S>& str )                       { insert( cbegin() + index, str ); }
    template<std::size_t S>
    inline constexpr Iterator insert( ConstIterator pos, const String<S>& str )                   { return insert( pos, str.asCString(), str.length() ); }

    inline constexpr String getInserted( std::size_t index, const char& value )             const { String tmp(*this); tmp.insert( index, value ); return tmp; }
    inline constexpr String getInserted( std::size_t index, char&& value )                  const { String tmp(*this); tmp.insert( index, value ); return tmp; }
    inline constexpr String getInserted( std::size_t index, std::size_t count, const char& value )const { String tmp(*this); tmp.insert( index, count, value ); return tmp; }
    inline constexpr String getInserted( std::size_t index, std::initializer_list<char> iList )const { String tmp(*this); tmp.insert( index, iList ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const char& value )             const { String tmp(*this); tmp.insert( pos, value ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, char&& value )                  const { String tmp(*this); tmp.insert( pos, value ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, std::size_t count, const char& value )const { String tmp(*this); tmp.insert( pos, value ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, std::initializer_list<char> iList )const { String tmp(*this); tmp.insert( pos, iList ); return tmp; }

    inline constexpr String getInserted( std::size_t index, const char* str )               const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const uint8_t* str )            const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const uint8_t* str )            const { String tmp(*this); tmp.insert( pos, str ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const char* str )               const { String tmp(*this); tmp.insert( pos, str ); return tmp; }
    
    inline constexpr String getInserted( std::size_t index, const char* str, std::size_t n )const { String tmp(*this); tmp.insert( index, str, n ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const uint8_t* str, std::size_t n )const { String tmp(*this); tmp.insert( index, str, n ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const uint8_t* str, std::size_t n )const { String tmp(*this); tmp.insert( pos, str, n ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const char* str, std::size_t n )const { String tmp(*this); tmp.insert( pos, str, n ); return tmp; }

    template<std::size_t S>
    inline constexpr String getInserted( std::size_t index, const char (&str)[S] )          const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    template<std::size_t S>
    inline constexpr String getInserted( std::size_t index, const uint8_t (&str)[S] )       const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    template<std::size_t S>
    inline constexpr String getInserted( ConstIterator pos, const uint8_t (&str)[S] )       const { String tmp(*this); tmp.insert( pos, str ); return tmp; }
    template<std::size_t S>
    inline constexpr String getInserted( ConstIterator pos, const char (&str)[S] )          const { String tmp(*this); tmp.insert( pos, str ); return tmp; }

    inline constexpr String getInserted( std::size_t index, const int8_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const int16_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const int32_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const int64_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const uint8_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const uint16_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const uint32_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }
    inline constexpr String getInserted( std::size_t index, const uint64_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( index, value, base ); return tmp; }

    inline constexpr String getInserted( ConstIterator pos, const int8_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const int16_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const int32_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const int64_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const uint8_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const uint16_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const uint32_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }
    inline constexpr String getInserted( ConstIterator pos, const uint64_t& value, std::size_t base = 10 )const { String tmp(*this); tmp.insert( pos, value, base ); return tmp; }

    template<std::size_t S>
    inline constexpr String getInserted( std::size_t index, const String<S>& str )          const { String tmp(*this); tmp.insert( index, str ); return tmp; }
    template<std::size_t S>
    inline constexpr String getInserted( ConstIterator pos, const String<S>& str )          const { String tmp(*this); tmp.insert( pos, str ); return tmp; }

    /* Operations: In/Out-of-Place - erase */
    inline constexpr void erase( std::size_t index )                                              { buffer.erase( index ); terminate(); }
    inline constexpr void erase( std::size_t first, std::size_t last )                            { buffer.erase( first, last ); terminate(); }
    inline constexpr Iterator erase( ConstIterator pos )                                          { auto it = buffer.erase( pos ); terminate(); return it; }
    inline constexpr Iterator erase( ConstIterator first, ConstIterator last )                    { auto it = buffer.erase( first, last ); terminate(); return it; }

    inline constexpr String getErased( std::size_t index )                                  const { String tmp(*this); tmp.erase( index ); return tmp; }
    inline constexpr String getErased( std::size_t first, std::size_t last )                const { String tmp(*this); tmp.erase( first, last ); return tmp; }
    inline constexpr String getErased( ConstIterator pos )                                  const { String tmp(*this); tmp.erase( pos ); return tmp; }
    inline constexpr String getErased( ConstIterator first, ConstIterator last )            const { String tmp(*this); tmp.erase( first, last ); return tmp; }

    /* Operations: In-Place - clear */
    inline constexpr void clear()                                                                 { buffer.clear(); terminate(); }

    /* Operations: Out-of-Place - copyTo */
    constexpr void copyTo( char* outputString, std::size_t n )                              const;    
    inline constexpr void copyTo( uint8_t* outputString, std::size_t n )                    const { copyTo( reinterpret_cast<char*>(outputString), n ); }

    template<std::size_t S>
    inline constexpr void copyTo( char (&outputString)[S] )                                 const { copyTo( outputString, S ); }
    template<std::size_t S>
    inline constexpr void copyTo( uint8_t (&outputString)[S] )                              const { copyTo( reinterpret_cast<char(&)[S]>(outputString) ); }

    /* Operations: Out-of-Place - find and rfind */
    constexpr Iterator find( ConstIterator pos, const char& value )                         const;
    constexpr Iterator find( ConstIterator pos, const char* value )                         const;
    constexpr Iterator find( ConstIterator pos, const char* value, std::size_t n )          const;
    template<std::size_t S>
    inline constexpr Iterator find( ConstIterator pos, const String<S>& value )             const { return find( pos, value, S ); }

    constexpr Iterator rfind( ConstReverseIterator pos, const char& value ) const;
    constexpr Iterator rfind( ConstReverseIterator pos, const char* value ) const;
    constexpr Iterator rfind( ConstReverseIterator pos, const char* value, std::size_t n )  const;
    template<std::size_t S>
    inline constexpr Iterator rfind( ConstReverseIterator pos, const String<S>& value )     const { return rfind( pos, value, S ); }

    /* Operations: Out-of-Place - contains */
    inline constexpr bool contains( const char& value )                                     const { return find( begin(), value ) != end(); }
    inline constexpr bool contains( const char* value )                                     const { return find( begin(), value ) != end(); }
    inline constexpr bool contains( const char* value, std::size_t n )                      const { return find( begin(), value ) != end(); }
    template<std::size_t S>
    inline constexpr bool contains( const String<S>& value )                                const { return find( begin(), value ) != end(); }

    /* Operations: Out-of-Place - equals */
    inline constexpr bool equals( const char& value )                                       const { return contains( &value, 1 ); }
    constexpr bool equals( const char* value )                                              const;
    constexpr bool equals( const char* value, std::size_t n )                               const;
    template<std::size_t S>
    inline constexpr bool equals( const String<S>& value )                                  const { return equals( value, value.length() ); }
    
    /* Operations: In/Out-of-Place - strip */
    constexpr String& strip( const char& value = '\0' );
    constexpr String& strip( const char* values );
    constexpr String& strip( const char* values, std::size_t n );
    template<std::size_t S>
    inline constexpr String& strip( const String<S>& values )                                     { return strip( values.asCString(), values.length() ); }

    inline constexpr String getStripped( const char& value = '\0' )                         const { String tmp(*this); tmp.strip( value ); return tmp; }
    inline constexpr String getStripped( const char* values )                               const { String tmp(*this); tmp.strip( values ); return tmp; }
    inline constexpr String getStripped( const char* values, std::size_t n )                const { String tmp(*this); tmp.strip( values, n ); return tmp; }
    template<std::size_t S>
    inline constexpr String getStripped( const String<S>& values )                          const { String tmp(*this); tmp.strip( values ); return tmp; }


    /* Operations: In/Out-of-Place - trim */
    inline constexpr String& trim( const char& value = '\0' )                                     { return trimRight( value ).trimLeft( value ); }
    inline constexpr String& trim( const char* values )                                           { return trimRight( values ).trimLeft( values ); }
    inline constexpr String& trim( const char* values, std::size_t n )                            { return trimRight( values, n ).trimLeft( values, n ); }
    constexpr String& trimLeft( const char& value = '\0' );
    constexpr String& trimLeft( const char* values );
    constexpr String& trimLeft( const char* values, std::size_t n );
    constexpr String& trimRight( const char& value = '\0' );
    constexpr String& trimRight( const char* values );
    constexpr String& trimRight( const char* values, std::size_t n );

    inline constexpr String getTrimmed( const char& value = '\0' )                          const { String tmp(*this); tmp.trim( value ); return tmp; }
    inline constexpr String getTrimmed( const char* values )                                const { String tmp(*this); tmp.trim( values ); return tmp; }
    inline constexpr String getTrimmed( const char* values, std::size_t n )                 const { String tmp(*this); tmp.trim( values, n ); return tmp; }
    inline constexpr String getTrimmedLeft( const char& value = '\0' )                      const { String tmp(*this); tmp.trimLeft( value ); return tmp; }
    inline constexpr String getTrimmedLeft( const char* values )                            const { String tmp(*this); tmp.trimLeft( values ); return tmp; }
    inline constexpr String getTrimmedLeft( const char* values, std::size_t n )             const { String tmp(*this); tmp.trimLeft( values, n ); return tmp; }
    inline constexpr String getTrimmedRight( const char& value = '\0' )                     const { String tmp(*this); tmp.trimRight( value ); return tmp; }
    inline constexpr String getTrimmedRight( const char* values )                           const { String tmp(*this); tmp.trimRight( values ); return tmp; }
    inline constexpr String getTrimmedRight( const char* values, std::size_t n )            const { String tmp(*this); tmp.trimRight( values, n ); return tmp; }


    /* Operations: In/Out-of-Place - reverse */
    constexpr String& reverse();
    inline constexpr String getReversed()                                                   const { String tmp(*this); tmp.reverse(); return tmp; }

    /* Operations: In/Out-of-Place - toLower */
    constexpr String& toLower();
    inline constexpr String getToLower()                                                    const { String tmp(*this); tmp.toLower(); return tmp; }

    /* Operations: In/Out-of-Place - toUpper */
    constexpr String& toUpper();
    inline constexpr String getToUpper()                                                    const { String tmp(*this); tmp.toUpper(); return tmp; }

    /* Operations: In/Out-of-Place - replace */
    constexpr String& replace( const char* lookFor, const char* replaceWith );
    constexpr String& replace( 
        const char* lookFor, std::size_t nLF, 
        const char* replaceWith, std::size_t nRW 
    );
    inline constexpr String getReplaced( const char* lookFor, const char* replaceWith )     const { String tmp(*this); tmp.replace( lookFor, replaceWith ); return tmp; }
    inline constexpr String getReplaced(
        const char* lookFor, std::size_t nLF, 
        const char* replaceWith, std::size_t nRW 
    )                                                                                       const { String tmp(*this); tmp.replace( lookFor, nLF, replaceWith, nRW ); return tmp; }

    /* Operations: In/Out-of-Place - subString */
    constexpr String& subString( ConstIterator start, ConstIterator end );
    constexpr String getSubString( ConstIterator start, ConstIterator end );

    /* Operations: Operator Overload - += */
    inline constexpr String& operator+=( const char* b )                                          { return append( b ); }
    inline constexpr String& operator+=( const uint8_t* b )                                       { return append( b ); }

    template<std::size_t S>
    inline constexpr String& operator+=( const char (&b)[S] )                                     { return append( b ); }
    template<std::size_t S>
    inline constexpr String& operator+=( const uint8_t (&b)[S] )                                  { return append( b ); }

    inline constexpr String& operator+=( const char& b )                                          { return append( b ); }
    inline constexpr String& operator+=( char&& b )                                               { return append( b ); }

    inline constexpr String& operator+=( const int8_t b )                                         { return append( b ); }
    inline constexpr String& operator+=( const int16_t b )                                        { return append( b ); }
    inline constexpr String& operator+=( const int32_t b )                                        { return append( b ); }
    inline constexpr String& operator+=( const int64_t b )                                        { return append( b ); }
    inline constexpr String& operator+=( const uint8_t b )                                        { return append( b ); }
    inline constexpr String& operator+=( const uint16_t b )                                       { return append( b ); }
    inline constexpr String& operator+=( const uint32_t b )                                       { return append( b ); }
    inline constexpr String& operator+=( const uint64_t b )                                       { return append( b ); }

    template<std::size_t S>
    inline constexpr String& operator+=( const String<S>& b )                                     { return append( b ); }

    /* Operations: Operator Overload - +(this, b) */
    inline constexpr String& operator+( const char* b )                                           { return append( b ); }
    inline constexpr String& operator+( const uint8_t* b )                                        { return append( b ); }

    template<std::size_t S>
    inline constexpr String& operator+( const char (&b)[S] )                                      { return append( b ); }
    template<std::size_t S>
    inline constexpr String& operator+( const uint8_t (&b)[S] )                                   { return append( b ); }

    inline constexpr String& operator+( const char& b )                                           { return append( b ); }
    inline constexpr String& operator+( char&& b )                                                { return append( b ); }

    inline constexpr String& operator+( const int8_t b )                                          { return append( b ); }
    inline constexpr String& operator+( const int16_t b )                                         { return append( b ); }
    inline constexpr String& operator+( const int32_t b )                                         { return append( b ); }
    inline constexpr String& operator+( const int64_t b )                                         { return append( b ); }
    inline constexpr String& operator+( const uint8_t b )                                         { return append( b ); }
    inline constexpr String& operator+( const uint16_t b )                                        { return append( b ); }
    inline constexpr String& operator+( const uint32_t b )                                        { return append( b ); }
    inline constexpr String& operator+( const uint64_t b )                                        { return append( b ); }

    template<std::size_t S>
    constexpr auto& operator+( String<S>&& b );

    /* Operations: Operator Overload - +(b, String) */
    friend inline constexpr String operator+( const char* b, const String& rhs )                  { String result(b); result.append(rhs); return result; }
    friend inline constexpr String operator+( const uint8_t* b, const String& rhs )               { String result(b); result.append(rhs); return result; }

    template<std::size_t S>
    friend inline constexpr String operator+( const char (&lhs)[S], const String& rhs )           { String result(lhs); result.append(rhs); return result; }
    template<std::size_t S>
    friend inline constexpr String operator+( const uint8_t (&lhs)[S], const String& rhs )        { String result(lhs); result.append(rhs); return result; }

    friend inline constexpr String operator+( const char& lhs, const String& rhs )                { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( char&& lhs, const String& rhs )                     { String result(lhs); result.append(rhs); return result; }
    
    friend inline constexpr String operator+( const int8_t lhs, const String& rhs )               { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( const int16_t lhs, const String& rhs )              { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( const int32_t lhs, const String& rhs )              { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( const int64_t lhs, const String& rhs )              { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( const uint8_t lhs, const String& rhs )              { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( const uint16_t lhs, const String& rhs )             { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( const uint32_t lhs, const String& rhs )             { String result(lhs); result.append(rhs); return result; }
    friend inline constexpr String operator+( const uint64_t lhs, const String& rhs )             { String result(lhs); result.append(rhs); return result; }

    template<std::size_t S>
    friend inline constexpr String operator+( const String<S>& lhs, const String& rhs )           { String result(lhs); result.append(rhs); return result; }

    /* Iterators */
    inline constexpr Iterator begin()                                                             { return buffer.begin(); }
    inline constexpr ConstIterator begin()                                                  const { return buffer.begin(); }
    inline constexpr ConstIterator cbegin()                                                 const { return buffer.cbegin(); }

    inline constexpr Iterator end()                                                               { return buffer.end(); }
    inline constexpr ConstIterator end()                                                    const { return buffer.end(); }
    inline constexpr ConstIterator cend()                                                   const { return buffer.cend(); }

    inline constexpr ReverseIterator rbegin()                                                     { return buffer.rbegin(); }
    inline constexpr ConstReverseIterator rbegin()                                          const { return buffer.rbegin(); }
    inline constexpr ConstReverseIterator crbegin()                                         const { return buffer.crbegin(); }

    inline constexpr ReverseIterator rend()                                                       { return buffer.rend(); }
    inline constexpr ConstReverseIterator rend()                                            const { return buffer.rend(); }
    inline constexpr ConstReverseIterator crend()                                           const { return buffer.crend(); }
};

} /* EDF */

#include "EDF/src/String.tpp"