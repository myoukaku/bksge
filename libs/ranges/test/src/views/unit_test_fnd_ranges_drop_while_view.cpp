/**
 *	@file	unit_test_fnd_ranges_drop_while_view.cpp
 *
 *	@brief	ranges::drop_while_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/drop_while_view.hpp>
#include <bksge/fnd/ranges/views/take_view.hpp>
#include <bksge/fnd/ranges/views/iota_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/contiguous_range.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace drop_while_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct NotEqual
{
	int N;
	constexpr bool operator()(int i) const { return i != N; }
};

struct Less
{
	int N;
	constexpr bool operator()(int i) const { return i < N; }
};

BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1,2,3,4,5,6,7,8,9};
	auto v = x | views::drop_while(NotEqual{5});

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert( ranges::is_sized_range<R>::value, "");
	static_assert( ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_contiguous_range<R>::value, "");

	VERIFY(ranges::size(v) == 5);

	int y[] = {5,6,7,8,9};
	VERIFY(ranges::equal(v, y));

	VERIFY(v.pred()(5) == false);
	VERIFY(v.pred()(6) == true);

	{
		auto b = v.base();
		VERIFY(ranges::equal(b, x));
	}
	{
		auto b = views::drop_while(x, NotEqual{5}).base();
		VERIFY(ranges::equal(b, x));
	}

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
#if !defined(BKSGE_MSVC)
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = views::iota(0) | views::drop_while(Less{14}) | views::take(5);

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = {14,15,16,17,18};
	VERIFY(ranges::equal(v, y));
#endif
	return true;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1,2,3,4,5};
	test_bidirectional_range<int> rx(x);
	auto v = rx | views::drop_while(Less{4});

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = {4,5};
	VERIFY(ranges::equal(v, y));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, DropWhileViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace drop_while_view_test

}	// namespace bksge_ranges_test
