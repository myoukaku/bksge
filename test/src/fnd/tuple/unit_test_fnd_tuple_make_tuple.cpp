/**
 *	@file	unit_test_fnd_tuple_make_tuple.cpp
 *
 *	@brief	make_tuple のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace make_tuple_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		auto t = bksge::make_tuple();
		static_assert(bksge::is_same<decltype(t), bksge::tuple<>>::value, "");
		(void)t;
	}
	{
		auto t = bksge::make_tuple(1.5);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<double>>::value, "");
		VERIFY(get<0>(t) == 1.5);
	}
	{
		auto t = bksge::make_tuple(2, 3);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int, int>>::value, "");
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 3);
	}
	{
		auto t = bksge::make_tuple(1, 'a', 0.5f);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int, char, float>>::value, "");
		VERIFY(get<0>(t) == 1);
		VERIFY(get<1>(t) == 'a');
		VERIFY(get<2>(t) == 0.5f);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, MakeTupleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace make_tuple_test

}	// namespace bksge_tuple_test
