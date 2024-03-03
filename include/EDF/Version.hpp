/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/String.hpp"

namespace EDF {

/*
 * Semantic version in the format MAJOR.MINOR.PATCH
 * https://semver.org/#semantic-versioning-200
 *
 * Supports up to 3 digits per element
 * Does not support appended pre-release    https://semver.org/#spec-item-9
 * Does not support appended build metadata https://semver.org/#spec-item-10
 */
class Version final{
private:
    static constexpr std::size_t DOTS = 2;      // two '.' characters
    static constexpr std::size_t DIGITS = 3;    // number of digits per element
    static_assert( DIGITS <= 3, "A uint32_t for number can only easily support versions from 999.999.999" );
    static constexpr std::size_t MULT = [](){
        std::size_t multiplier = 1;
        for( std::size_t k = 0; k < DIGITS; ++k ) {
            multiplier *= 10;
        }
        return multiplier;
    }();
public:
    using String = String<DOTS+(3*DIGITS)+1>;   // (3*DIGITS) for 3 elements, plus 1 null
private:
    uint32_t number;    // number representation for easy comparison
    String string;      // string representation for easy output
public:
    constexpr Version() : number(0), string( "0.0.0" ) {}
    constexpr Version( const char* str ) : number( fromString( str ) ), string( str ) {}
    constexpr Version( const uint32_t& value ) : number( value ), string( fromNumber() ) {}

    template<std::size_t N>
    constexpr Version( const char (&str)[N] ) : number( fromString( str ) ), string( str ) {}

    template<std::size_t N>
    constexpr Version( const EDF::String<N>& str ) : number( fromString( str ) ), string( str )  {}

    ~Version() = default;

    /* Access */
    constexpr uint32_t getMajor()                   const { return number / (MULT*MULT); }
    constexpr uint32_t getMinor()                   const { return (number / MULT) % MULT; }
    constexpr uint32_t getPatch()                   const { return number % MULT; }
    constexpr const uint32_t& asNumber()            const { return number; }
    constexpr const String& asString()              const { return string; }
    constexpr const char* asCString()               const { return string.asCString(); }

    /* EDF Version */
    static constexpr Version EDF()                        { return "0.1.0"; }

    /* Comparison Operators - (this, rhs) */
    constexpr bool operator> ( const Version& rhs ) const { return number > rhs.number; };
    constexpr bool operator< ( const Version& rhs ) const { return number < rhs.number; };
    constexpr bool operator>=( const Version& rhs ) const { return number >= rhs.number; };
    constexpr bool operator<=( const Version& rhs ) const { return number <= rhs.number; };
    constexpr bool operator==( const Version& rhs ) const { return number == rhs.number; };
    constexpr bool operator!=( const Version& rhs ) const { return number != rhs.number; };

    constexpr bool operator> ( const char* rhs )    const { return operator> ( Version( rhs ) ); };
    constexpr bool operator< ( const char* rhs )    const { return operator< ( Version( rhs ) ); };
    constexpr bool operator>=( const char* rhs )    const { return operator>=( Version( rhs ) ); };
    constexpr bool operator<=( const char* rhs )    const { return operator<=( Version( rhs ) ); };
    constexpr bool operator==( const char* rhs )    const { return operator==( Version( rhs ) ); };
    constexpr bool operator!=( const char* rhs )    const { return operator!=( Version( rhs ) ); };

    /* Comparison Operators - (lhs, this) */
    friend constexpr bool operator> ( const char* lhs, const Version& rhs ) { return Version( lhs ) > rhs; }
    friend constexpr bool operator< ( const char* lhs, const Version& rhs ) { return Version( lhs ) < rhs; }
    friend constexpr bool operator>=( const char* lhs, const Version& rhs ) { return Version( lhs ) >= rhs; }
    friend constexpr bool operator<=( const char* lhs, const Version& rhs ) { return Version( lhs ) <= rhs; }
    friend constexpr bool operator==( const char* lhs, const Version& rhs ) { return Version( lhs ) == rhs; }
    friend constexpr bool operator!=( const char* lhs, const Version& rhs ) { return Version( lhs ) != rhs; }
private:
    constexpr uint32_t fromString( const String& str ) {
        // this is used to initialize number
        // this->string is not initialized yet as it declared AFTER 'number' in the class definition
        auto firstDot = str.find( '.' );
        auto secondDot = str.rfind( '.' ).base() - 1; // -1 since it was a reverse iterator
        EDF_ASSERTD( (*str.begin()     != '0') || (firstDot  -  str.begin()    == 1) ); // MUST NOT contain leading zeros https://semver.org/#spec-item-2
        EDF_ASSERTD( (*(firstDot + 1)  != '0') || (secondDot - (firstDot + 1)  == 1) ); // MUST NOT contain leading zeros https://semver.org/#spec-item-2
        EDF_ASSERTD( (*(secondDot + 1) != '0') || (str.end() - (secondDot + 1) == 1) ); // MUST NOT contain leading zeros https://semver.org/#spec-item-2
        EDF_ASSERTD( !str.contains( '-' ) );                                            // MUST NOT contain negative numbers https://semver.org/#spec-item-2
        const uint32_t major = str.getSubString( str.begin(), firstDot ).toUint32_t();
        EDF_ASSERTD( major < MULT ); // major must be less than multiplier
        const uint32_t minor = str.getSubString( firstDot + 1, secondDot ).toUint32_t();
        EDF_ASSERTD( minor < MULT ); // minor must be less than multiplier
        const uint32_t patch = str.getSubString( secondDot + 1, str.end() ).toUint32_t();
        EDF_ASSERTD( patch < MULT ); // patch must be less than multiplier
        return (major * (MULT*MULT)) + (minor * MULT) + patch;
    }
    constexpr String fromNumber() {
        // number is initialized as it is declared BEFORE 'string' in the class definition
        EDF_ASSERTD( getMajor() < MULT ); // major must be less than multiplier
        EDF_ASSERTD( getMinor() < MULT ); // minor must be less than multiplier
        EDF_ASSERTD( getPatch() < MULT ); // patch must be less than multiplier
        return String( getMajor() ).append( '.' ).append( getMinor() ).append( '.' ).append( getPatch() );
    }
};

} /* EDF */