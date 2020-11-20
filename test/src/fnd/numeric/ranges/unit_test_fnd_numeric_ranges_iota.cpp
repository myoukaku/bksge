/**
 *	@file	unit_test_fnd_numeric_ranges_iota.cpp
 *
 *	@brief	ranges::iota のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/ranges/iota.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace ranges_iota_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iota(first, last, value)
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a[5]{};
		auto ret = ranges::iota(bksge::begin(a), bksge::end(a), 0);
		VERIFY(ret == bksge::end(a));
		VERIFY(a[0] == 0);
		VERIFY(a[1] == 1);
		VERIFY(a[2] == 2);
		VERIFY(a[3] == 3);
		VERIFY(a[4] == 4);
	}
	{
		int a[6]{};
		auto ret = ranges::iota(bksge::begin(a), bksge::end(a), 10);
		VERIFY(ret == bksge::end(a));
		VERIFY(a[0] == 10);
		VERIFY(a[1] == 11);
		VERIFY(a[2] == 12);
		VERIFY(a[3] == 13);
		VERIFY(a[4] == 14);
		VERIFY(a[5] == 15);
	}
	{
		int a[6]{};
		auto ret = ranges::iota(bksge::begin(a), bksge::begin(a)+3, 10);
		VERIFY(ret == bksge::begin(a)+3);
		VERIFY(a[0] == 10);
		VERIFY(a[1] == 11);
		VERIFY(a[2] == 12);
		VERIFY(a[3] == 0);
		VERIFY(a[4] == 0);
		VERIFY(a[5] == 0);
	}
	return true;
}

// iota(rng, value)
inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int a[3]{};
		auto ret = ranges::iota(a, 0);
		VERIFY(ret == bksge::end(a));
		VERIFY(a[0] == 0);
		VERIFY(a[1] == 1);
		VERIFY(a[2] == 2);
	}
	{
		int a[4]{};
		test_range<int, output_iterator_wrapper> ra(a);
		auto ret = ranges::iota(ra, 42);
		VERIFY(ret == bksge::end(ra));
		VERIFY(a[0] == 42);
		VERIFY(a[1] == 43);
		VERIFY(a[2] == 44);
		VERIFY(a[3] == 45);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, RangesIotaTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ranges_iota_test

}	// namespace bksge_numeric_test
