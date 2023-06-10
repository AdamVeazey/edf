/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Vector.hpp>

#include <iostream>

template<typename T, std::size_t N> void
print( const EDF::Vector<T, N>& vector ){
    for( auto&& e : vector ){
        std::cout << e << ' ';
    }
    std::cout << '\n';
}

int main( void ) {

    // tag::init[]
    EDF::Vector<int, 8> vector = { 10, 2, 3, 4, 5, 6 };    
    // end::init[]

    // tag::element_access_standard[]
    vector[0] = 100;
    // end::element_access_standard[]

    // tag::element_access_at[]
    vector.at( 0 ) = 1;
    // end::element_access_at[]

    vector.insert( std::size_t(0), { 0 } );
    std::cout << "After inserting 0 at slot 0" << '\n';
    print(vector);

    std::cout << "vector.length(): " << vector.length() << std::endl;

    // std::cout << "After erasing vector[2]: " << vector[2] << '\n';
    // vector.erase( 2 ); // erases index 2
    // print(vector);

    // std::cout << "popBack() " << vector.popBack() << '\n';
    // vector.clear();

    // std::cout << "After clearing the vector" << '\n';
    // print(vector);

    // std::cout << "Place value 100 at end of vector" << '\n';
    // vector.emplaceBack( 100 );
    // print(vector);

    // std::cout << "erase vector[3 to 5]" << '\n';
    // vector.erase( 3, 5 );
    // print(vector);

    std::cout << "vector.clear()\n";
    vector.clear();
    print(vector);

    return 0;
}