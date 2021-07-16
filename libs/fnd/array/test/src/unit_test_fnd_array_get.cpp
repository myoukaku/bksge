/**
 *	@file	unit_test_fnd_array_get.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/array/get.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test_get()
{
	using std::get;
	{
		bksge::array<int, 2> a{{1,2}};
		int& r0 = get<0>(a);
		VERIFY(r0 == 1);
		int& r1 = get<1>(a);
		VERIFY(r1 == 2);
	}
	{
		bksge::array<int, 2> const a{{3,4}};
		int const& r0 = get<0>(a);
		VERIFY(r0 == 3);
		int const& r1 = get<1>(a);
		VERIFY(r1 == 4);
	}
	{
		bksge::array<int, 2> a{{1,2}};
		int&& r0 = get<0>(std::move(a));
		VERIFY(r0 == 1);
	}
	{
		bksge::array<int, 2> const a{{3,4}};
		int const&& r0 = get<0>(std::move(a));
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
