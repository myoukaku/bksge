/**
 *	@file	unit_test_fnd_ranges_size.cpp
 *
 *	@brief	ranges::size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/concepts/disable_sized_range.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace size_test
{

struct R
{
	BKSGE_CXX14_CONSTEXPR int size() { return 1; }
	BKSGE_CXX14_CONSTEXPR long size() const noexcept { return 2; }
};

struct R3
{
	BKSGE_CXX14_CONSTEXPR int* size() { return nullptr; }
	friend BKSGE_CXX14_CONSTEXPR int size(R3&) noexcept { return 1; }
	friend BKSGE_CXX14_CONSTEXPR long size(const R3&) { return 2L; }
	friend BKSGE_CXX14_CONSTEXPR unsigned int size(R3&&) { return 3U; }
	friend BKSGE_CXX14_CONSTEXPR unsigned long size(const R3&&) noexcept { return 4UL; }
};

struct R5
{
	BKSGE_CXX14_CONSTEXPR int size() const noexcept { return 0; }
	BKSGE_CXX14_CONSTEXPR R5* begin() { return this; }
	BKSGE_CXX14_CONSTEXPR R5* end() { return this + 1; }
};

}	// namespace size_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

template <>
BKSGE_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true, bksge_ranges_test::size_test::R5);

}}	// bksge::ranges

namespace bksge_ranges_test
{

namespace size_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a1[10] = {};
	int a2[2]  = {};

	static_assert(noexcept(bksge::ranges::size(a1)), "");
	static_assert(noexcept(bksge::ranges::size(a2)), "");

	return
		bksge::ranges::size(a1) == 10 &&
		bksge::ranges::size(a2) == 2;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	R r{};
	const R& c = r;

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert(!noexcept(bksge::ranges::size(std::declval<R&>())), "");
	static_assert( noexcept(bksge::ranges::size(std::declval<R const&>())), "");
#endif

	return
		bksge::ranges::size(r) == 1 &&
		bksge::ranges::size(c) == 2L;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R3 r{};
	const R3& c = r;

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert( noexcept(bksge::ranges::size(std::declval<R3&>())), "");
	static_assert(!noexcept(bksge::ranges::size(std::declval<R3 const&>())), "");
	static_assert(!noexcept(bksge::ranges::size(std::declval<R3&&>())), "");
	static_assert( noexcept(bksge::ranges::size(std::declval<R3 const&&>())), "");
#endif

	return
		bksge::ranges::size(r) == 1 &&
		bksge::ranges::size(c) == 2L &&
		bksge::ranges::size(bksge::move(r)) == 3U &&
		bksge::ranges::size(bksge::move(c)) == 4UL;
}

bool test04()
{
	bksge::vector<int> v = {1,2,3};

	return bksge::ranges::size(v) == 3;
}

BKSGE_CXX14_CONSTEXPR bool test05()
{
	R5 r{};
	return bksge::ranges::size(r) == 1;
}

GTEST_TEST(RangesTest, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	                      EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace size_test

}	// namespace bksge_ranges_test
