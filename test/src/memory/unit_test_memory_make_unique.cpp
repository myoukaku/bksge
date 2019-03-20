/**
 *	@file	unit_test_memory_make_unique.cpp
 *
 *	@brief	make_unique のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/memory/make_unique.hpp>
#include <gtest/gtest.h>
#include <memory>

namespace bksge_memory_make_unique_test
{

class Foo
{
public:
	static unsigned int instances;

	explicit Foo(
		int v1 = 0,
		int v2 = 0,
		int v3 = 0,
		int v4 = 0,
		int v5 = 0,
		int v6 = 0,
		int v7 = 0,
		int v8 = 0,
		int v9 = 0)
		: sum(v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + v9)
	{
		instances++;
	}

	~Foo()
	{
		instances--;
	}

	const int sum;

private:
	Foo(const Foo&);
	Foo& operator=(const Foo&);
};

unsigned int Foo::instances = 0;

GTEST_TEST(MemoryTest, MakeUniqueArgsTest)
{
	using bksge::make_unique;
	using std::unique_ptr;

	EXPECT_EQ(0u, Foo::instances);
	{
		unique_ptr<Foo> x = make_unique<Foo>();
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(0, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6, 7);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6 + 7, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6, 7, 8);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6, 7, 8, 9);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
}

GTEST_TEST(MemoryTest, MakeUniqueArrayTest)
{
	using bksge::make_unique;
	using std::unique_ptr;

    {
        unique_ptr<int[]> a1 = make_unique<int[]>(3);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(0, a1[0]);
        EXPECT_EQ(0, a1[1]);
        EXPECT_EQ(0, a1[2]);
    }

    {
        unique_ptr<int[][2]> a1 = make_unique<int[][2]>(2);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(0, a1[0][0]);
        EXPECT_EQ(0, a1[0][1]);
        EXPECT_EQ(0, a1[1][0]);
        EXPECT_EQ(0, a1[1][1]);
    }

    {
        unique_ptr<const int[]> a1 = make_unique<const int[]>(3);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(0, a1[0]);
        EXPECT_EQ(0, a1[1]);
        EXPECT_EQ(0, a1[2]);
    }

    {
        unique_ptr<const int[][2]> a1 = make_unique<const int[][2]>(2);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(0, a1[0][0]);
        EXPECT_EQ(0, a1[0][1]);
        EXPECT_EQ(0, a1[1][0]);
        EXPECT_EQ(0, a1[1][1]);
    }

	EXPECT_EQ(0u, Foo::instances);
	{
        unique_ptr<Foo[]> a1 = make_unique<Foo[]>(3);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(3u, Foo::instances);
        a1.reset();
		EXPECT_EQ(0u, Foo::instances);
    }

    {
        unique_ptr<Foo[][2]> a1 = make_unique<Foo[][2]>(2);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(4u, Foo::instances);
    }
	EXPECT_EQ(0u, Foo::instances);

    {
        unique_ptr<const Foo[]> a1 = make_unique<const Foo[]>(3);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(3u, Foo::instances);
        a1.reset();
		EXPECT_EQ(0u, Foo::instances);
    }

    {
        unique_ptr<const Foo[][2]> a1 = make_unique<const Foo[][2]>(2);
        EXPECT_TRUE(a1.get() != nullptr);
        EXPECT_EQ(4u, Foo::instances);
    }
	EXPECT_EQ(0u, Foo::instances);
}

}	// namespace bksge_memory_make_unique_test
