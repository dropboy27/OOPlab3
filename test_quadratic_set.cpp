#include <gtest/gtest.h>
#include "quadratic_set.h"

TEST(QuadraticSetTest, EmptyOnCreation)
{
    QuadraticSet set;

    EXPECT_EQ(set.size(), 0u);
    EXPECT_TRUE(set.empty());
}