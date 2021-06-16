/**
 *	@file	unit_test_fnd_memory_addressof.cpp
 *
 *	@brief	addressof のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace addressof_test
{

struct UselessType {};

// operator&がオーバーロードされていないクラス
struct A
{
};

// operator&がオーバーロードされているクラス
struct B
{
	BKSGE_CONSTEXPR UselessType operator&(void) const
	{
		return UselessType();
	}
};

// operator&がグローバル関数としてオーバーロードされているクラス
struct C
{
};

BKSGE_CONSTEXPR UselessType operator&(C const&)
{
	return UselessType();
}

BKSGE_CONSTEXPR int func(UselessType)
{
	return 0;
}

BKSGE_CONSTEXPR int func(A const*)
{
	return 1;
}

BKSGE_CONSTEXPR int func(B const*)
{
	return 2;
}

BKSGE_CONSTEXPR int func(C const*)
{
	return 3;
}

GTEST_TEST(MemoryTest, AddressofTest)
{
	{
		BKSGE_CONSTEXPR                int n1 = 0;
		BKSGE_CONSTEXPR const          int n2 = 0;
		                      volatile int n3 = 0;
		                const volatile int n4 = 0;
		BKSGE_CONSTEXPR_EXPECT_TRUE(&n1 == bksge::addressof(n1));
		BKSGE_CONSTEXPR_EXPECT_TRUE(&n2 == bksge::addressof(n2));
		                EXPECT_TRUE(&n3 == bksge::addressof(n3));
		                EXPECT_TRUE(&n4 == bksge::addressof(n4));
	}
	{
		BKSGE_CONSTEXPR A a {};
		BKSGE_CONSTEXPR_EXPECT_EQ(1, func(&a));
		BKSGE_CONSTEXPR_EXPECT_EQ(1, func(bksge::addressof(a)));
	}
	{
		BKSGE_CONSTEXPR B b {};
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(0, func(&b));
#if defined(BKSGE_APPLE_CLANG)
		                      EXPECT_EQ(2, func(bksge::addressof(b)));
#else
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, func(bksge::addressof(b)));
#endif
	}
	{
		BKSGE_CONSTEXPR C c {};
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(0, func(&c));
#if defined(BKSGE_APPLE_CLANG)
		                      EXPECT_EQ(3, func(bksge::addressof(c)));
#else
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, func(bksge::addressof(c)));
#endif
	}
}

}	// namespace addressof_test

}	// namespace bksge_memory_test
