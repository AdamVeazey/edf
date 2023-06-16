/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <cstddef>

// NOTE: This needs to be in the global namespace. EX: 0_uz == std::size_t literal 
inline std::size_t operator ""_uz( unsigned long long x ) { return x; }

namespace EDF {


} /* EDF */