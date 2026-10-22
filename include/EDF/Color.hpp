/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/BitField.hpp"

namespace EDF {

class Color {
private:
    BitField32 rgba;
public:
    constexpr Color( std::uint32_t initialValue = 0 ) : rgba( initialValue ) {}
    constexpr Color( std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 0xFF ) :
        rgba( static_cast<std::uint32_t>((a << 24) | (r << 16) | (g << 8) | b) )
    {}

    /* Set color components */
    constexpr void setR( std::uint8_t r )     { rgba.set( 16, 8, r ); }
    constexpr void setG( std::uint8_t g )     { rgba.set(  8, 8, g ); }
    constexpr void setB( std::uint8_t b )     { rgba.set(  0, 8, b ); }
    constexpr void setA( std::uint8_t a )     { rgba.set( 24, 8, a ); }

    /* Get color components */
    constexpr std::uint8_t r()          const { return static_cast<std::uint8_t>(rgba.get( 16, 8 )); }
    constexpr std::uint8_t g()          const { return static_cast<std::uint8_t>(rgba.get( 8 , 8 )); }
    constexpr std::uint8_t b()          const { return static_cast<std::uint8_t>(rgba.get(  0, 8 )); }
    constexpr std::uint8_t a()          const { return static_cast<std::uint8_t>(rgba.get( 24, 8 )); }

    constexpr std::uint32_t asRGBA()    const { return rgba.get( 0, 32 ); }
    constexpr std::uint32_t asRGB()     const { return rgba.get( 0, 24 ); }

    constexpr bool operator==( const Color& other ) const { return asRGBA() == other.asRGBA(); }
    constexpr bool operator!=( const Color& other ) const { return !(*this == other); }

    /* Named colors */

    // tag::named_colors[]
    static constexpr Color red()        { return Color( 255,   0,   0 ); }
    static constexpr Color orange()     { return Color( 255, 128,   0 ); }
    static constexpr Color yellow()     { return Color( 255, 255,   0 ); }
    static constexpr Color lime()       { return Color( 128, 255,   0 ); }
    static constexpr Color green()      { return Color(   0, 255,   0 ); }
    static constexpr Color springGreen(){ return Color(   0, 255, 128 ); }
    static constexpr Color cyan()       { return Color(   0, 255, 255 ); }
    static constexpr Color dodgerBlue() { return Color(   0, 128, 255 ); }
    static constexpr Color blue()       { return Color(   0,   0, 255 ); }
    static constexpr Color blueViolet() { return Color( 128,   0, 255 ); }
    static constexpr Color magenta()    { return Color( 255,   0, 255 ); }
    static constexpr Color deepPink()   { return Color( 255,   0, 128 ); }

    static constexpr Color black()	    { return Color(   0,   0,   0 ); }
    static constexpr Color dimGray()	{ return Color( 105, 105, 105 ); }
    static constexpr Color gray()	    { return Color( 128, 128, 128 ); }
    static constexpr Color darkGray()	{ return Color( 169, 169, 169 ); }
    static constexpr Color silver()	    { return Color( 192, 192, 192 ); }
    static constexpr Color lightGray()	{ return Color( 211, 211, 211 ); }
    static constexpr Color gainsboro()	{ return Color( 220, 220, 220 ); }
    static constexpr Color whiteSmoke()	{ return Color( 245, 245, 245 ); }
    static constexpr Color white()	    { return Color( 255, 255, 255 ); }
    // end::named_colors[]
};

class Color565 {
private:
    BitField16 rgb;
public:
    constexpr Color565( std::uint16_t raw565 = 0 ) : rgb( raw565 ) {}
    constexpr Color565( const Color& c ) :
        rgb( static_cast<std::uint16_t>(((c.r() >> 3) << 11) | ((c.g() >> 2) << 5) | (c.b() >> 3)) )
    {}

    /* Set color components */
    constexpr void setR( std::uint8_t r )     { EDF_ASSERTD( r < 32, "Expected value: [0-31]"); rgb.set( 11, 5, r ); }
    constexpr void setG( std::uint8_t g )     { EDF_ASSERTD( g < 64, "Expected value: [0-63]"); rgb.set(  5, 6, g ); }
    constexpr void setB( std::uint8_t b )     { EDF_ASSERTD( b < 32, "Expected value: [0-31]"); rgb.set(  0, 5, b ); }

    /* Get color components */
    constexpr std::uint8_t r()          const { return static_cast<std::uint8_t>(rgb.get( 11, 5 )); }
    constexpr std::uint8_t g()          const { return static_cast<std::uint8_t>(rgb.get(  5, 6 )); }
    constexpr std::uint8_t b()          const { return static_cast<std::uint8_t>(rgb.get(  0, 5 )); }

    constexpr std::uint16_t asRGB()     const { return rgb.get( 0, 16 ); }
    constexpr Color asColor()           const { return Color( (r() * 255) / 31, (g() * 255) / 63, (b() * 255) / 31 ); }

    constexpr bool operator==( const Color565& other ) const { return asRGB() == other.asRGB(); }
    constexpr bool operator!=( const Color565& other ) const { return !(*this == other); }
};

} /* EDF */