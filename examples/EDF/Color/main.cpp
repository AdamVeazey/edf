/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Color.hpp>

#include <iostream>


void example() {
    // tag::init_default[]
    EDF::Color black;
    // end::init_default[]

    // tag::init_initial_value[]
    EDF::Color salmon( 0xFA8072 );
    // end::init_initial_value[]

    // tag::init_rgba[]
    EDF::Color white( 255, 255, 255 );
    EDF::Color gray( 128, 128, 128, 255 );
    // end::init_rgba[]

    // tag::set_rgba[]
    black.setR( 255 );  // turn red
    black.setG( 255 );  // turn yellow
    black.setB( 255 );  // turn white
    black.setA( 0 );    // turn transparent
    // end::set_rgba[]

    // tag::get_rgba[]
    salmon.r(); // 0xFA
    salmon.g(); // 0x80
    salmon.b(); // 0x72
    salmon.a(); // 0xFF
    // end::get_rgba[]

    // tag::get_as[]
    white.asRGB();  // 0xFFFFFF
    gray.asRGBA();  // 0xFFFFFFFF
    // end::get_as[]

    // tag::named_colors[]
    EDF::Color::red();
    EDF::Color::springGreen();
    EDF::Color::cyan();
    // end::named_colors[]
}

// tag::example_565_1[]
void function( const EDF::Color565& color ) {
    uint16_t data = color.asRGB();
    /* ... */
    (void)data;
}
// end::example_565_1[]

void example565() {
    // tag::init_default_565[]
    EDF::Color565 black;
    // end::init_default_565[]

    // tag::init_initial_value_565[]
    EDF::Color565 salmon( 0xFC0E );
    // end::init_initial_value_565[]

    // tag::init_rgba_565[]
    EDF::Color565 white( 255, 255, 255 );
    // end::init_rgba_565[]

    // tag::init_color_565[]
    EDF::Color565 color( EDF::Color::blueViolet() );
    // end::init_color_565[]
    (void)color;
    // tag::set_rgba_565[]
    black.setR( 255 );  // turn red
    black.setG( 255 );  // turn yellow
    black.setB( 255 );  // turn white
    // end::set_rgba_565[]

    // tag::get_rgba_565[]
    salmon.r(); // 0xF8
    salmon.g(); // 0x80
    salmon.b(); // 0x70
    // end::get_rgba_565[]

    // tag::get_as_565[]
    white.asRGB();  // 0xFFFF
    // end::get_as_565[]

    // tag::example_565_2[]
    function( EDF::Color::magenta() );
    // end::example_565_2[]
}

int main( void ) {

    EDF::Color565 c( EDF::Color( 0xFA8072 ) );
    std::cout << std::hex;
    std::cout << "r: " << +c.r() << '\n'
              << "g: " << +c.g() << '\n'
              << "b: " << +c.b() << '\n';
    // std::cout << "a: " << +c.a() << '\n';
    // c.setG( 0 );
    uint32_t value = c.asRGB();
    std::cout << "0x" << value << std::endl;

    return 0;
}
