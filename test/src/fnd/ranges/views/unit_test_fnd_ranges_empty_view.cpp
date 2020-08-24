/**
 *	@file	unit_test_fnd_ranges_empty_view.cpp
 *
 *	@brief	ranges::empty_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/empty_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/data.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/empty.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace empty_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test()
{
	static_assert(bksge::ranges::is_view<bksge::ranges::empty_view<T>>::value, "");

	bksge::ranges::empty_view<T> e{};

	VERIFY(e.begin() == nullptr);
	VERIFY(e.end()   == nullptr);
	VERIFY(e.data()  == nullptr);
	VERIFY(e.size()  == 0);
	VERIFY(e.empty());

	VERIFY(bksge::ranges::begin(e) == nullptr);
	VERIFY(bksge::ranges::end(e)   == nullptr);
	VERIFY(bksge::ranges::data(e)  == nullptr);
	VERIFY(bksge::ranges::size(e)  == 0);
	VERIFY(bksge::ranges::empty(e));

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	auto e2 = bksge::ranges::views::empty<T>;
	static_assert(bksge::is_same<decltype(e), decltype(e2)>::value, "");
#endif

	auto e3 = bksge::ranges::views::empty<T>();
	static_assert(bksge::is_same<decltype(e), decltype(e3)>::value, "");

	return true;
}

#undef VERIFY

struct A {};

GTEST_TEST(RangesTest, EmptyViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<float>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());
}

}	// namespace empty_view_test

}	// namespace bksge_ranges_test
