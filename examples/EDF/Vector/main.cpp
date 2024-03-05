/*
 * Copyright (c) 2024, Adam Veazey
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
    EDF::Vector<int, 16> vector = { 10, 2, 3, 4, 5, 6 };    
    // end::init[]
    
    print( vector );

    // tag::element_access_standard[]
    vector[0_uz] = 100;
    // end::element_access_standard[]
    
    print( vector );

    // tag::element_access_at[]
    vector.at( 0_uz ) = 1;
    // end::element_access_at[]
    
    print( vector );

    // tag::operation_insert_list[]
    for( auto it = vector.cbegin(); it != vector.cend(); ++it ) {
        if( *it == 3 ) {
            vector.insert( it, {99, 88, 77, 66, 55} );
            it += 5;
        }
    }
    // end::operation_insert_list[]
    
    print( vector );

    // tag::operation_erase_range[]
    vector.erase( 2, 4 );    // [2,4) 
    auto seventySeven = std::find(vector.cbegin(), vector.cend(), 77);
    vector.erase( seventySeven, seventySeven + 3 );
    // end::operation_erase_range[]
    
    print( vector );

    // tag::operation_push_back[]
    vector.pushBack( 2 + 2 );
    vector.pushBack( 12345 );
    // end::operation_push_back[]
    
    print( vector );

    // tag::operation_erase_single[]
    vector.erase( vector.length() - 2 ); 
    vector.erase( std::find( vector.cbegin(), vector.cend(), 12345 ) );
    // end::operation_erase_single[]
    
    print( vector );

    // tag::operation_emplace_back[]
    vector.emplaceBack( 100 );
    // end::operation_emplace_back[]
    
    print( vector );

    // tag::operation_pop_back[]
    auto copyOfLastElement = vector.popBack();
    // end::operation_pop_back[]
    std::cout << "copy of last element: " << copyOfLastElement << std::endl;
    print( vector );

    return 0;
}