#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

TEST(TestCaseName, TestName) {
	EXPECT_THAT(1, Eq(1));
}