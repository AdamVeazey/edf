/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <EDF/Assert.hpp>

#include <gtest/gtest.h>


TEST(AssertDebug, AssertionPasses) {
    EDF_ASSERT(true, "This shouldn't be output because the condition is true");
    SUCCEED();
}

TEST(AssertDebug, AssertionFails) {
    ASSERT_DEATH(EDF_ASSERT(false, "This should be output because the condition is false"), "");
}

TEST(AssertDebug, DebugAssertionSideEffectEvaluation) {
    int sideEffectCounter = 1;
    // In Debug mode, a failing condition triggers an abort, so we test it inside ASSERT_DEATH.
    // The side effect executes right before the assertion triggers an abort.
    ASSERT_DEATH(EDF_ASSERTD(--sideEffectCounter, "Should decrement and then abort"), "");
}
