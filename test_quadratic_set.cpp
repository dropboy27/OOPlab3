#include <gtest/gtest.h>
#include <utility>
#include "quadratic_set.h"

TEST(QuadraticSetTest, EmptyOnCreation)
{
    QuadraticSet set;

    EXPECT_EQ(set.size(), 0u);
    EXPECT_TRUE(set.empty());
}

TEST(QuadraticSetTest, OneElement)
{
    QuadraticSet set;
    EXPECT_TRUE(set.add(Quadratic(1, 2, 3)));
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set.contains(Quadratic(1, 2, 3)));
}

TEST(QuadraticSetTest, Duplicate)
{
    QuadraticSet set;
    EXPECT_TRUE(set.add(Quadratic(1, 2, 3)));
    EXPECT_FALSE(set.add(Quadratic(1, 2, 3)));
    EXPECT_EQ(set.size(), 1u);
}

TEST(QuadraticSetTest, Delete)
{
    QuadraticSet set;
    EXPECT_TRUE(set.add(Quadratic(1, 1, 1)));
    EXPECT_TRUE(set.add(Quadratic(2, 2, 1)));
    EXPECT_TRUE(set.add(Quadratic(3, 2, 3)));
    EXPECT_EQ(set.size(), 3u);
    EXPECT_TRUE(set.remove(Quadratic(2, 2, 1)));
}

TEST(QuadraticSetTest, Copy)
{
    QuadraticSet set;
    EXPECT_TRUE(set.add(Quadratic(1, 1, 1)));
    QuadraticSet copy(set);
    copy.add(Quadratic(2, 2, 2));
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set.contains(Quadratic(1, 1, 1)));
}

TEST(QuadraticSetTest, Move)
{
    QuadraticSet set;
    EXPECT_TRUE(set.add(Quadratic(1, 1, 1)));
    QuadraticSet copy(std::move(set));
    EXPECT_TRUE(copy.contains(Quadratic(1, 1, 1)));
    EXPECT_TRUE(set.empty());
}

TEST(QuadraticSetTest, Union)
{
    QuadraticSet first;
    QuadraticSet second;
    first.add(Quadratic(1, 1, 1));
    first.add(Quadratic(2, 2, 2));
    second.add(Quadratic(2, 2, 2));
    second.add(Quadratic(3, 3, 3));

    QuadraticSet result = first | second;
    EXPECT_EQ(result.size(), 3u);
    EXPECT_TRUE(result.contains(Quadratic(1, 1, 1)));
    EXPECT_TRUE(result.contains(Quadratic(2, 2, 2)));
    EXPECT_TRUE(result.contains(Quadratic(3, 3, 3)));
}

TEST(QuadraticSetTest, Intersection)
{
    QuadraticSet first;
    QuadraticSet second;
    first.add(Quadratic(1, 1, 1));
    first.add(Quadratic(2, 2, 2));
    second.add(Quadratic(2, 2, 2));
    second.add(Quadratic(3, 3, 3));

    QuadraticSet result = first & second;
    EXPECT_EQ(result.size(), 1u);
    EXPECT_TRUE(result.contains(Quadratic(2, 2, 2)));
}

TEST(QuadraticSetTest, Difference)
{
    QuadraticSet first;
    QuadraticSet second;
    first.add(Quadratic(1, 1, 1));
    first.add(Quadratic(2, 2, 2));
    second.add(Quadratic(2, 2, 2));
    second.add(Quadratic(3, 3, 3));

    QuadraticSet result = first - second;
    EXPECT_EQ(result.size(), 1u);
    EXPECT_TRUE(result.contains(Quadratic(1, 1, 1)));
}
