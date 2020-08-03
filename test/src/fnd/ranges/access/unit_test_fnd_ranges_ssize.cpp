/**
 *	@file	unit_test_fnd_ranges_ssize.cpp
 *
 *	@brief	ranges::ssize のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/ssize.hpp>
#include <bksge/fnd/ranges/concepts/disable_sized_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/signed_integral.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace ssize_test
{

struct R
{
	BKSGE_CXX14_CONSTEXPR int size() const noexcept { return 0; }
	BKSGE_CXX14_CONSTEXPR R* begin() { return this; }
	BKSGE_CXX14_CONSTEXPR R* end() { return this + 1; }
};

}	// namespace ssize_test

}	// namespace bksge_ranges_test

BKSGE_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true, bksge_ranges_test::ssize_test::R);

namespace bksge_ranges_test
{

namespace ssize_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a1[10] ={};
	int a2[2] ={};

	static_assert(bksge::is_same<decltype(bksge::ranges::ssize(a1)), std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::ssize(a2)), std::ptrdiff_t>::value, "");

	static_assert(bksge::is_signed_integral<decltype(bksge::ranges::ssize(a1))>::value, "");
	static_assert(bksge::is_signed_integral<decltype(bksge::ranges::ssize(a2))>::value, "");

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(noexcept(bksge::ranges::ssize(a1)), "");
	static_assert(noexcept(bksge::ranges::ssize(a2)), "");
#endif

	return
		bksge::ranges::ssize(a1) == 10 &&
		bksge::ranges::ssize(a2) == 2;
}

bool test02()
{
	std::vector<int> v ={1,2,3,4};
	static_assert(bksge::is_signed_integral<decltype(bksge::ranges::ssize(v))>::value, "");
	return bksge::ranges::size(v) == 4;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R r;
	static_assert(bksge::is_signed_integral<decltype(bksge::ranges::ssize(r))>::value, "");
	return bksge::ranges::ssize(r) == 1;
}

GTEST_TEST(RangesTest, SSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace ssize_test

}	// namespace bksge_ranges_test
