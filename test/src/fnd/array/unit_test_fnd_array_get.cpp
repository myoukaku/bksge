/**
 *	@file	unit_test_fnd_array_get.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/array/get.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test_get()
{
	{
		bksge::array<int, 2> a{{1,2}};
		int& r0 = bksge::get<0>(a);
		VERIFY(r0 == 1);
		int& r1 = bksge::get<1>(a);
		VERIFY(r1 == 2);
	}
	{
		bksge::array<int, 2> const a{{3,4}};
		int const& r0 = bksge::get<0>(a);
		VERIFY(r0 == 3);
		int const& r1 = bksge::get<1>(a);
		VERIFY(r1 == 4);
	}
	{
		bksge::array<int, 2> a{{1,2}};
		int&& r0 = bksge::get<0>(bksge::move(a));
		VERIFY(r0 == 1);
	}
	{
		bksge::array<int, 2> const a{{3,4}};
		int const&& r0 = bksge::get<0>(bksge::move(a));
		VERIFY(r0 == 3);
	}
	return true;
}

GTEST_TEST(ArrayTest, GetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_get()));
}

#undef VERIFY

}	// namespace bksge_array_test
