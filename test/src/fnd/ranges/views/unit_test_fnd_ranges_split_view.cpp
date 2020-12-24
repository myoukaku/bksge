/**
 *	@file	unit_test_fnd_ranges_split_view.cpp
 *
 *	@brief	ranges::split_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/split_view.hpp>
#include <bksge/fnd/ranges/views/transform_view.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/cbegin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace split_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	char x[] = "the quick brown fox";
	using R = test_forward_range<char>;
	R rx(x, x+sizeof(x)-1);
	auto v = rx | views::split(' ');
	auto i = v.begin();
	VERIFY(i == v.begin());
	VERIFY(i != v.end());
	VERIFY(v.begin() == i);
	VERIFY(v.end() != i);
	VERIFY(ranges::equal(*i++, bksge::string_view("the")));
	VERIFY(ranges::equal(*i++, bksge::string_view("quick")));
	VERIFY(ranges::equal(*i++, bksge::string_view("brown")));
	VERIFY(ranges::equal(*i++, bksge::string_view("fox")));
	VERIFY(i != v.begin());
	VERIFY(i == v.end());
	VERIFY(v.begin() != i);
	VERIFY(v.end() == i);

	VERIFY(ranges::equal(v.base(), rx));
	VERIFY(ranges::equal(views::split(rx, ' ').base(), rx));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	char x[] = "the quick brown fox";
	using R = test_input_range<char>;
	R rx(x, x+sizeof(x)-1);
	auto v = rx | views::split(' ');
	auto i = v.begin();
	VERIFY(ranges::equal(*i, bksge::string_view("the")));
	++i;
	VERIFY(ranges::equal(*i, bksge::string_view("quick")));
	i++;
	VERIFY(ranges::equal(*i, bksge::string_view("brown")));
	++i;
	VERIFY(ranges::equal(*i, bksge::string_view("fox")));
	i++;
	VERIFY(i == v.end());

	return true;
}

inline bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	bksge::string str = "hello world";
	auto v = str | views::transform(bksge::identity{}) | views::split(' ');

	// Verify that _Iterator<false> is implicitly convertible to _Iterator<true>.
	static_assert(!bksge::is_same_as<
		decltype(ranges::begin(v)),
		decltype(ranges::cbegin(v))>::value, "");
	auto b = ranges::cbegin(v);
	b = ranges::begin(v);
	VERIFY(b != ranges::end(v));
	VERIFY(b != ranges::cend(v));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1,0,2,0,0,3,4,0,0,0,5,6,7,0,0,8,9};
	int p[] = {0,0};
	auto v = x | views::split(p);
	auto i = v.begin();
	{
		auto inner_iter = (*i).begin();
		VERIFY(inner_iter == (*i).begin());
		VERIFY(inner_iter != (*i).end());
		VERIFY((*i).end() != inner_iter);
		inner_iter++;
		VERIFY(inner_iter != (*i).begin());
		VERIFY(inner_iter != (*i).end());
		VERIFY((*i).end() != inner_iter);
		++inner_iter;
		VERIFY(inner_iter != (*i).begin());
		VERIFY(inner_iter != (*i).end());
		VERIFY((*i).end() != inner_iter);
		inner_iter++;
		VERIFY(inner_iter != (*i).begin());
		VERIFY(inner_iter == (*i).end());
		VERIFY((*i).end() == inner_iter);
	}
	VERIFY(i == v.begin());
	VERIFY(i != v.end());
	int const a1[] = {1,0,2};
	VERIFY(ranges::equal(*i++, a1));
	int const a2[] = {3,4};
	VERIFY(ranges::equal(*i++, a2));
	int const a3[] = {0,5,6,7};
	VERIFY(ranges::equal(*i++, a3));
	int const a4[] = {8,9};
	VERIFY(ranges::equal(*i++, a4));
	VERIFY(i != v.begin());
	VERIFY(i == v.end());

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1,2,0,3,4,5};
	using R1 = test_input_range<int>;
	R1 rx(x);
	int p[] = {0};
	using R2 = test_forward_static_sized_view<int, 1>;
	R2 rp(p);

	using V1 = views::all_t<R1&>;
	using V2 = views::all_t<R2&>;

	static_assert( ranges::is_input_range<V1>::value, "");
	static_assert( ranges::is_forward_range<V2>::value, "");
	static_assert( ranges::is_view<V1>::value, "");
	static_assert( ranges::is_view<V2>::value, "");
	static_assert(!ranges::is_forward_range<V1>::value, "");
	static_assert( ranges::detail::is_tiny_range<V2>::value, "");

	auto v = ranges::split_view<V1, V2>(rx, rp);
	{
		auto i = v.begin();
		auto inner_iter = (*i).begin();
		VERIFY(inner_iter != (*i).end());
		VERIFY((*i).end() != inner_iter);
		VERIFY(*inner_iter == 1);
		inner_iter++;
		VERIFY(inner_iter != (*i).end());
		VERIFY((*i).end() != inner_iter);
		VERIFY(*inner_iter == 2);
		++inner_iter;
		VERIFY(inner_iter == (*i).end());
		VERIFY((*i).end() == inner_iter);
	}
	auto i = v.begin();
	int const a1[] = {1,2};
	VERIFY(ranges::equal(*i, a1));
	i++;
	int const a2[] = {3,4,5};
	VERIFY(ranges::equal(*i, a2));
	++i;
	VERIFY(i == v.end());

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1,2,0,3,4,5};
	using R1 = test_input_range<int>;
	R1 rx(x);
	int p[] = {0};
	using R2 = test_forward_static_sized_view<int, 0>;
	R2 rp(p, p);

	using V1 = views::all_t<R1&>;
	using V2 = views::all_t<R2&>;

	static_assert( ranges::is_input_range<V1>::value, "");
	static_assert( ranges::is_forward_range<V2>::value, "");
	static_assert( ranges::is_view<V1>::value, "");
	static_assert( ranges::is_view<V2>::value, "");
	static_assert(!ranges::is_forward_range<V1>::value, "");
	static_assert( ranges::detail::is_tiny_range<V2>::value, "");

	auto v = ranges::split_view<V1, V2>(rx, rp);
	{
		auto i = v.begin();
		auto inner_iter = (*i).begin();
		VERIFY(inner_iter != (*i).end());
		VERIFY((*i).end() != inner_iter);
		inner_iter++;
		VERIFY(inner_iter == (*i).end());
		VERIFY((*i).end() == inner_iter);
		++inner_iter;
		VERIFY(inner_iter == (*i).end());
		VERIFY((*i).end() == inner_iter);
	}
	auto i = v.begin();
	int const a1[] = {1};
	VERIFY(ranges::equal(*i, a1));
	i++;
	int const a2[] = {2};
	VERIFY(ranges::equal(*i, a2));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test07()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1,2,0,3,4,5};
	using R1 = test_forward_range<int>;
	R1 rx(x);
	int p[] = {0};
	using R2 = test_forward_range<int>;
	R2 rp(p, p);

	using V1 = views::all_t<R1&>;
	using V2 = views::all_t<R2&>;
	auto v = ranges::split_view<V1, V2>(rx, rp);
	{
		auto i = v.begin();
		auto inner_iter = (*i).begin();
		VERIFY(inner_iter != (*i).end());
		VERIFY((*i).end() != inner_iter);
		inner_iter++;
		VERIFY(inner_iter == (*i).end());
		VERIFY((*i).end() == inner_iter);
		++inner_iter;
		VERIFY(inner_iter == (*i).end());
		VERIFY((*i).end() == inner_iter);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewTest)
{
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
}

}	// namespace split_view_test

}	// namespace bksge_ranges_test
