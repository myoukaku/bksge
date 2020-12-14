/**
 *	@file	unit_test_fnd_tuple_tuple_cat.cpp
 *
 *	@brief	tuple_cat のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_cat.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/array/array.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_tuple_test
{

namespace tuple_cat_test
{

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat()),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::tuple<>>())),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::tuple<>&>())),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::tuple<> const>())),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::tuple<> const&>())),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::pair<int, bool>>())),
	bksge::tuple<int, bool>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::pair<int, bool>&>())),
	bksge::tuple<int, bool>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::pair<int, bool> const>())),
	bksge::tuple<int, bool>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::pair<int, bool> const&>())),
	bksge::tuple<int, bool>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::array<int, 3>>())),
	bksge::tuple<int, int, int>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::array<int, 3>&>())),
	bksge::tuple<int, int, int>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::array<int, 3> const>())),
	bksge::tuple<int, int, int>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(bksge::declval<bksge::array<int, 3> const&>())),
	bksge::tuple<int, int, int>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(
		bksge::declval<bksge::tuple<>>(),
		bksge::declval<bksge::tuple<>>())),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(
		bksge::declval<bksge::tuple<>>(),
		bksge::declval<bksge::tuple<>>(),
		bksge::declval<bksge::tuple<>>())),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(
		bksge::declval<bksge::tuple<>>(),
		bksge::declval<bksge::array<char, 0>>(),
		bksge::declval<bksge::array<int, 0>>(),
		bksge::declval<bksge::tuple<>>())),
	bksge::tuple<>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(
		bksge::declval<bksge::tuple<int>>(),
		bksge::declval<bksge::tuple<double>>())),
	bksge::tuple<int, double>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(
		bksge::declval<bksge::tuple<int>>(),
		bksge::declval<bksge::tuple<double>>(),
		bksge::declval<bksge::tuple<const long&>>())),
	bksge::tuple<int, double, const long&>>::value, "");

static_assert(bksge::is_same<
	decltype(bksge::tuple_cat(
		bksge::declval<bksge::array<wchar_t, 3>&>(),
		bksge::declval<bksge::tuple<double>>(),
		bksge::declval<bksge::tuple<>>(),
		bksge::declval<bksge::tuple<unsigned&>>(),
		bksge::declval<bksge::pair<bool, std::nullptr_t>>())),
	bksge::tuple<wchar_t, wchar_t, wchar_t, double, unsigned&, bool, std::nullptr_t>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::tuple<> t1;
		auto t2 = bksge::tuple_cat(t1);
		static_assert(bksge::is_same<decltype(t2), bksge::tuple<>>::value, "");
	}
	{
		bksge::tuple<int>          t1(1);
		bksge::tuple<char, double> t2('a', 3.5);
		auto t3 = bksge::tuple_cat(t1, t2);
		static_assert(bksge::is_same<decltype(t3), bksge::tuple<int, char, double>>::value, "");
		VERIFY(get<0>(t3) == 1);
		VERIFY(get<1>(t3) == 'a');
		VERIFY(get<2>(t3) == 3.5);
	}
	{
		bksge::array<int, 3> a {{1,2,3}};
		bksge::pair<float, char> p { 0.5f, 'b' };
		bksge::tuple<double, short, long> t(1.5, 4, 5);
		auto t2 = bksge::tuple_cat(a, p, t);
		static_assert(bksge::is_same<decltype(t2),
			bksge::tuple<int, int, int, float, char, double, short, long>>::value, "");
		VERIFY(get<0>(t2) == 1);
		VERIFY(get<1>(t2) == 2);
		VERIFY(get<2>(t2) == 3);
		VERIFY(get<3>(t2) == 0.5f);
		VERIFY(get<4>(t2) == 'b');
		VERIFY(get<5>(t2) == 1.5);
		VERIFY(get<6>(t2) == 4);
		VERIFY(get<7>(t2) == 5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, TupleCatTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace tuple_cat_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP();
