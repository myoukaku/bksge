/**
 *	@file	unit_test_fnd_tuple_tuple_tail_type.cpp
 *
 *	@brief	tuple_tail_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_tail_type.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace tuple_tail_type_test
{

template <typename... Types>
struct MyTuple
{
};

template <template <typename...> class Tuple>
void TupleTailTypeTest()
{
	{
		using t1 = Tuple<int, float, double, long>;
		using t2 = bksge::tuple_tail_type_t<t1>;
		using t3 = bksge::tuple_tail_type_t<t2>;
		using t4 = bksge::tuple_tail_type_t<t3>;
		using t5 = bksge::tuple_tail_type_t<t4>;
		using t6 = bksge::tuple_tail_type_t<t5>;

		static_assert(bksge::is_same<t1, Tuple<int, float, double, long>>::value, "");
		static_assert(bksge::is_same<t2, Tuple<     float, double, long>>::value, "");
		static_assert(bksge::is_same<t3, Tuple<            double, long>>::value, "");
		static_assert(bksge::is_same<t4, Tuple<                    long>>::value, "");
		static_assert(bksge::is_same<t5, Tuple<                        >>::value, "");
		static_assert(bksge::is_same<t6, Tuple<                        >>::value, "");
	}
	{
		using t1 = Tuple<int, int, int>;
		using t2 = bksge::tuple_tail_type_t<t1>;
		using t3 = bksge::tuple_tail_type_t<t2>;
		using t4 = bksge::tuple_tail_type_t<t3>;
		using t5 = bksge::tuple_tail_type_t<t4>;

		static_assert(bksge::is_same<t1, Tuple<int, int, int>>::value, "");
		static_assert(bksge::is_same<t2, Tuple<     int, int>>::value, "");
		static_assert(bksge::is_same<t3, Tuple<          int>>::value, "");
		static_assert(bksge::is_same<t4, Tuple<             >>::value, "");
		static_assert(bksge::is_same<t5, Tuple<             >>::value, "");
	}
	{
		using t1 = Tuple<>;
		using t2 = bksge::tuple_tail_type_t<t1>;
		using t3 = bksge::tuple_tail_type_t<t2>;

		static_assert(bksge::is_same<t1, Tuple<>>::value, "");
		static_assert(bksge::is_same<t2, Tuple<>>::value, "");
		static_assert(bksge::is_same<t3, Tuple<>>::value, "");
	}
}

GTEST_TEST(TupleTest, TupleTailTypeTest)
{
	TupleTailTypeTest<bksge::tuple>();
	TupleTailTypeTest<MyTuple>();
}

}	// namespace tuple_tail_type_test

}	// namespace bksge_tuple_test
