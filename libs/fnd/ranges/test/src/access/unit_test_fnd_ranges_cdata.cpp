/**
 *	@file	unit_test_fnd_ranges_cdata.cpp
 *
 *	@brief	ranges::cdata のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/cdata.hpp>
#include <bksge/fnd/ranges/data.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace cdata_test
{

struct R
{
	int i = 0;
	int j = 0;
	BKSGE_CXX14_CONSTEXPR int* data() { return &j; }
	BKSGE_CXX14_CONSTEXPR const R* data() const noexcept { return nullptr; }
};

struct R3
{
	long l = 0;

	BKSGE_CXX14_CONSTEXPR int* data() const { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR long* begin(R3&& r); // this function is not defined
	friend BKSGE_CXX14_CONSTEXPR const long* begin(const R3& r) { return &r.l; }
	friend BKSGE_CXX14_CONSTEXPR const short* begin(const R3&&); // not defined
};

}	// namespace cdata_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

// This is a lie, ranges::begin(R3&&) returns a dangling iterator.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::cdata_test::R3);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace cdata_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	R r;
	const R& c = r;

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(!noexcept(bksge::ranges::data(std::declval<R&>())), "");
	static_assert( noexcept(bksge::ranges::data(std::declval<R const&>())), "");
	static_assert( noexcept(bksge::ranges::cdata(std::declval<R&>())), "");
	static_assert( noexcept(bksge::ranges::cdata(std::declval<R const&>())), "");
#endif

	return
		bksge::ranges::data(r) == &r.j &&
		bksge::ranges::data(c) == (R*)nullptr &&
		bksge::ranges::cdata(r) == (R*)nullptr &&
		bksge::ranges::cdata(c) == (R*)nullptr;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[] ={0, 1};
	return bksge::ranges::cdata(a) == a + 0;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R3 r;
	const R3& c = r;

	return
		bksge::ranges::cdata(r) == bksge::ranges::data(c) &&
		bksge::ranges::cdata(bksge::move(r)) == bksge::ranges::begin(c) &&
		bksge::ranges::cdata(bksge::move(c)) == bksge::ranges::begin(c);
}

GTEST_TEST(RangesTest, CDataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace cdata_test

}	// namespace bksge_ranges_test
