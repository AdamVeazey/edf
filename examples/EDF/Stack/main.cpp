/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Stack.hpp>

#include <iostream>

// ---------------------------------------------------------------------------
// --------------------- Buildable Documentation Snippts ---------------------
// ---------------------------------------------------------------------------

void docSnippets() {
    // tag::init[]
    EDF::Stack<int, 4> stack;
    // end::init[]

    // tag::init_list[]
    EDF::Stack<int, 4> stackInitializationList = { 10, 20 };
    // end::init_list[]
    (void)stackInitializationList;

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
    auto nElementsInStack = stack.length();
    // end::capacity_length[]
    (void)nElementsInStack;

    // tag::capacity_max_length[]
    constexpr auto maxNumberOfElements = stack.maxLength();
    // end::capacity_max_length[]
    (void)maxNumberOfElements;

    stack.push( 3 );
    stack.push( 4 );

    // tag::operation_peek[]
    auto& lastElement = stack.peek();
    // end::operation_peek[]

    std::cout << "last element: " << lastElement << '\n';

    // tag::is_question_empty[]
    while( !stack.isEmpty() ){
        /* ... */
    // end::is_question_empty[]

        // tag::operation_pop[]
        auto mostRecentElement = stack.pop();
        // end::operation_pop[]
        (void)mostRecentElement;
    }
}

void docSnippets2() {
    // tag::init_no_default[]
    struct CustomType{
        int value;
        CustomType( int v ) : value(v) {}
    };

    EDF::Stack<CustomType, 3> stack = {
        CustomType( 0 ),
        CustomType( 0 ),
        CustomType( 0 )
    };
    stack.clear();
    // end::init_no_default[]
}

// ---------------------------------------------------------------------------
// --------------------------- Simple Example --------------------------------
// ---------------------------------------------------------------------------

enum class Move { Up, Down, Left, Right };

const char* toString( Move m ) {
    switch( m ) {
    case Move::Up:      return "Up";
    case Move::Down:    return "Down";
    case Move::Left:    return "Left";
    case Move::Right:   return "Right";
    }
}

int main() {
    EDF::Stack<Move, 5> undo;

    // Simulate user actions
    undo.push(Move::Up);
    undo.push(Move::Left);
    undo.push(Move::Down);
    undo.push(Move::Right);

    std::cout << "Undo expected order: Right Down Left Up\n";
    std::cout << "             Actual: ";
    while( !undo.isEmpty() ) {
        std::cout << toString(undo.pop()) << ' ';
    }

    return 0;
}