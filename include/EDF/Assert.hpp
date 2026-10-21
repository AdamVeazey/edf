/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#if defined(__ZEPHYR__)
    #include <zephyr/kernel.h>
    #include <zephyr/sys/printk.h>
    #define NEDF_TARGET_ZEPHYR 1
#else
    #include <cstddef>
    #include <cstdio>
    #include <cstdlib>
    #define NEDF_TARGET_ZEPHYR 0
#endif

// TODO: keep an eye out for C++23 support to use <stacktrace>

// TODO: __PRETTY_FUNCTION__ is not standard. Add in a bunch of #defines
//       to use whatever your specific compiler uses or nothing if it's not
//       supported.
#ifndef __PRETTY_FUNCTION__
#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
#define __PRETTY_FUNCTION__ __PRETTY_FUNCTION__
#else
#define __PRETTY_FUNCTION__ __func__
#endif
#endif

#ifndef NEDF_ASSERT_PRINT_ASSUMPTION
#define PRINT_ASSUMPTION_FORMAT             "assumption: %s\n"
#define PRINT_ASSUMPTION_VALUE(assumption)  , assumption
#else
#define PRINT_ASSUMPTION_FORMAT             ""
#define PRINT_ASSUMPTION_VALUE(assumption)  /* empty */
#endif

#ifndef NEDF_ASSERT_PRINT_FUNCTION_NAME
#define PRINT_FUNCTION_NAME_FORMAT          "function:   '%s'\n"
#define PRINT_FUNCTION_NAME_VALUE           , __PRETTY_FUNCTION__
#else
#define PRINT_FUNCTION_NAME_FORMAT          ""
#define PRINT_FUNCTION_NAME_VALUE           /* empty */
#endif

#ifndef NEDF_ASSERT_PRINT_FILE_NAME_LINE_NUM
#define PRINT_FILE_NAME_LINE_NUM_FORMAT     "%s:%d\n"
#define PRINT_FILE_NAME_LINE_NUM_VALUE      , __FILE__, __LINE__
#else
#define PRINT_FILE_NAME_LINE_NUM_FORMAT     ""
#define PRINT_FILE_NAME_LINE_NUM_VALUE      /* empty */
#endif

#ifndef NEDF_ASSERT_PRINT
    #if NEDF_TARGET_ZEPHYR
        #define NEDF_INTERNAL_PRINT(...) printk(__VA_ARGS__)
    #else
        #define NEDF_INTERNAL_PRINT(...) std::fprintf(stderr, __VA_ARGS__)
    #endif

    #define ASSERT_PRINT_ENABLED( condition, assumption )   \
        NEDF_INTERNAL_PRINT(                                \
            "\nAssert failed!\ncondition:  !(%s)\n"         \
            PRINT_ASSUMPTION_FORMAT                         \
            PRINT_FUNCTION_NAME_FORMAT                      \
            PRINT_FILE_NAME_LINE_NUM_FORMAT,                \
            #condition                                      \
            PRINT_ASSUMPTION_VALUE(assumption)              \
            PRINT_FUNCTION_NAME_VALUE                       \
            PRINT_FILE_NAME_LINE_NUM_VALUE                  \
        );
#else
#define ASSERT_PRINT_ENABLED( condition, assumption )
#endif

#ifndef NEDF_ASSERT_ABORT
    #if NEDF_TARGET_ZEPHYR
        #define NEDF_INTERNAL_ABORT() k_panic()
    #else
        #define NEDF_INTERNAL_ABORT() std::abort()
    #endif
#endif

/* tag::EDF_ASSERT[] */
#define EDF_ASSERT( condition, assumption )             \
/* end::EDF_ASSERT[] */                                 \
    do {                                                \
        if( !(condition) ) {                            \
            ASSERT_PRINT_ENABLED(condition, assumption) \
            NEDF_INTERNAL_ABORT();                      \
        }                                               \
    } while(0)                                          \

/* tag::EDF_ASSERTD[] */
#ifndef NDEBUG
#define EDF_ASSERTD( condition, assumption )    EDF_ASSERT( condition, assumption )
#else
#define EDF_ASSERTD( condition, assumption )    ((void)(condition))
#endif /* NDEBUG */
/* end::EDF_ASSERTD[] */
