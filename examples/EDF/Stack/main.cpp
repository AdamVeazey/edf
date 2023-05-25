/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Stack.hpp>

#include <iostream>

int main( void ) {

    EDF::Stack<int, 4> stack;
    stack.push( 1 );
    stack.push( 2 );
    stack.push( 3 );
    stack.push( 4 );

    std::cout << "last element: " << stack.top() << '\n';

    while( !stack.isEmpty() ){
        std::cout << stack.pop() << '\n';
    }

    struct CustomType{
        int value;
        CustomType( int v = 0xA5 ) : value(v) {}
    };

    EDF::Stack<CustomType, 3> stack2;
    stack2.push( CustomType(5) );
    stack2.push( CustomType(6) );
    stack2.push( CustomType(7) );

    EDF::Stack<CustomType, 3> stack3 = stack2;

    std::cout << "last element: " << stack2.top().value << '\n';

    while( !stack2.isEmpty() ){
        std::cout << stack2.pop().value << '\n';
    }

    std::cout << "last element: " << stack3.top().value << '\n';

    while( !stack3.isEmpty() ){
        std::cout << stack3.pop().value << '\n';
    }

    return 0;
}