/**
 *	@file	unit_test_fnd_ranges_elements_view.cpp
 *
 *	@brief	ranges::elements_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/elements_view.hpp>
#include <bksge/fnd/ranges/views/reverse_view.hpp>
#include <bksge/fnd/ranges/views/filter_view.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/cbegin.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/utility/as_const.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace elements_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	std::tuple<int, int> x[] = {{1, 2}, {3, 4}, {5, 6}};
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	auto v0 = x | views::elements<0>;
#else
	auto v0 = x | views::elements_t<0>{};
#endif
	int const y[] = { 1, 3, 5 };
	VERIFY(ranges::equal(v0, y));
	VERIFY(ranges::equal(v0, x | views::keys));
	VERIFY(ranges::equal(v0.base(), x));
	VERIFY(ranges::equal(views::keys(x).base(), x));
	VERIFY(ranges::size(v0) == 3);
	VERIFY(ranges::size(bksge::as_const(v0)) == 3);

	using R0 = decltype(v0);
	static_assert(ranges::is_random_access_range<R0>::value, "");
	static_assert(ranges::is_sized_range<R0>::value, "");
	static_assert(ranges::is_common_range<R0>::value, "");

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	auto v1 = x | views::reverse | views::elements<1> | views::reverse;
#else
	auto v1 = x | views::reverse | views::elements_t<1>{} | views::reverse;
#endif
	int const z[] = { 2, 4, 6 };
	VERIFY(ranges::equal(v1, z));
	VERIFY(ranges::equal(v1, x | views::values));

	{
		auto i = v0.begin();
		VERIFY(i.base() == &x[0]);
		VERIFY(v0.begin().base() == &x[0]);
		VERIFY(i[0] == 1);
		VERIFY(i[1] == 3);
		VERIFY(i[2] == 5);
		VERIFY(*(i+1) == 3);
		VERIFY(*(2+i) == 5);
		VERIFY((i == v0.begin()) == true);
		VERIFY((i != v0.begin()) == false);
		VERIFY((i <  v0.begin()) == false);
		VERIFY((i >  v0.begin()) == false);
		VERIFY((i <= v0.begin()) == true);
		VERIFY((i >= v0.begin()) == true);
		VERIFY((i - v0.end()) == -3);
		VERIFY((v0.end() - i) ==  3);
		i += 3;
		VERIFY(*(i-1) == 5);
		VERIFY(*(i-2) == 3);
		VERIFY((i - v0.begin()) == 3);
		VERIFY((i == v0.begin()) == false);
		VERIFY((i != v0.begin()) == true);
		VERIFY((i <  v0.begin()) == false);
		VERIFY((i >  v0.begin()) == true);
		VERIFY((i <= v0.begin()) == false);
		VERIFY((i >= v0.begin()) == true);
		i -= 3;
		VERIFY((i == v0.begin()) == true);
		VERIFY((i != v0.begin()) == false);
		VERIFY((i <  v0.begin()) == false);
		VERIFY((i >  v0.begin()) == false);
		VERIFY((i <= v0.begin()) == true);
		VERIFY((i >= v0.begin()) == true);
	}

	return true;
}

struct S
{
	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, I)>
	friend constexpr bool operator==(I const& i, S)
	{
		return std::get<1>(*i) == 0;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, I)>
	friend constexpr bool operator!=(I const& i, S const& s)
	{
		return !(i == s);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, I)>
	friend constexpr bool operator==(S const& s, I const& i)
	{
		return i == s;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, I)>
	friend constexpr bool operator!=(S const& s, I const& i)
	{
		return !(i == s);
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	// This verifies that P1994R1 (and LWG3406) is implemented.
	std::pair<std::pair<char, int>, long> x[] =
	{{{(char)1, 2}, 3l}, {{(char)1, 0}, 2l}, {{(char)1, 2}, 0l}};
	ranges::subrange<decltype(ranges::begin(x)), S> r{ranges::begin(x), S{}};

	auto v = r | views::keys;
	std::pair<char, int> y[] = { {(char)1, 2}, {(char)1, 0} };
	VERIFY(ranges::equal(v, y));
	ranges::subrange<decltype(ranges::begin(v)), S> v2{ranges::begin(v), S{}};
	std::pair<char, int> z[] = { {(char)1, 2} };
	VERIFY(ranges::equal(v2, z));

	{
		auto a = ranges::cbegin(v);
		a = ranges::begin(v);
	}
	{
		auto b = ranges::cend(v);
		b = ranges::end(v);
	}

	return true;
}

struct F
{
	template <typename Tuple>
	constexpr bool operator()(Tuple const& t) const
	{
		return std::get<1>(t) < 5;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	std::tuple<int, int> x[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
	auto v0 = x | views::filter(F{}) | views::keys;
	int const y[] = { 1, 3 };
	VERIFY(ranges::equal(v0, y));

	using R0 = decltype(v0);
	static_assert(!ranges::is_sized_range<R0>::value, "");
	static_assert( ranges::is_bidirectional_range<R0>::value, "");
	static_assert(!ranges::is_random_access_range<R0>::value, "");

	auto v1 = x | views::filter(F{}) | views::values;
	int const z[] = { 2, 4 };
	VERIFY(ranges::equal(v1, z));

	using R1 = decltype(v1);
	static_assert(!ranges::is_sized_range<R1>::value, "");
	static_assert( ranges::is_bidirectional_range<R1>::value, "");
	static_assert(!ranges::is_random_access_range<R1>::value, "");

	{
		auto i = v0.begin();
		VERIFY(i == v0.begin());
		VERIFY(i != v0.end());
		VERIFY(v0.begin() == i);
		VERIFY(v0.end()   != i);
		++i;
		VERIFY(i != v0.begin());
		VERIFY(i != v0.end());
		VERIFY(v0.begin() != i);
		VERIFY(v0.end()   != i);
		i++;
		VERIFY(i != v0.begin());
		VERIFY(i == v0.end());
		VERIFY(v0.begin() != i);
		VERIFY(v0.end()   == i);
		--i;
		VERIFY(i != v0.begin());
		VERIFY(i != v0.end());
		VERIFY(v0.begin() != i);
		VERIFY(v0.end()   != i);
		i--;
		VERIFY(i == v0.begin());
		VERIFY(i != v0.end());
		VERIFY(v0.begin() == i);
		VERIFY(v0.end()   != i);
	}

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	std::tuple<int, int> x[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
	test_bidirectional_range<std::tuple<int, int>> rx(x);
	auto v0 = rx | views::filter(F{}) | views::keys;
	int const y[] = { 1, 3 };
	VERIFY(ranges::equal(v0, y));

	using R0 = decltype(v0);
	static_assert(!ranges::is_sized_range<R0>::value, "");
	static_assert(!ranges::is_common_range<R0>::value, "");
	static_assert( ranges::is_bidirectional_range<R0>::value, "");
	static_assert(!ranges::is_random_access_range<R0>::value, "");

	auto v1 = rx | views::filter(F{}) | views::values;
	int const z[] = { 2, 4 };
	VERIFY(ranges::equal(v1, z));

	using R1 = decltype(v1);
	static_assert(!ranges::is_sized_range<R1>::value, "");
	static_assert( ranges::is_bidirectional_range<R1>::value, "");
	static_assert(!ranges::is_random_access_range<R1>::value, "");

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	std::tuple<int, int> x[] = {{1, 2}, {3, 4}, {5, 6}};
	test_random_access_range<std::tuple<int, int>> rx(x);
	auto v0 = rx | views::keys;
	int const y[] = { 1, 3, 5 };
	VERIFY(ranges::equal(v0, y));

	using R0 = decltype(v0);
	static_assert( ranges::is_sized_range<R0>::value, "");
	static_assert(!ranges::is_common_range<R0>::value, "");
	static_assert( ranges::is_random_access_range<R0>::value, "");

	auto v1 = rx | views::values;
	int const z[] = { 2, 4, 6 };
	VERIFY(ranges::equal(v1, z));

	{
		auto i = v0.begin();
		VERIFY((i - v0.end()) == -3);
		VERIFY((v0.end() - i) ==  3);
		VERIFY((i.base() - v0.end().base()) == -3);
	}
	{
		auto a = ranges::cbegin(v0);
		a = ranges::begin(v0);
	}
	{
		auto b = ranges::cend(v0);
		b = ranges::end(v0);
	}

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	std::tuple<int, int> x[] = {{1, 2}, {3, 4}, {5, 6}};
	test_input_range<std::tuple<int, int>> rx(x);
	auto v0 = rx | views::keys;
	int const y[] = { 1, 3, 5 };
	VERIFY(ranges::equal(v0, y));

	using R0 = decltype(v0);
	static_assert(!ranges::is_sized_range<R0>::value, "");
	static_assert(!ranges::is_common_range<R0>::value, "");
	static_assert( ranges::is_input_range<R0>::value, "");

	auto v1 = rx | views::values;
	int const z[] = { 2, 4, 6 };
	VERIFY(ranges::equal(v1, z));

	{
		auto i = v0.begin();
		VERIFY(i == v0.begin());
		VERIFY(i != v0.end());
		VERIFY(v0.end() != i);
		++i;
		VERIFY(i != v0.begin());
		VERIFY(i != v0.end());
		i++;
		VERIFY(i != v0.begin());
		VERIFY(i != v0.end());
		++i;
		VERIFY(i != v0.begin());
		VERIFY(i == v0.end());
		VERIFY(v0.end() == i);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#if !defined(_MSC_VER)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#else
	EXPECT_TRUE(test02());
#endif
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
}

}	// namespace elements_view_test

}	// namespace bksge_ranges_test
