/**
 *	@file	unit_test_fnd_ranges_end.cpp
 *
 *	@brief	ranges::end のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/as_const.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace end_test
{

struct R
{
	int a[4] ={0, 1, 2, 3};

	       BKSGE_CXX14_CONSTEXPR const int* begin() const { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR       int* begin(R&&) noexcept { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const R&&) noexcept { return nullptr; }

	// Should be ignored because it doesn't return a sentinel for int*
	       BKSGE_CXX14_CONSTEXPR const long* end() const;

	friend BKSGE_CXX14_CONSTEXPR       int* end(R& r) { return r.a + 0; }
	friend BKSGE_CXX14_CONSTEXPR       int* end(R&& r) { return r.a + 1; }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const R& r) noexcept { return r.a + 2; }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const R&& r) noexcept { return r.a + 3; }
};

struct RV // view on an R
{
	R& r;

	       BKSGE_CXX14_CONSTEXPR const int* begin() const { return nullptr; }

	friend BKSGE_CXX14_CONSTEXPR       int* end(RV& v) noexcept { return end(v.r); }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const RV& v) { return end(bksge::as_const(v.r)); }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] ={0, 1, 2, 3};

	       BKSGE_CXX14_CONSTEXPR const void* begin() const { return nullptr; } // return type not an iterator

	friend BKSGE_CXX14_CONSTEXPR const short* begin(RR&) noexcept { return nullptr; }
	       BKSGE_CXX14_CONSTEXPR       short* end() noexcept { return &s; }

	friend BKSGE_CXX14_CONSTEXPR const long* begin(const RR&) noexcept { return nullptr; }
	       BKSGE_CXX14_CONSTEXPR const long* end() const { return &l; }

	friend BKSGE_CXX14_CONSTEXPR const int* begin(RR&&) noexcept { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR       int* end(RR&) { BKSGE_ASSERT(false); return nullptr; } // not valid for rvalues
	friend BKSGE_CXX14_CONSTEXPR       int* end(RR&& r) { return r.a + 1; }

	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RR&&) noexcept { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const RR&) { BKSGE_ASSERT(false); return nullptr; } // not valid for rvalues
	friend BKSGE_CXX14_CONSTEXPR const int* end(const RR&& r) noexcept { return r.a + 3; }
};

}	// namespace end_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

// Allow ranges::begin to work with RV&&
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::end_test::RV);

// N.B. this is a lie, end on an RR rvalue will return a dangling pointer.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::end_test::RR);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace end_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	// t + extent_v<T> if E is of array type T.

	static_assert(bksge::is_same<decltype(bksge::ranges::end(a)), decltype(a + 2)>::value, "");
	static_assert(noexcept(bksge::ranges::end(a)), "");
	return bksge::ranges::end(a) == (a + 2);
}

bool test02()
{
	bksge::vector<int> v ={1,2,3};

	static_assert(bksge::is_same<decltype(bksge::ranges::end(v)), decltype(v.end())>::value, "");
	return bksge::ranges::end(v) == v.end();
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	RV v{r};
	const RV cv{r};

	static_assert(bksge::is_same<decltype(bksge::ranges::end(r)), decltype(end(r))>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::end(c)), decltype(end(c))>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::end(std::move(v))), decltype(end(r))>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::end(std::move(cv))), decltype(end(c))>::value, "");

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(!noexcept(bksge::ranges::end(std::declval<R&>())), "");
	static_assert( noexcept(bksge::ranges::end(std::declval<R const&>())), "");
	static_assert( noexcept(bksge::ranges::end(std::move(v))), "");
	static_assert(!noexcept(bksge::ranges::end(std::move(cv))), "");
#endif

	return
		bksge::ranges::end(r) == end(r) &&
		bksge::ranges::end(c) == end(c) &&
		bksge::ranges::end(std::move(v)) == end(r) &&
		bksge::ranges::end(std::move(cv)) == end(c);
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert( noexcept(bksge::ranges::end(std::declval<RR&>())), "");
	static_assert(!noexcept(bksge::ranges::end(std::declval<RR const&>())), "");
	static_assert( noexcept(bksge::ranges::end(std::move(r))), "");
	static_assert(!noexcept(bksge::ranges::end(std::move(c))), "");
#endif

	return
		bksge::ranges::end(r) == &r.s &&
		bksge::ranges::end(c) == &r.l &&
		bksge::ranges::end(std::move(r)) == &r.s &&
		bksge::ranges::end(std::move(c)) == &r.l;
}

GTEST_TEST(RangesTest, EndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace end_test

}	// namespace bksge_ranges_test
