/**
 *	@file	unit_test_fnd_tuple_forward_as_tuple.cpp
 *
 *	@brief	forward_as_tuple のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/forward_as_tuple.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
//#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace forward_as_tuple_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		auto t = bksge::forward_as_tuple();
		static_assert(bksge::is_same<decltype(t), bksge::tuple<>>::value, "");
	}
	{
		auto t = bksge::forward_as_tuple(0.5f);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<float&&>>::value, "");
		VERIFY(get<0>(bksge::forward_as_tuple(0.5f)) == 0.5f);
	}
	{
		auto t = bksge::forward_as_tuple(1, 'a', 2.5);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int&&, char&&, double&&>>::value, "");
		VERIFY(get<0>(bksge::forward_as_tuple(1, 'a', 2.5)) == 1);
		VERIFY(get<1>(bksge::forward_as_tuple(1, 'a', 2.5)) == 'a');
		VERIFY(get<2>(bksge::forward_as_tuple(1, 'a', 2.5)) == 2.5);
	}
	{
		int a = 3;
		const float b = 4.5f;
		auto t = bksge::forward_as_tuple(a, 5, b);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int&, int&&, const float&>>::value, "");
		VERIFY(get<0>(t) == a);
		VERIFY(get<2>(t) == b);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, ForwardAsTupleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace forward_as_tuple_test

}	// namespace bksge_tuple_test
