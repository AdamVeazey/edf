/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_EDF_ASSERT_HPP_
#define SRC_EDF_ASSERT_HPP_

#include <cstddef>
#include <cstdio>

// TODO: keep an eye out for C++23 support to use <stacktrace>

// TODO: __PRETTY_FUNCTION__ is not standard. Add in a bunch of #defines
//       to use whatever your specific compiler uses or nothing if it's not
//       supported.

#define EDF_ASSERT( condition )  do{                                \
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
                                        abort();                    \
                                    }                               \
                                }while(0)                           \

#ifndef NDEBUG
#define EDF_ASSERTD(condition)   EDF_ASSERT(condition)
#else
#define EDF_ASSERTD(condition)
#endif /* NDEBUG */

#endif /* SRC_EDF_ASSERT_HPP_ */