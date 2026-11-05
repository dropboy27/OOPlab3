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

TEST(QuadraticSetTest, RemoveMissing)
{
    QuadraticSet set;
    EXPECT_FALSE(set.remove(Quadratic(1, 1, 1)));
    set.add(Quadratic(2, 2, 2));
    EXPECT_FALSE(set.remove(Quadratic(1, 1, 1)));
    EXPECT_FALSE(set.remove(Quadratic(3, 3, 3)));
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set.contains(Quadratic(2, 2, 2)));
}

TEST(QuadraticSetTest, RemoveOnlyElement)
{
    QuadraticSet set;
    set.add(Quadratic(1, 2, 3));
    EXPECT_TRUE(set.remove(Quadratic(1, 2, 3)));
    EXPECT_EQ(set.size(), 0u);
    EXPECT_TRUE(set.empty());
    EXPECT_FALSE(set.contains(Quadratic(1, 2, 3)));
}

TEST(QuadraticSetTest, CopyAssignment)
{
    QuadraticSet set;
    set.add(Quadratic(1, 1, 1));
    set.add(Quadratic(2, 2, 2));
    QuadraticSet copy;
    copy.add(Quadratic(3, 3, 3));

    copy = set;
    EXPECT_TRUE(copy == set);
    copy.remove(Quadratic(1, 1, 1));
    EXPECT_EQ(copy.size(), 1u);
    EXPECT_TRUE(copy.contains(Quadratic(2, 2, 2)));
    EXPECT_EQ(set.size(), 2u);
    EXPECT_TRUE(set.contains(Quadratic(1, 1, 1)));
}

TEST(QuadraticSetTest, MoveAssignment)
{
    QuadraticSet set;
    set.add(Quadratic(1, 1, 1));
    set.add(Quadratic(2, 2, 2));
    QuadraticSet moved;
    moved.add(Quadratic(3, 3, 3));

    moved = std::move(set);
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_TRUE(moved.contains(Quadratic(1, 1, 1)));
    EXPECT_TRUE(moved.contains(Quadratic(2, 2, 2)));
    EXPECT_TRUE(set.empty());
}

TEST(QuadraticSetTest, CallOperator)
{
    QuadraticSet set;
    set.add(Quadratic(1, 2, 3));
    EXPECT_TRUE(set(Quadratic(1, 2, 3)));
    EXPECT_FALSE(set(Quadratic(3, 2, 1)));
}

TEST(QuadraticSetTest, CompoundAssignment)
{
    QuadraticSet set;
    set += Quadratic(1, 2, 3);
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set.contains(Quadratic(1, 2, 3)));
    set -= Quadratic(1, 2, 3);
    EXPECT_TRUE(set.empty());
}

TEST(QuadraticSetTest, CompareSets)
{
    QuadraticSet first;
    QuadraticSet second;
    first.add(Quadratic(1, 1, 1));
    first.add(Quadratic(2, 2, 2));
    second.add(Quadratic(2, 2, 2));
    second.add(Quadratic(1, 1, 1));

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);
    second.remove(Quadratic(1, 1, 1));
    second.add(Quadratic(3, 3, 3));
    EXPECT_FALSE(first == second);
    EXPECT_TRUE(first != second);
}

TEST(QuadraticSetTest, ManyElements)
{
    QuadraticSet set;
    for (int i = 999; i >= 0; i--)
    {
        EXPECT_TRUE(set.add(Quadratic(i, 0, 0)));
    }
    EXPECT_EQ(set.size(), 1000u);

    for (int i = 0; i < 1000; i++)
    {
        EXPECT_TRUE(set.contains(Quadratic(i, 0, 0)));
        EXPECT_FALSE(set.add(Quadratic(i, 0, 0)));
    }
    EXPECT_EQ(set.size(), 1000u);
}
