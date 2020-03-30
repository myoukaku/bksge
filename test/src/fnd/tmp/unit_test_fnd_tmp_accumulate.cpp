/**
 *	@file	unit_test_fnd_tmp_accumulate.cpp
 *
 *	@brief	accumulate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/accumulate.hpp>
#include <bksge/fnd/tmp/plus.hpp>
#include <bksge/fnd/tmp/minus.hpp>
#include <bksge/fnd/tmp/multiplies.hpp>
#include <bksge/fnd/tmp/max.hpp>
#include <bksge/fnd/tmp/min.hpp>
#include <bksge/fnd/utility/integer_sequence.hpp>
#include <gtest/gtest.h>

namespace bksge_tmp_test
{

namespace accumulate_test
{

template <typename T, T... Is>
struct MySeq
{
	using value_type = T;
};

GTEST_TEST(TmpTest, AccumulateTest)
{
	using namespace bksge::tmp;
	using bksge::integer_sequence;

	static_assert(accumulate<integer_sequence<int>>::value == 0, "");
	static_assert(accumulate<integer_sequence<int>, 2>::value == 2, "");
	static_assert(accumulate<integer_sequence<int, 1>>::value == 1, "");
	static_assert(accumulate<integer_sequence<int, 1>, 3>::value == 4, "");
	static_assert(accumulate<integer_sequence<int, 2, 3>>::value == 5, "");
	static_assert(accumulate<integer_sequence<int, 3, 4, 5>>::value == 12, "");
	static_assert(accumulate<integer_sequence<int, 3, 4, 5>, 0, plus>::value == 12, "");

	static_assert(accumulate<integer_sequence<unsigned int, 2>>::value == 2, "");
	static_assert(accumulate<integer_sequence<unsigned int, 3, 1, 4, 1, 5>>::value == 14, "");
	static_assert(accumulate<integer_sequence<unsigned int, 3, 1, 4, 1, 5>, 42>::value == 56, "");

	static_assert(accumulate<integer_sequence<int>, 1, multiplies>::value == 1, "");
	static_assert(accumulate<integer_sequence<int, 3>, 1, multiplies>::value == 3, "");
	static_assert(accumulate<integer_sequence<int, 3, 4>, 1, multiplies>::value == 12, "");
	static_assert(accumulate<integer_sequence<int, 3, 4, 5>, 1, multiplies>::value == 60, "");
	static_assert(accumulate<integer_sequence<int, 3, 4, 5>, 2, multiplies>::value == 120, "");

	static_assert(accumulate<integer_sequence<int, 3, 4, 5>, 0, minus>::value == -12, "");
	static_assert(accumulate<integer_sequence<int, 3, 4, 5>, 100, minus>::value == 88, "");
	static_assert(accumulate<integer_sequence<int>, 0, minus>::value == 0, "");
	static_assert(accumulate<integer_sequence<int, 9, -1, 3, 12, -5, 7>, 0, minus>::value == -25, "");

	static_assert(accumulate<integer_sequence<int, 9, -1, 3, 12, -5, 7>, 0, max>::value == 12, "");
	static_assert(accumulate<integer_sequence<int, 9, -1, 3, 12, -5, 7>, 0, min>::value == -5, "");

	static_assert(accumulate<MySeq<int, 1, 2>>::value == 3, "");
	static_assert(accumulate<MySeq<int, 3, 4, 5>>::value == 12, "");
}

}	// namespace accumulate_test

}	// namespace bksge_tmp_test
