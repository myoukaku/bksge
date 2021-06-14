/**
 *	@file	unit_test_fnd_ranges_crbegin.cpp
 *
 *	@brief	ranges::crbegin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/crbegin.hpp>
#include <bksge/fnd/ranges/rbegin.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace crbegin_test
{

struct R1
{
	int i = 0;
	int j = 0;

	       BKSGE_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	friend BKSGE_CXX14_CONSTEXPR const int* rbegin(const R1&& r) { return &r.j; }
};

struct R1V // view on an R1
{
	R1& r;

	friend BKSGE_CXX14_CONSTEXPR const long* rbegin(R1V&); // this is not defined
	friend BKSGE_CXX14_CONSTEXPR const int* rbegin(const R1V& rv) noexcept { return rv.r.rbegin(); }
};

struct R2
{
	int a[2] ={};
	long l[2] ={};

	       BKSGE_CXX14_CONSTEXPR const int* begin() const { return a; }
	       BKSGE_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend BKSGE_CXX14_CONSTEXPR const long* begin(const R2&&); // not defined
	friend BKSGE_CXX14_CONSTEXPR const long* end(const R2&&); // not defined
};

}	// namespace crbegin_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

// Allow ranges::end to work with R1V&&
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::crbegin_test::R1V);

// N.B. this is a lie, rbegin on an R2 rvalue will return a dangling pointer.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::crbegin_test::R2);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace crbegin_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	R1 r;
	const R1& c = r;
	R1V v{r};
	const R1V cv{r};

	return
		bksge::ranges::crbegin(r) == bksge::ranges::rbegin(c) &&
		bksge::ranges::crbegin(c) == bksge::ranges::rbegin(c) &&
		bksge::ranges::crbegin(bksge::move(v))  == bksge::ranges::rbegin(c) &&
		bksge::ranges::crbegin(bksge::move(cv)) == bksge::ranges::rbegin(c);
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	R2 r;
	const R2& c = r;

	return
		bksge::ranges::crbegin(r) == bksge::ranges::rbegin(c) &&
		bksge::ranges::crbegin(c) == bksge::ranges::rbegin(c) &&
		bksge::ranges::crbegin(bksge::move(r)) == bksge::ranges::rbegin(c) &&
		bksge::ranges::crbegin(bksge::move(c)) == bksge::ranges::rbegin(c);
}

GTEST_TEST(RangesTest, CRBeginTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace crbegin_test

}	// namespace bksge_ranges_test
