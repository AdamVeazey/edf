/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Array.hpp>

#include <iostream>

int main( void ) {

    // tag::init_POD[]
    EDF::Array<int, 4> array;
    // end::init_POD[]
    // tag::element_access_standard[]
    array[0] = 1;
    // end::element_access_standard[]
    array[1] = 2; 
    array[2] = 3;
    array[3] = 4;
    // tag::element_access_at[]
    // array.at( 40 ) = 100;
    // end::element_access_at[]

    for( auto&& element : array ){
        std::cout << element << '\n';
    }

    std::cout << "Clear the array, then print it out again\n";

    array.clear();

    for( auto&& element : array ){
        std::cout << element << '\n';
    }

    // tag::init_custom_type[]
    struct CustomType{
        int value;
        CustomType( int v ) : value(v) {}        
    };

    EDF::Array<CustomType, 4> array2 = { 
        CustomType(5), 
        CustomType(6), 
        CustomType(7), 
        CustomType(8) 
    }; 
    // end::init_custom_type[]

    std::cout << "Print out array2\n";

    for( auto&& element : array2 ){
        std::cout << element.value << '\n';
    }

    std::cout << "Fill array2, then print it out again\n";
    array2.fill( CustomType(5) );
    // array2.clear();

    for( auto&& element : array2 ){
        std::cout << element.value << '\n';
    }

    // tag::init_copy_assignment[]
    EDF::Array<CustomType, 4> array3 = array2;
    // end::init_copy_assignment[]

    std::cout << "print out array3, a copy of array 2\n";

    for( auto&& element : array3 ){
        std::cout << element.value << '\n';
    }

    return 0;
}