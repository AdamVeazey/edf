/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef NDEBUG
#define NDEBUG
#endif

#include <EDF/Assert.hpp>

#include <gtest/gtest.h>


TEST(AssertRelease, AssertionPasses) {
    EDF_ASSERT(true, "This shouldn't be output because the condition is true");
    SUCCEED();
}

TEST(AssertRelease, AssertionFails) {
    EDF_ASSERTD(false, "This shouldn't cause an abort in release mode");
    SUCCEED();
}

TEST(AssertRelease, AssertionSideEffectEvaluation) {
    int sideEffectCounter = 1;
    // In Release mode (NDEBUG defined), side effects don't happen
    EDF_ASSERTD(--sideEffectCounter, "Shouldn't cause an abort or decrement the counter");
    EXPECT_EQ(sideEffectCounter, 1);
}
