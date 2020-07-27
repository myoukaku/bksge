/**
 *	@file	unit_test_fnd_ranges_crend.cpp
 *
 *	@brief	ranges::crend のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/crend.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace crend_test
{

struct R1
{
	int i = 0;
	int j = 0;

	       BKSGE_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	       BKSGE_CXX14_CONSTEXPR const int* rend() const { return &i + 1; }
	friend BKSGE_CXX14_CONSTEXPR const int* rbegin(const R1&& r) { return &r.j; }
	friend BKSGE_CXX14_CONSTEXPR const int* rend(const R1&& r) { return &r.j + 1; }
};

struct R2
{
	int a[2] ={};
	long l[2] ={};

	       BKSGE_CXX14_CONSTEXPR const int* begin() const { return a; }
	       BKSGE_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend BKSGE_CXX14_CONSTEXPR const long* begin(const R2&& r) { return r.l; }
	friend BKSGE_CXX14_CONSTEXPR const long* end(const R2&& r) { return r.l + 2; }
};

struct R3
{
	int i = 0;

	       BKSGE_CXX14_CONSTEXPR const int* rbegin() const noexcept { return &i + 1; }
	       BKSGE_CXX14_CONSTEXPR const long* rend() const noexcept { return nullptr; } // not a sentinel for rbegin()

	friend BKSGE_CXX14_CONSTEXPR const long* rbegin(const R3&) noexcept { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR const int* rend(const R3& r) { return &r.i; }
};

}	// namespace crend_test

}	// namespace bksge_ranges_test

// N.B. this is a lie, rend on an R1 rvalue will return a dangling pointer.
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::crend_test::R1);

// N.B. this is a lie, rend on an R2 rvalue will return a dangling pointer.
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::crend_test::R2);

// N.B. this is a lie, rend on an R3 rvalue will return a dangling pointer.
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::crend_test::R3);

namespace bksge_ranges_test
{

namespace crend_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	R1 r;
	const R1& c = r;

	return
		bksge::ranges::crend(r) == bksge::ranges::rend(c) &&
		bksge::ranges::crend(c) == bksge::ranges::rend(c) &&
		bksge::ranges::crend(bksge::move(r)) == bksge::ranges::rend(c) &&
		bksge::ranges::crend(bksge::move(c)) == bksge::ranges::rend(c);
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	R2 r;
	const R2& c = r;

	return
		bksge::ranges::crend(r) == bksge::ranges::rend(c) &&
		bksge::ranges::crend(c) == bksge::ranges::rend(c) &&
		bksge::ranges::crend(bksge::move(r)) == bksge::ranges::rend(bksge::move(c)) &&
		bksge::ranges::crend(bksge::move(c)) == bksge::ranges::rend(bksge::move(c));
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(!noexcept(bksge::ranges::crend(bksge::declval<R3&>())), "");
	static_assert(!noexcept(bksge::ranges::crend(bksge::declval<R3 const&>())), "");
#endif

	R3 r;
	const R3& c = r;
	return
		bksge::ranges::crend(r) == bksge::ranges::rend(c) &&
		bksge::ranges::crend(c) == bksge::ranges::rend(c);
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	int a[2] ={};
	const auto& c = a;

	return
		bksge::ranges::crend(a) == bksge::ranges::rend(c) &&
		bksge::ranges::crend(c) == bksge::ranges::rend(c);
}

GTEST_TEST(RangesTest, CREndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace crend_test

}	// namespace bksge_ranges_test
