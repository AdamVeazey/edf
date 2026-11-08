/*
 * Copyright (c) 2026, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

 #include "EDF/Assert.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace EDF {
namespace impl {

void assertion_failed(const char* format, ...) {
    std::va_list args;
    va_start(args, format);
    std::vfprintf(stderr, format, args);
    va_end(args);
}

[[noreturn]] void assertion_abort() {
    std::abort();
}

} /* impl */
} /* EDF */