/**
 *	@file	unit_test_fnd_ranges_data.cpp
 *
 *	@brief	ranges::data のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/data.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/memory/to_address.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace data_test
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
	friend BKSGE_CXX14_CONSTEXPR long* begin(R3& r) { return &r.l; }
	friend BKSGE_CXX14_CONSTEXPR const long* begin(const R3& r) { return &r.l + 1; }
};

}	// namespace data_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

// N.B. this is a lie, begin on an R3 rvalue will return a dangling pointer.
template <>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge_ranges_test::data_test::R3);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace data_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	R r;
	const R& c = r;

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(!noexcept(bksge::ranges::data(bksge::declval<R&>())), "");
	static_assert( noexcept(bksge::ranges::data(bksge::declval<R const&>())), "");
#endif

	return
		bksge::ranges::data(r) == &r.j &&
		bksge::ranges::data(c) == (R*)nullptr;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[] ={0, 1};
	return bksge::ranges::data(a) == a + 0;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R3 r;
	const R3& c = r;
	// r.data() can only be used on an lvalue, but ranges::begin(R3&&) is OK
	// because R3 satisfies ranges::borrowed_range.
	return
		bksge::ranges::data(bksge::move(r)) == bksge::to_address(bksge::ranges::begin(bksge::move(r))) &&
		bksge::ranges::data(bksge::move(c)) == bksge::to_address(bksge::ranges::begin(bksge::move(c)));
}

GTEST_TEST(RangesTest, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace data_test

}	// namespace bksge_ranges_test
