/**
 *	@file	unit_test_fnd_functional_cref.cpp
 *
 *	@brief	cref のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/cref.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_functional_test
{

namespace cref_test
{

GTEST_TEST(CRefTest, TypeTest)
{
	int i = 0;
	auto r = bksge::cref(i);
	static_assert(bksge::is_same<decltype(r), bksge::reference_wrapper<int const>>::value, "");
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
	return bksge::cref(f)(i, j);
}

inline BKSGE_CXX14_CONSTEXPR int
invoke_test02(int i, int j)
{
	F f{};
	return bksge::cref(bksge::cref(f))(i, j);
}

GTEST_TEST(CRefTest, InvokeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(1, 2), 2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(1, 2), 2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(3, 4), 12);
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(3, 4), 12);
}

}	// namespace cref_test

}	// namespace bksge_functional_test
