/**
 *	@file	unit_test_fnd_ranges_rend.cpp
 *
 *	@brief	ranges::rend のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/rend.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/iterator/make_reverse_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace rend_test
{

struct R1
{
	int i = 0;
	int j = 0;

	       BKSGE_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	       BKSGE_CXX14_CONSTEXPR const int* rend() const { return &i + 1; }
	friend BKSGE_CXX14_CONSTEXPR const int* rbegin(const R1&&); // not defined
	friend BKSGE_CXX14_CONSTEXPR const int* rend(const R1&&); // not defined
};

struct R2
{
	int i = 0;

	       BKSGE_CXX14_CONSTEXPR int* rbegin() noexcept { return &i + 1; }
	       BKSGE_CXX14_CONSTEXPR long* rend() noexcept { return nullptr; } // not a sentinel for rbegin()

	friend BKSGE_CXX14_CONSTEXPR long* rbegin(R2&) noexcept { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR int* rend(R2& r) { return &r.i; }
};

struct R3
{
	int a[2] ={};
	long l[2] ={};

	       BKSGE_CXX14_CONSTEXPR const int* begin() const { return a; }
	       BKSGE_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend BKSGE_CXX14_CONSTEXPR const long* begin(const R3&& r) { return r.l; }
	friend BKSGE_CXX14_CONSTEXPR const long* end(const R3&& r) { return r.l + 2; }
};

}	// namespace rend_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

// N.B. this is a lie, rend on an R1 rvalue will return a dangling pointer.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::rend_test::R1);

// N.B. this is a lie, begin/end on an R3 rvalue will return a dangling pointer.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::rend_test::R3);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace rend_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	R1 r;

	// decay-copy(t.rend()) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::rbegin(E))>

	return
		bksge::ranges::rend(r) == &r.i + 1 &&
		bksge::ranges::rend(std::move(r)) == &r.i + 1;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	R2 r;

	// Otherwise, decay-copy(rend(t)) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::rbegin(E))>

	auto i1 = bksge::ranges::rbegin(r);
	auto i2 = rend(r);
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	static_assert(bksge::sentinel_for<decltype(i2), decltype(i1)>, "");
#else
	static_assert(bksge::sentinel_for<decltype(i2), decltype(i1)>::value, "");
#endif

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(!noexcept(bksge::ranges::rend(std::declval<R2&>())), "");
#endif

	return bksge::ranges::rend(r) == &r.i;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R3 r;

	// Otherwise, make_reverse_iterator(ranges::begin(t)) if both
	// ranges::begin(t) and ranges::end(t) are valid expressions
	// of the same type I which models bidirectional_iterator.

	return
		bksge::ranges::rend(r)            == bksge::make_reverse_iterator(bksge::ranges::begin(r)) &&
		bksge::ranges::rend(std::move(r)) == bksge::make_reverse_iterator(bksge::ranges::begin(std::move(r)));
}

GTEST_TEST(RangesTest, REndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace rend_test

}	// namespace bksge_ranges_test
