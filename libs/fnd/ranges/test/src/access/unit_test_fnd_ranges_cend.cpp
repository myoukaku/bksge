/**
 *	@file	unit_test_fnd_ranges_cend.cpp
 *
 *	@brief	ranges::cend のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/cend.hpp>
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

namespace cend_test
{

struct R
{
	int a[4] ={0, 1, 2, 3};

	       BKSGE_CXX14_CONSTEXPR const int* begin() const { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const R&& ) noexcept { return nullptr; }

	// Should be ignored because it doesn't return a sentinel for int*
	       BKSGE_CXX14_CONSTEXPR const long* end() const { return nullptr; }

	friend BKSGE_CXX14_CONSTEXPR       int* end(R& r) { return r.a + 0; }
	friend BKSGE_CXX14_CONSTEXPR       int* end(R&& r) { return r.a + 1; }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const R& r) noexcept { return r.a + 2; }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const R&& r) noexcept { return r.a + 3; }
};

struct RV // view on an R
{
	R& r;

	friend BKSGE_CXX14_CONSTEXPR const int* begin(RV& rv) { return rv.r.begin(); }
	friend BKSGE_CXX14_CONSTEXPR       int* end(RV& rv) { return end(rv.r); }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RV& rv) noexcept { return rv.r.begin(); }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const RV& rv) noexcept { return end(bksge::as_const(rv.r)); }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] ={0, 1, 2, 3};

	       BKSGE_CXX14_CONSTEXPR const void* begin() const; // return type not an iterator

	friend BKSGE_CXX14_CONSTEXPR       int*   end(RR&) { BKSGE_ASSERT(false); return nullptr; }
	       BKSGE_CXX14_CONSTEXPR       short* end() noexcept { return &s; }

	friend BKSGE_CXX14_CONSTEXPR const long* begin(const RR&) noexcept { return nullptr; }
	       BKSGE_CXX14_CONSTEXPR const long* end() const { return &l; }

	friend BKSGE_CXX14_CONSTEXPR       int* begin(RR&&) noexcept { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR       int* end(RR&& r) { return r.a + 1; }

	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RR&&) noexcept { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR const int* end(const RR&& r) noexcept { return r.a + 3; }
};

}	// namespace cend_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

// Allow ranges::end to work with RV&&
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::cend_test::RV);

// N.B. this is a lie, begin/end on an RR rvalue will return a dangling pointer.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::cend_test::RR);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace cend_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	static_assert(bksge::is_same<decltype(bksge::ranges::cend(a)), const int*>::value, "");
	static_assert(noexcept(bksge::ranges::cend(a)), "");
	return bksge::ranges::cend(a) == (a + 2);
}

bool test02()
{
	bksge::vector<int> v ={1,2,3};

	static_assert(bksge::is_same<decltype(bksge::ranges::cend(v)), decltype(v.cend())>::value, "");
	return bksge::ranges::cend(v) == v.cend();
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	RV v{r};
	const RV cv{r};

	return
		bksge::ranges::cend(r) == bksge::ranges::end(c) &&
		bksge::ranges::cend(c) == bksge::ranges::end(c) &&
		bksge::ranges::cend(std::move(v))  == bksge::ranges::end(c) &&
		bksge::ranges::cend(std::move(cv)) == bksge::ranges::end(c);
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;

	return
		bksge::ranges::cend(r) == bksge::ranges::end(c) &&
		bksge::ranges::cend(c) == bksge::ranges::end(c) &&
		bksge::ranges::cend(std::move(r)) == bksge::ranges::end(c) &&
		bksge::ranges::cend(std::move(c)) == bksge::ranges::end(c);
}

GTEST_TEST(RangesTest, CEndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace cend_test

}	// namespace bksge_ranges_test
