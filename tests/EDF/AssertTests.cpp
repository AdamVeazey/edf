/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <EDF/Assert.hpp>

#include <gtest/gtest.h>


TEST(Assert, AssertionPasses) {
    EDF_ASSERT(true, "This shouldn't be output because the condition is true");
}

TEST(Assert, AssertionFails) {
    ASSERT_DEATH(EDF_ASSERT(false, "This should be output because the condition is false"), "");
}

TEST(Assert, DebugAssertionPasses) {
#ifndef NDEBUG
    // Expecting that this condition should pass, so the program should not terminate.
    EDF_ASSERTD(true, "This shouldn't be output because the condition is true");
#else
    // When NDEBUG is not defined, EDF_ASSERTD is a no-op, so this test will pass regardless of the condition.
    SUCCEED();
#endif
}

TEST(Assert, DebugAssertionFails) {
#ifndef NDEBUG
    ASSERT_DEATH(EDF_ASSERTD(false, "This should be output because the condition is false"), "");
#else
    // When NDEBUG is not defined, EDF_ASSERTD is a no-op, so this test will pass regardless of the condition.
    SUCCEED();
#endif
}