/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Vector.hpp>

#include <iostream>

int main( void ) {

    EDF::Vector<int, 8> vector;

    vector.pushBack( 1 );
    vector.pushBack( 2 );
    vector.pushBack( 3 );
    vector.pushBack( 5 );
    vector.pushBack( 6 );
    vector.pushBack( 7 );
    

    for( auto&& e : vector ){
        std::cout << e << '\n';
    }

    vector.insert(3, 4);

    std::cout << "After inserting 3" << '\n';

    for( auto&& e : vector ){
        std::cout << e << '\n';
    }

    vector.erase( 2 ); // erases value 3
    std::cout << "After erasing value 3" << '\n';

    for( auto&& e : vector ){
        std::cout << e << '\n';
    }


    std::cout << "popBack() " << vector.popBack() << '\n';

    std::cout << "After clearing the vector" << '\n';
    vector.clear();

    for( auto&& e : vector ){
        std::cout << e << '\n';
    }

    std::cout << "Place value 100 at end of vector" << '\n';
    vector.emplaceBack( 100 );
    for( auto&& e : vector ){
        std::cout << e << '\n';
    }

    return 0;
}