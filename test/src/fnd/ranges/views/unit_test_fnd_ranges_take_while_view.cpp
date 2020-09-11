/**
 *	@file	unit_test_fnd_ranges_take_while_view.cpp
 *
 *	@brief	ranges::take_while_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/take_while_view.hpp>
#include <bksge/fnd/ranges/views/iota_view.hpp>
#include <bksge/fnd/ranges/views/transform_view.hpp>
#include <bksge/fnd/ranges/views/filter_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/contiguous_range.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/functional/negate.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace take_while_view_test
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

struct IsOdd
{
	constexpr bool operator()(int i) const { return i % 2 == 1; }
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = views::iota(10) | views::take_while(NotEqual{16});

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_random_access_range<R>::value, "");
	static_assert(!ranges::is_contiguous_range<R>::value, "");

	int y[] = {10,11,12,13,14,15};
	VERIFY(ranges::equal(v, y));

	VERIFY(v.pred()(15) == true);
	VERIFY(v.pred()(16) == false);

	VERIFY((v.begin() == v.end()) == false);
	VERIFY((v.begin() != v.end()) == true);
	VERIFY((v.end() == v.begin()) == false);
	VERIFY((v.end() != v.begin()) == true);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	test_forward_range<int> rx(x);
	auto v = rx | views::take_while(Less{4});

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_forward_range<R>::value, "");
	static_assert(!ranges::is_bidirectional_range<R>::value, "");

	int y[] = {1,2,3};
	VERIFY(ranges::equal(v, y));

	VERIFY(v.base().begin() == rx.begin());
	VERIFY(views::take_while(rx, Less{4}).base().begin() == rx.begin());
	auto e = v.end().base();
	VERIFY(v.begin() != e);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 3, 4, 5};
	test_forward_range<int> rx(x);
	auto v = rx | views::transform(bksge::negate<>{}) | views::take_while(Less{4});

	// Verify that _Sentinel<false> is implicitly convertible to _Sentinel<true>.
	using R = decltype(v);
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert(!bksge::is_same_as<
		decltype(ranges::end(v)),
		decltype(ranges::cend(v))>::value, "");
	auto b = ranges::cend(v);
	b = ranges::end(v);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	auto v = views::iota(0) | views::filter(IsOdd{}) | views::take_while(Less{10});

	using R = decltype(v);
	static_assert( ranges::is_view<R>::value, "");
	static_assert(!ranges::is_sized_range<R>::value, "");
	static_assert(!ranges::is_common_range<R>::value, "");
	static_assert( ranges::is_bidirectional_range<R>::value, "");
	static_assert(!ranges::is_random_access_range<R>::value, "");

	int y[] = {1,3,5,7,9};
	VERIFY(ranges::equal(v, y));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, TakeWhileViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace take_while_view_test

}	// namespace bksge_ranges_test
