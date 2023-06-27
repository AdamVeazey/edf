/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Heap.hpp>

#include <iostream>
#include <cstring>

void exampleMaxHeap() {
    // tag::init_max[]
    EDF::HeapMax<int, 7> heap;
    // end::init_max[]

    // tag::init_max_list[]
    EDF::HeapMax<int, 7> heapInitializationList = { 10, 20 };
    // end::init_max_list[]

    // tag::operation_clear[]
    heap.clear();
    // end::operation_clear[]

    // tag::is_question_full[]
    if( !heap.isFull() ) {
        /* ... */
    }
    // end::is_question_full[]

    // tag::operation_push[]
    heap.push( 2 );
    // end::operation_push[]
    // tag::operation_emplace[]
    heap.emplace( 6 );
    // end::operation_emplace[]
    // tag::capacity_length[]
    auto& nElementsInHeap = heap.length();
    // end::capacity_length[]
    // tag::capacity_max_length[]
    constexpr auto maxNumberOfElements = heap.maxLength();
    // end::capacity_max_length[]
    heap.push( 1 );
    heap.push( 7 );
    heap.push( 4 );
    heap.push( 5 );
    heap.push( 3 );

    // tag::operation_peek[]
    auto& rootElement = heap.peek();
    // end::operation_peek[]

    // tag::is_question_empty[]
    while( !heap.isEmpty() ) {
        /* ... */
    // end::is_question_empty[]
        // tag::operation_pop[]
        auto removedElement = heap.pop();
        // end::operation_pop[]
        std::cout << removedElement << '\n';
    }

    // tag::init_max_no_default[]
    struct CustomType {
        int value;
        CustomType( int v ) : value(v) {}
    };

    EDF::HeapMax<CustomType, 3> heap2 = {
        CustomType( 0 ),
        CustomType( 0 ),
        CustomType( 0 ),
    };
    heap2.clear();
    // end::init_max_no_default[]
}

void exampleMinHeap() {
    // tag::init_min[]
    EDF::HeapMin<int, 7> heap;
    // end::init_min[]

    heap.push( 2 );
    heap.push( 6 );
    heap.push( 1 );
    heap.push( 7 );
    heap.push( 4 );
    heap.push( 5 );
    heap.push( 3 );

    while( !heap.isEmpty() ) {
        std::cout << heap.pop() << '\n';
    }
}

int main( int argc, char* argv[] ){

    if( argc > 1 ) {
        // has at least 2 arguments
        auto whichExample = argv[1]; // valid value is either "min" or "max"
        if( std::strcmp(whichExample, "min") == 0 ) {
            exampleMinHeap();
        }
        else if( std::strcmp( whichExample, "max" ) == 0 ) {
            exampleMaxHeap();
        }
        else{
            std::cout << "Argument must be 'min' or 'max'. You entered: " 
                << argv[1] 
                << std::endl;
        }
    }
    else {
        std::cout << "Max heap output:" << '\n';
        exampleMaxHeap();
        std::cout << "Min heap output:" << '\n';
        exampleMinHeap();
    }

    return 0;
}