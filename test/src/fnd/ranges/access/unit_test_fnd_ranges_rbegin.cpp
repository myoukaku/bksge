/**
 *	@file	unit_test_fnd_ranges_rbegin.cpp
 *
 *	@brief	ranges::rbegin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/rbegin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/iterator/make_reverse_iterator.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace rbegin_test
{

struct R1
{
	int i = 0;
	int j = 0;

	       BKSGE_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	friend BKSGE_CXX14_CONSTEXPR const int* rbegin(const R1&& r) { return &r.j; }
};

struct R2
{
	int a[2] ={};

	       BKSGE_CXX14_CONSTEXPR const int* begin() const { return a; }
	       BKSGE_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend BKSGE_CXX14_CONSTEXPR const long* begin(const R2&&); // not defined
	friend BKSGE_CXX14_CONSTEXPR const long* end(const R2&&); // not defined
};

}	// namespace rbegin_test

}	// namespace bksge_ranges_test

// N.B. this is a lie, rbegin on an R1 rvalue will return a dangling pointer.
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::rbegin_test::R1);

// N.B. this is a lie, begin/end on an R2 rvalue will return a dangling pointer.
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::rbegin_test::R2);

namespace bksge_ranges_test
{

namespace rbegin_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	R1 r;
	// decay-copy(t.rbegin()) if it is a valid expression
	// and its type I models input_or_output_iterator.
	return
		bksge::ranges::rbegin(r) == &r.i &&
		bksge::ranges::rbegin(bksge::move(r)) == &r.i;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	R2 r;
	// Otherwise, decay-copy(rbegin(t)) if it is a valid expression
	// and its type I models input_or_output_iterator [...]
	return
		bksge::ranges::rbegin(r)              == bksge::make_reverse_iterator(bksge::ranges::end(r)) &&
		bksge::ranges::rbegin(bksge::move(r)) == bksge::make_reverse_iterator(bksge::ranges::end(bksge::move(r)));
}

GTEST_TEST(RangesTest, RBeginTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace rbegin_test

}	// namespace bksge_ranges_test
