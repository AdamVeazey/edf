/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <EDF/Heap.hpp>
#include <EDF/String.hpp>

#include <iostream>

// ---------------------------------------------------------------------------
// --------------------- Buildable Documentation Snippts ---------------------
// ---------------------------------------------------------------------------

void docSnippets() {
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
    auto nElementsInHeap = heap.length();
    // end::capacity_length[]
    (void)nElementsInHeap;

    // tag::capacity_max_length[]
    constexpr auto maxNumberOfElements = heap.maxLength();
    // end::capacity_max_length[]
    (void)maxNumberOfElements;

    // tag::operation_peek[]
    auto& rootElement = heap.peek();
    // end::operation_peek[]
    (void)rootElement;

    // tag::is_question_empty[]
    while( !heap.isEmpty() ) {
        /* ... */
    // end::is_question_empty[]

        // tag::operation_pop[]
        auto removedElement = heap.pop();
        // end::operation_pop[]
        (void)removedElement;
    }
}

void docSnippets2() {
    // tag::init_max_no_default[]
    struct CustomType {
        int value;
        CustomType( int v ) : value(v) {}
        constexpr bool operator>( const CustomType& rhs ) const {
            return value > rhs.value;
        }
        constexpr bool operator<(  const CustomType& rhs ) const {
            return value < rhs.value;
        }
    };

    EDF::HeapMax<CustomType, 3> heap = {
        CustomType( 0 ),
        CustomType( 0 ),
        CustomType( 0 ),
    };
    heap.clear();
    // end::init_max_no_default[]
}

void docSnippets3() {
    // tag::init_min[]
    EDF::HeapMin<int, 7> heap;
    // end::init_min[]
}

// ---------------------------------------------------------------------------
// --------------------------- Simple Example --------------------------------
// ---------------------------------------------------------------------------

struct Task {
    uint8_t priority; // Lower number = higher priority
    int taskId; // Task Control Block ID number

    // Min-heap: higher priority (lower number) comes to the root
    constexpr bool operator>( const Task& other ) const { return priority > other.priority; }
    constexpr bool operator<( const Task& other ) const { return priority < other.priority; }
};

int main() {
    EDF::HeapMin<Task, 5> scheduler;

    scheduler.push({ .priority = 5, .taskId = 0 }); // Background logger
    scheduler.push({ .priority = 1, .taskId = 1 }); // Emergency power fault
    scheduler.push({ .priority = 3, .taskId = 2 }); // Sensor poll

    std::cout << "Executing tasks by priority:\n";
    while( !scheduler.isEmpty() ) {
        Task t = scheduler.pop();
        std::cout << "Priority: " << +t.priority
                  << "Running Task ID: " << t.taskId << '\n';
    }
    return 0;
}