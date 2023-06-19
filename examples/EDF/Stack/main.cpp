/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Stack.hpp>

#include <iostream>

int main( void ) {
    // tag::init[]
    EDF::Stack<int, 4> stack;
    // end::init[]

    // tag::init_list[]
    EDF::Stack<int, 4> stackInitializationList = { 10, 20 };
    // end::init_list[]

    // tag::operation_clear[]
    stack.clear();
    // end::operation_clear[]

    // tag::is_question_full[]
    if( !stack.isFull() ) {
        /* ... */
    }
    // end::is_question_full[]

    // tag::operation_push[]
    stack.push( 1 );
    // end::operation_push[]
    // tag::operation_emplace[]
    stack.emplace( 2 );
    // end::operation_emplace[]
    // tag::capacity_length[]
    auto& nElementsInStack = stack.length();
    // end::capacity_length[]
    // tag::capacity_max_length[]
    constexpr auto maxNumberOfElements = stack.maxLength();
    // end::capacity_max_length[]
    stack.push( 3 );
    stack.push( 4 );

    // tag::operation_top[]
    auto& lastElement = stack.top();
    // end::operation_top[]

    std::cout << "last element: " << lastElement << '\n';

    // tag::is_question_empty[]
    while( !stack.isEmpty() ){
        /* ... */
    // tag::is_question_empty[]

        // tag::operation_pop[]
        auto mostRecentElement = stack.pop();
        // end::operation_pop[]
        std::cout << mostRecentElement << '\n';
    }
    
    // tag::init_no_default[]
    struct CustomType{
        int value;
        CustomType( int v ) : value(v) {}
    };

    EDF::Stack<CustomType, 3> stack2 = {
        CustomType( 0 ),
        CustomType( 0 ),
        CustomType( 0 )
    };
    stack2.clear();
    // end::init_no_default[]

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