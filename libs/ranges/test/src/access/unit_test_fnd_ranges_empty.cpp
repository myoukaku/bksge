/**
 *	@file	unit_test_fnd_ranges_empty.cpp
 *
 *	@brief	ranges::empty のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/empty.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace empty_test
{

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};
	return !bksge::ranges::empty(a);
}

bool test02()
{
	bksge::vector<int> v1 ={1};
	bksge::vector<int> v2;
	bksge::list<int>   l1 ={1,2};
	bksge::list<int>   l2;
	bksge::forward_list<int> fl1 ={1,2,3};
	bksge::forward_list<int> fl2;

	static_assert(bksge::is_same<decltype(bksge::ranges::empty(v1)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(v2)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(l1)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(l2)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(fl1)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(fl2)), bool>::value, "");

	return
		!bksge::ranges::empty(v1) &&
		 bksge::ranges::empty(v2) &&
		!bksge::ranges::empty(l1) &&
		 bksge::ranges::empty(l2) &&
		!bksge::ranges::empty(fl1) &&
		 bksge::ranges::empty(fl2);
}

struct R1
{
	BKSGE_CXX14_CONSTEXPR int empty() const noexcept { return 0; }
};
struct R2
{
	BKSGE_CXX14_CONSTEXPR const void* empty() const { return this; }
};

BKSGE_CXX14_CONSTEXPR bool test03()
{
	R1 r1{};
	R2 r2{};

	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r1)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r2)), bool>::value, "");

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert( noexcept(bksge::ranges::empty(bksge::declval<R1 const&>())), "");
	static_assert(!noexcept(bksge::ranges::empty(bksge::declval<R2 const&>())), "");
#endif

	return
		!bksge::ranges::empty(r1) &&
		 bksge::ranges::empty(r2);
}

struct R3
{
	BKSGE_CXX14_CONSTEXPR int size() const noexcept { return 0; }
};
struct R4
{
	BKSGE_CXX14_CONSTEXPR int size() const { return 1; }
};

BKSGE_CXX14_CONSTEXPR bool test04()
{
	R3 r3{};
	R4 r4{};

	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r3)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r4)), bool>::value, "");

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 90000))
	static_assert( noexcept(bksge::ranges::empty(bksge::declval<R3 const&>())), "");
	static_assert(!noexcept(bksge::ranges::empty(bksge::declval<R4 const&>())), "");
#endif

	return
		 bksge::ranges::empty(r3) &&
		!bksge::ranges::empty(r4);
}

BKSGE_CXX14_CONSTEXPR bool test05()
{
	int a[2] {};
	test_forward_range<int>       r1{};
	test_forward_range<int>       r2(a, a);
	test_forward_range<int>       r3(a, a+1);
	test_bidirectional_range<int> r4{};
	test_bidirectional_range<int> r5(a, a+2);

	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r1)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r2)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r3)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r4)), bool>::value, "");
	static_assert(bksge::is_same<decltype(bksge::ranges::empty(r5)), bool>::value, "");

	return
		 bksge::ranges::empty(r1) &&
		 bksge::ranges::empty(r2) &&
		!bksge::ranges::empty(r3) &&
		 bksge::ranges::empty(r4) &&
		!bksge::ranges::empty(r5);
}

GTEST_TEST(RangesTest, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace empty_test

}	// namespace bksge_ranges_test
