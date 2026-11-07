/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Vector.hpp>

#include <cstdint>
#include <iostream>

// ---------------------------------------------------------------------------
// --------------------- Buildable Documentation Snippts ---------------------
// ---------------------------------------------------------------------------

void docSnippets() {
    // tag::init[]
    EDF::Vector<int, 16> vector = { 10, 2, 3, 4, 5, 6 };
    // end::init[]

    // tag::element_access_standard[]
    vector[0_uz] = 100;
    // end::element_access_standard[]

    // tag::element_access_at[]
    vector.at( 0_uz ) = 1;
    // end::element_access_at[]

    // tag::operation_insert_list[]
    for( auto it = vector.cbegin(); it != vector.cend(); ++it ) {
        if( *it == 3 ) {
            vector.insert( it, {99, 88, 77, 66, 55} );
            it += 5;
        }
    }
    // end::operation_insert_list[]

    // tag::operation_erase_range[]
    vector.erase( 2, 4 );    // [2,4)
    auto seventySeven = std::find(vector.cbegin(), vector.cend(), 77);
    vector.erase( seventySeven, seventySeven + 3 );
    // end::operation_erase_range[]

    // tag::operation_push_back[]
    vector.pushBack( 2 + 2 );
    vector.pushBack( 12345 );
    // end::operation_push_back[]

    // tag::operation_erase_single[]
    vector.erase( vector.length() - 2 );
    vector.erase( std::find( vector.cbegin(), vector.cend(), 12345 ) );
    // end::operation_erase_single[]

    // tag::operation_emplace_back[]
    vector.emplaceBack( 100 );
    // end::operation_emplace_back[]

    // tag::operation_pop_back[]
    auto copyOfLastElement = vector.popBack();
    // end::operation_pop_back[]
    (void)copyOfLastElement;
}

// ---------------------------------------------------------------------------
// --------------------------- Simple Example --------------------------------
// ---------------------------------------------------------------------------

int main() {
    EDF::Vector<uint32_t, 4> samples;

    // Simulate initial readings filling up the vector
    samples.pushBack( 105 );
    samples.pushBack( 106 );
    samples.pushBack( 108 );
    samples.pushBack( 106 );

    // Calculate average value
    uint32_t avg = 0;
    for( auto s : samples ) {
        avg += s;
    }
    avg /= samples.length();

    std::cout << "Average: " << avg << '\n';

    // Simulate adding another reading
    if( samples.isFull() ) {
        samples.erase( 0_uz );
    }
    samples.pushBack( 108 );

    // Calculate average value again
    avg = 0;
    for( auto s : samples ) {
        avg += s;
    }
    avg /= samples.length();

    std::cout << "Average: " << avg << '\n';

    return 0;
}