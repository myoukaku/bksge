/**
 *	@file	unit_test_fnd_ranges_begin.cpp
 *
 *	@brief	ranges::begin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace begin_test
{

struct R
{
	int a[4] ={0, 1, 2, 3};

	friend BKSGE_CXX14_CONSTEXPR       int* begin(R& r) { return r.a + 0; }
	friend BKSGE_CXX14_CONSTEXPR       int* begin(R&& r); // this overload is not defined
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const R& r) noexcept { return r.a + 2; }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const R&& r) noexcept; // not defined
};

struct RV // view on an R
{
	R& r;

	friend BKSGE_CXX14_CONSTEXPR       int* begin(RV& rv) { return begin(rv.r); }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RV& rv) noexcept { return begin(rv.r); }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] ={0, 1, 2, 3};

	       BKSGE_CXX14_CONSTEXPR       short* begin() noexcept { return &s; }
	       BKSGE_CXX14_CONSTEXPR const long*  begin() const { return &l; }

	friend BKSGE_CXX14_CONSTEXPR       int* begin(RR& r) noexcept { return r.a + 0; }
	friend BKSGE_CXX14_CONSTEXPR       int* begin(RR&& r); // not defined
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RR& r) { return r.a + 2; }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RR&& r) noexcept; // not defined
};

}	// namespace begin_test

}	// namespace bksge_ranges_test

// Allow ranges::begin to work with RV&&
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::begin_test::RV);

// N.B. this is a lie, begin on an RR rvalue will return a dangling pointer.
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::begin_test::RR);

namespace bksge_ranges_test
{

namespace begin_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	static_assert(bksge::is_same<decltype(bksge::ranges::begin(a)), decltype(a + 0)>::value, "");
	static_assert(noexcept(bksge::ranges::begin(a)), "");
	return bksge::ranges::begin(a) == (a + 0);
}

bool test02()
{
	std::vector<int> v ={1,2,3};

	static_assert(bksge::is_same<decltype(bksge::ranges::begin(v)), decltype(v.begin())>::value, "");
	return bksge::ranges::begin(v) == v.begin();
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	RV v{r};
	// enable_borrowed_range<RV> allows ranges::begin to work for rvalues,
	// but it will call v.begin() or begin(v) on an lvalue:
	const RV cv{r};

	static_assert(bksge::is_same<decltype(bksge::ranges::begin(r)), decltype(begin(r))>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::begin(c)), decltype(begin(c))>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::begin(bksge::move(v))), decltype(begin(v))>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::begin(bksge::move(cv))), decltype(begin(cv))>::value, "");

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(!noexcept(bksge::ranges::begin(bksge::declval<R&>())), "");
	static_assert( noexcept(bksge::ranges::begin(bksge::declval<R const&>())), "");
	static_assert(!noexcept(bksge::ranges::begin(bksge::move(v))), "");
	static_assert( noexcept(bksge::ranges::begin(bksge::move(cv))), "");
#endif

	return
		bksge::ranges::begin(r) == begin(r) &&
		bksge::ranges::begin(c) == begin(c) &&
		bksge::ranges::begin(bksge::move(v))  == begin(v) &&
		bksge::ranges::begin(bksge::move(cv)) == begin(cv);
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert( noexcept(bksge::ranges::begin(bksge::declval<RR&>())), "");
	static_assert(!noexcept(bksge::ranges::begin(bksge::declval<RR const&>())), "");
	static_assert( noexcept(bksge::ranges::begin(bksge::move(r))), "");
	static_assert(!noexcept(bksge::ranges::begin(bksge::move(c))), "");
#endif

	return
		bksge::ranges::begin(r) == &r.s &&
		bksge::ranges::begin(c) == &r.l &&
		bksge::ranges::begin(bksge::move(r)) == bksge::ranges::begin(r) &&
		bksge::ranges::begin(bksge::move(c)) == bksge::ranges::begin(c);
}

GTEST_TEST(RangesTest, BeginTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace begin_test

}	// namespace bksge_ranges_test
