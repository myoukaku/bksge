/**
 *	@file	unit_test_tuple_tuple_sort_type.cpp
 *
 *	@brief	tuple_sort_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/tuple/tuple_sort_type.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <type_traits>
#include "my_tuple.hpp"

namespace bksge_tuple_test
{

namespace tupe_sort_type_test
{

struct size_greater
{
	template <typename T1, typename T2>
	using type = std::integral_constant<bool, (sizeof(T1) > sizeof(T2))>;
};

template <template <typename...> class Tuple>
void TupleSortTypeTest()
{
	{
		using t = Tuple<
			std::integral_constant<int, 3>,
			std::integral_constant<int, 1>,
			std::integral_constant<int, 4>,
			std::integral_constant<int, 1>,
			std::integral_constant<int, 5>,
			std::integral_constant<int, 9>,
			std::integral_constant<int, 2>,
			std::integral_constant<int, 6>,
			std::integral_constant<int, 5>,
			std::integral_constant<int, 3>,
			std::integral_constant<int, 5>
		>;

		using t2 = bksge::tuple_sort_type_t<t>;

		using expected = Tuple<
			std::integral_constant<int, 1>,
			std::integral_constant<int, 1>,
			std::integral_constant<int, 2>,
			std::integral_constant<int, 3>,
			std::integral_constant<int, 3>,
			std::integral_constant<int, 4>,
			std::integral_constant<int, 5>,
			std::integral_constant<int, 5>,
			std::integral_constant<int, 5>,
			std::integral_constant<int, 6>,
			std::integral_constant<int, 9>
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<
			std::integral_constant<int, 3>
		>;

		using t2 = bksge::tuple_sort_type_t<t>;

		using expected = Tuple<
			std::integral_constant<int, 3>
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<>;

		using t2 = bksge::tuple_sort_type_t<t>;

		using expected = Tuple<>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<
			char[1],
			char[3],
			char[2],
			char[4],
			char[5]
		>;

		using t2 = bksge::tuple_sort_type_t<t, size_greater>;

		using expected = Tuple<
			char[5],
			char[4],
			char[3],
			char[2],
			char[1]
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
}

GTEST_TEST(TupleTest, TupleSortTypeTest)
{
	TupleSortTypeTest<std::tuple>();
	TupleSortTypeTest<MyTuple>();
}

}	// namespace tupe_sort_type_test

}	// namespace bksge_tuple_test
