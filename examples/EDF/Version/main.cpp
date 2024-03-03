/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Version.hpp>

#include <iostream>

int main( void ) {
    // tag::init_default[]
    EDF::Version versionDefault;
    // end::init_default[]

    // tag::init[]
    EDF::Version version( "1.2.3" );
    // end::init[]

    // tag::init_value[]
    EDF::Version versionValue( 10203 );
    // end::init_value[]

    // tag::init_str_array[]
    const char array[] = "10.20.30";
    EDF::Version versionArray( array );
    // end::init_str_array[]

    // tag::init_edf_string[]
    EDF::String<32> string( "123.456.789" );
    EDF::Version versionString( string );
    // end::init_edf_string[]

    // tag::access_get_major[]
    version.getMajor(); // 1
    // end::access_get_major[]

    // tag::access_get_minor[]
    version.getMinor(); // 2
    // end::access_get_minor[]

    // tag::access_get_patch[]
    version.getPatch(); // 3
    // end::access_get_patch[]

    // tag::access_as_number[]
    version.asNumber(); // 10203
    // end::access_as_number[]

    // tag::access_as_string[]
    version.asString(); // EDF::String<9>("1.2.3")
    // end::access_as_string[]

    // tag::access_as_c_string[]
    version.asCString(); // "1.2.3"
    // end::access_as_c_string[]

    // tag::edf_version[]
    EDF::Version::EDF();
    // end::edf_version[]

    // tag::operator_greater[]
    if( version > "0.1.0" ) {
        /* ... */
    }
    if( "0.1.0" > version ) {
        /* ... */
    }
    if( version > EDF::Version() ) {
        /* ... */
    }
    // end::operator_greater[]

    // tag::operator_less[]
    if( version < "2.0.0" ) {
        /* ... */
    }
    if( "2.0.0" < version ) {
        /* ... */
    }
    // end::operator_less[]

    // tag::operator_greater_equal[]
    if( version >= "1.1.0" ) {
        /* ... */
    }
    if( "0.1.0" >= version ) {
        /* ... */
    }
    // end::operator_greater_equal[]

    // tag::operator_less_equal[]
    if( version <= "2.0.0" ) {
        /* ... */
    }
    if( "2.0.0" <= version ) {
        /* ... */
    }
    // end::operator_less_equal[]

    // tag::operator_equal[]
    if( version == "1.2.3" ) {
        /* ... */
    }
    if( "1.2.3" == version ) {
        /* ... */
    }
    // end::operator_equal[]

    // tag::operator_not_equal[]
    if( version != "2.14.56" ) {
        /* ... */
    }
    if( "2.14.56" != version ) {
        /* ... */
    }
    // end::operator_not_equal[]

    std::cout << version.getMajor() << '\n';
    std::cout << version.getMinor() << '\n';
    std::cout << version.getPatch() << '\n';
    std::cout << version.asNumber() << '\n';
    std::cout << version.asCString() << '\n';
    std::cout << versionString.asCString() << '\n';

    return 0;
}
