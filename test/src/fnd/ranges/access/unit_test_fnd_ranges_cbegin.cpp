/**
 *	@file	unit_test_fnd_ranges_cbegin.cpp
 *
 *	@brief	ranges::cbegin のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/cbegin.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/as_const.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace cbegin_test
{

struct R
{
	int a[4] ={0, 1, 2, 3};

	friend BKSGE_CXX14_CONSTEXPR       int* begin(R& r) { return r.a + 0; }
	friend BKSGE_CXX14_CONSTEXPR       int* begin(R&&); // this function is not defined
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const R& r) noexcept { return r.a + 2; }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const R&&); // this function is not defined
};

struct RV // view on an R
{
	R& r;

	friend BKSGE_CXX14_CONSTEXPR       int* begin(RV&); // this function is not defined
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RV& rv) noexcept { return begin(bksge::as_const(rv.r)); }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] ={0, 1, 2, 3};

	       BKSGE_CXX14_CONSTEXPR       short* begin() noexcept { return &s; }
	       BKSGE_CXX14_CONSTEXPR const long*  begin() const { return &l; }

	friend BKSGE_CXX14_CONSTEXPR       int* begin(RR& r) { return r.a + 0; }
	friend BKSGE_CXX14_CONSTEXPR       int* begin(RR&& r) { return r.a + 1; }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RR& r) { return r.a + 2; }
	friend BKSGE_CXX14_CONSTEXPR const int* begin(const RR&& r) noexcept { return r.a + 3; }
};

}	// namespace cbegin_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

// Allow ranges::begin to work with RV&&
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::cbegin_test::RV);

// N.B. this is a lie, cbegin on an RR rvalue will return a dangling pointer.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::cbegin_test::RR);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace cbegin_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	static_assert(bksge::is_same<decltype(bksge::ranges::cbegin(a)), const int*>::value, "");
	static_assert(noexcept(bksge::ranges::cbegin(a)), "");
	return bksge::ranges::cbegin(a) == (a + 0);
}

bool test02()
{
	std::vector<int> v ={1,2,3};

	static_assert(bksge::is_same<decltype(bksge::ranges::cbegin(v)), decltype(v.cbegin())>::value, "");
	return bksge::ranges::cbegin(v) == v.cbegin();
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	RV v{r};
	const RV cv{r};

	return
		bksge::ranges::cbegin(r) == bksge::ranges::begin(c) &&
		bksge::ranges::cbegin(c) == bksge::ranges::begin(c) &&
		bksge::ranges::cbegin(bksge::move(v))  == bksge::ranges::begin(c) &&
		bksge::ranges::cbegin(bksge::move(cv)) == bksge::ranges::begin(c);
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;

	return
		bksge::ranges::cbegin(r) == bksge::ranges::begin(c) &&
		bksge::ranges::cbegin(c) == bksge::ranges::begin(c) &&
		bksge::ranges::cbegin(bksge::move(r)) == bksge::ranges::begin(c) &&
		bksge::ranges::cbegin(bksge::move(c)) == bksge::ranges::begin(c);
}

GTEST_TEST(RangesTest, CBeginTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace cbegin_test

}	// namespace bksge_ranges_test
