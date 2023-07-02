/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/String.hpp"

#include <iostream>

int main() {
    EDF::String<128> test( 1234 );
    test += 567890;
    std::cout << "1:" << test.asCString() << '\n';
    test.insert( 4, " Inserted Value" );
    std::cout << (4 + (EDF::String<10>(" Okay") + test)).strip().asCString() << '\n';

    std::cout << "2:" << test.asCString() << '\n';
    test.insert( 0_uz, " \n Test \n" );
    std::cout << "3:" << test.asCString() << '\n';
    std::cout << "4:" << test.getStripped( "ea" ).asCString() << '\n';

    EDF::String<64> smallerTest = "   !Hello, world!   ";
    smallerTest.trim( " !");
    std::cout << "5:>" << smallerTest.asCString() << "<" << '\n';

    std::cout << "6:" << smallerTest.contains("Hello") << '\n';

    std::cout << "7:" << smallerTest.getReversed().asCString() << '\n';

    std::cout << "8:" << smallerTest.equals( "Hello, world" ) << '\n';

    std::cout << "9:" << smallerTest.getToUpper().asCString() << '\n';
    
    std::cout << "10:" << smallerTest.getToLower().asCString() << '\n';

    std::cout << "11:" 
              << smallerTest
                    .getAppended( " world something" )
                    .getReplaced( "world", "solar system!" )
                    .asCString()
              << '\n';

    auto comma = smallerTest.find( smallerTest.begin(), ',' );
    auto firstWord = smallerTest.find( comma + 2, ' ' );
    std::cout << "12:" 
              << smallerTest.getSubString( comma + 2, firstWord ).asCString()
              << '\n';

    std::cout << "13:" << smallerTest.asCString() << '\n';


    return 0;
}