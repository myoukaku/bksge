/**
 *	@file	unit_test_fnd_functional_ref.cpp
 *
 *	@brief	ref のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/ref.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_functional_test
{

namespace ref_test
{

GTEST_TEST(RefTest, TypeTest)
{
	int i = 0;
	auto r = bksge::ref(i);
	static_assert(bksge::is_same<decltype(r), bksge::reference_wrapper<int>>::value, "");
}

struct F
{
	BKSGE_CXX14_CONSTEXPR int operator()(int i, int j) { return i + j; }
	BKSGE_CXX14_CONSTEXPR int operator()(int i, int j) const { return i * j; }
};

inline BKSGE_CXX14_CONSTEXPR int
invoke_test01(int i, int j)
{
	F f{};
	return bksge::ref(f)(i, j);
}

inline BKSGE_CXX14_CONSTEXPR int
invoke_test02(int i, int j)
{
	F f{};
	return bksge::ref(bksge::ref(f))(i, j);
}

GTEST_TEST(RefTest, InvokeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(1, 2), 3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(1, 2), 3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(3, 4), 7);
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(3, 4), 7);
}

}	// namespace ref_test

}	// namespace bksge_functional_test
