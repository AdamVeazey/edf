/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdlib>

// TODO: keep an eye out for C++23 support to use <stacktrace>

// TODO: __PRETTY_FUNCTION__ is not standard. Add in a bunch of #defines
//       to use whatever your specific compiler uses or nothing if it's not
//       supported.

/* tag::EDF_ASSERT[] */
#define EDF_ASSERT( condition ) \
/* end::EDF_ASSERT[] */                                             \
                                do{                                 \
                                    if( !(condition) ) {            \
                                        std::fprintf(               \
                                            stderr,                 \
                                            "Assert failed !(%s)\n" \
                                            "%s\n"                  \
                                            "%s:%d\n",              \
                                            #condition,             \
                                            __PRETTY_FUNCTION__,    \
                                            __FILE__, __LINE__      \
                                        );                          \
                                        std::abort();               \
                                    }                               \
                                }while(0)                           \
/* tag::EDF_ASSERTD[] */
#ifndef NDEBUG
#define EDF_ASSERTD( condition )    EDF_ASSERT( condition )
#else
#define EDF_ASSERTD( condition )
#endif /* NDEBUG */
/* end::EDF_ASSERTD[] */
