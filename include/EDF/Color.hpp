/*
 * Copyright (c) 2023, Adam Veazey
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
    constexpr Color( uint32_t initialValue = 0 ) : rgba( initialValue ) {}
    constexpr Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF ) :
        rgba( (a << 24) | (r << 16) | (g << 8) | b )
    {}

    /* Set color components */
    constexpr void setR( uint8_t r )          { rgba.set( 16, 8, r ); }
    constexpr void setG( uint8_t g )          { rgba.set(  8, 8, g ); }
    constexpr void setB( uint8_t b )          { rgba.set(  0, 8, b ); }
    constexpr void setA( uint8_t a )          { rgba.set( 24, 8, a ); }

    /* Get color components */
    constexpr uint8_t r()               const { return rgba.get( 16, 8 ); }
    constexpr uint8_t g()               const { return rgba.get( 8 , 8 ); }
    constexpr uint8_t b()               const { return rgba.get(  0, 8 ); }
    constexpr uint8_t a()               const { return rgba.get( 24, 8 ); }

    constexpr uint32_t asRGBA()         const { return rgba.get( 0, 32 ); }
    constexpr uint32_t asRGB()          const { return rgba.get( 0, 24 ); }

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
    constexpr Color565( uint16_t initialValue = 0 ) : rgb( initialValue ) {}
    constexpr Color565( uint8_t r, uint8_t g, uint8_t b ) :
        rgb( ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3) )
    {}
    constexpr Color565( const Color& c ) :
        rgb( ((c.r() >> 3) << 11) | ((c.g() >> 2) << 5) | (c.b() >> 3) )
    {}

    /* Set color components */
    constexpr void setR( uint8_t r )          { rgb.set( 11, 5, r >> 3 ); }
    constexpr void setG( uint8_t g )          { rgb.set(  5, 6, g >> 2 ); }
    constexpr void setB( uint8_t b )          { rgb.set(  0, 5, b >> 3 ); }

    /* Get color components */
    constexpr uint8_t r()               const { return rgb.get( 11, 5 ) << 3; }
    constexpr uint8_t g()               const { return rgb.get(  5, 6 ) << 2; }
    constexpr uint8_t b()               const { return rgb.get(  0, 5 ) << 3; }

    constexpr uint16_t asRGB()          const { return rgb.get( 0, 16 ); }
};

} /* EDF */