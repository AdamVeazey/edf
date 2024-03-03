/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Queue.hpp>

#include <iostream>

int main( void ) {
    // tag::init[]
    EDF::Queue<int, 8> queue;
    // end::init[]

    // tag::init_list[]
    EDF::Queue<int, 8> queueInitializationList = { 10, 20 };
    // end::init_list[]

    // tag::operation_clear[]
    queue.clear();
    // end::operation_clear[]

    // tag::is_question_full[]
    if( !queue.isFull() ) {
        /* ... */
    }
    // end::is_question_full[]

    // tag::operation_push[]
    queue.push( 1 );
    // end::operation_push[]
    // tag::operation_emplace[]
    auto& valueConstructed = queue.emplace( 2 );
    // end::operation_emplace[]
    // tag::capacity_length[]
    auto nElementsInQueue = queue.length();
    // end::capacity_length[]
    // tag::capacity_max_length[]
    constexpr auto maxNumberOfElements = queue.maxLength();
    // end::capacity_max_length[]
    queue.push( 3 );
    queue.push( 4 );

    // tag::operation_peek[]
    auto& firstElement = queue.peek();
    // end::operation_peek[]

    std::cout << "first element: " << firstElement << '\n';

    // tag::is_question_empty[]
    while( !queue.isEmpty() ){
        /* ... */
    // end::is_question_empty[]

        // tag::operation_pop[]
        auto firstElement = queue.pop();
        // end::operation_pop[]
        std::cout << firstElement << '\n';
    }
    
    // tag::init_no_default[]
    struct CustomType{
        int value;
        CustomType( int v ) : value(v) {}
    };

    EDF::Queue<CustomType, 4> queue2 = {
        CustomType( 0 ),
        CustomType( 0 ),
        CustomType( 0 ),
        CustomType( 0 )
    };
    queue2.clear();
    // end::init_no_default[]
    queue2.push( CustomType(5) );
    queue2.push( CustomType(6) );
    queue2.push( CustomType(7) );

    EDF::Queue<CustomType, 4> queue3 = queue2;

    std::cout << "first element: " << queue3.peek().value << '\n';

    while( !queue2.isEmpty() ){
        std::cout << queue2.pop().value << '\n';
    }

    std::cout << "first element: " << queue3.peek().value << '\n';

    while( !queue3.isEmpty() ){
        std::cout << queue3.pop().value << '\n';
    }

    /* uint8_t specialized member functions */
    // tag::uint8_t_init[]
    EDF::Queue<uint8_t, 32> q;
    // end::uint8_t_init[]

    // tag::uint8_t_pop8be[]
    q.push( 0x12 );
    uint8_t data8be = q.pop8be(); // 0x12
    // end::uint8_t_pop8be[]
    std::cout << std::hex;
    std::cout << "data8be:  0x" << +data8be << '\n';

    // tag::uint8_t_pop16be[]
    q.push( 0x12 );
    q.push( 0x34 );
    uint16_t data16be = q.pop16be(); // 0x1234
    // end::uint8_t_pop16be[]
    std::cout << "data16be: 0x" << data16be << '\n';

    // tag::uint8_t_pop32be[]
    q.push( 0x12 );
    q.push( 0x34 );
    q.push( 0x56 );
    q.push( 0x78 );
    uint32_t data32be = q.pop32be(); // 0x12345678
    // end::uint8_t_pop32be[]
    std::cout << "data32be: 0x" << data32be << '\n';

    // tag::uint8_t_pop64be[]
    q.push( 0x12 );
    q.push( 0x34 );
    q.push( 0x56 );
    q.push( 0x78 );
    q.push( 0x9A );
    q.push( 0xBC );
    q.push( 0xDE );
    q.push( 0xF0 );
    uint64_t data64be = q.pop64be(); // 0x123456789ABCDEF0
    // end::uint8_t_pop64be[]
    std::cout << "data64be: 0x" << data64be << '\n';

    // tag::uint8_t_pop8le[]
    q.push( 0x12 );
    uint8_t data8le = q.pop8le(); // 0x12
    // end::uint8_t_pop8le[]
    std::cout << "data8le:  0x" << +data8le << '\n';

    // tag::uint8_t_pop16le[]
    q.push( 0x34 );
    q.push( 0x12 );
    uint16_t data16le = q.pop16le(); // 0x1234
    // end::uint8_t_pop16le[]
    std::cout << "data16le: 0x" << data16le << '\n';

    // tag::uint8_t_pop32le[]
    q.push( 0x78 );
    q.push( 0x56 );
    q.push( 0x34 );
    q.push( 0x12 );
    uint32_t data32le = q.pop32le(); // 0x12345678
    // end::uint8_t_pop32le[]
    std::cout << "data32le: 0x" << data32le << '\n';

    // tag::uint8_t_pop64le[]
    q.push( 0xF0 );
    q.push( 0xDE );
    q.push( 0xBC );
    q.push( 0x9A );
    q.push( 0x78 );
    q.push( 0x56 );
    q.push( 0x34 );
    q.push( 0x12 );
    uint64_t data64le = q.pop64le(); // 0x123456789ABCDEF0
    // end::uint8_t_pop64le[]
    std::cout << "data64le: 0x" << data64le << '\n';

    q.push( 0x12 );
    q.push( 0x34 );
    q.push( 0x56 );
    q.push( 0x78 );
    uint32_t be = q.pop32be();

    q.push( 0x78 );
    q.push( 0x56 );
    q.push( 0x34 );
    q.push( 0x12 );
    uint32_t le = q.pop32le();

    std::cout << "be == le: " << (be == le) 
              << " value: 0x" << std::hex << be 
              << std::endl;

    return 0;
}