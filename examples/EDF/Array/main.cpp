/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Array.hpp>

#include <iostream>
#include <algorithm>

// ---------------------------------------------------------------------------
// --------------------- Buildable Documentation Snippts ---------------------
// ---------------------------------------------------------------------------

void docSnippets() {
    // tag::init_POD[]
    EDF::Array<int, 4> array;
    // end::init_POD[]

    // tag::element_access_standard[]
    array[0] = 1;
    // end::element_access_standard[]

    // tag::element_access_at[]
    // array.at( 40 ) = 100; // Throws out-of-bounds error
    // end::element_access_at[]

    // tag::init_custom_type[]
    struct CustomType {
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

    // tag::init_copy_assignment[]
    EDF::Array<CustomType, 4> array3 = array2;
    // end::init_copy_assignment[]

    (void)array3;
}

// ---------------------------------------------------------------------------
// --------------------------- Simple Example --------------------------------
// ---------------------------------------------------------------------------

template<std::size_t N>
constexpr EDF::Array<int, N> generateSensorThresholds() {
    EDF::Array<int, N> table;
    for( std::size_t k = 0; k < N; ++k ) {
        // Pre-calculate non-linear scaling or calibration values
        table[k] = static_cast<int>((k * k) * 25);
    }
    return table;
}

int main() {
    // This entire table is calculated by the compiler and baked into ROM!
    constexpr auto thresholds = generateSensorThresholds<5>();

    std::cout << "Table capacity: " << thresholds.maxLength() << " entries\n\n";

    std::cout << "Index-based access:\n";
    for( std::size_t k = 0; k < thresholds.maxLength(); ++k ) {
        std::cout << "threshold[" << k << "]: " << thresholds[k] << " mV\n";
    }

    std::cout << "\nRange-based iteration (STL compatibility):\n";
    for( auto val : thresholds ) {
        std::cout << val << " mV\n";
    }

    return 0;
}