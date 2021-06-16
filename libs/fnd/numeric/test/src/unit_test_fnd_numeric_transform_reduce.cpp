/**
 *	@file	unit_test_fnd_numeric_transform_reduce.cpp
 *
 *	@brief	transform_reduce のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/transform_reduce.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace transform_reduce_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	double b[] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

	auto res = bksge::transform_reduce(bksge::begin(a), bksge::end(a), bksge::begin(b), 1.0f);
	static_assert(bksge::is_same<decltype(res), float>::value, "");
	VERIFY(res == (float)(1 + 0.5 + 1 + 1.5 + 2 + 2.5 + 3 + 3.5 + 4 + 4.5 + 5));

	test_container<int, input_iterator_wrapper> ca(a);
	test_container<double, input_iterator_wrapper> cb(b);

	auto res2 = bksge::transform_reduce(ca.begin(), ca.end(), cb.begin(), 1.0f);
	static_assert(bksge::is_same<decltype(res2), float>::value, "");
	VERIFY(res2 == res);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	double b[] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

	auto res = bksge::transform_reduce(
		bksge::begin(a), bksge::end(a),
		bksge::begin(b),
		1L,
		bksge::multiplies<>{},
		bksge::plus<int>{});
	static_assert(bksge::is_same<decltype(res), long>::value, "");
	VERIFY(res == (1L * 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10));

	test_container<int, input_iterator_wrapper> ca(a);
	test_container<double, input_iterator_wrapper> cb(b);

	auto res2 = bksge::transform_reduce(
		ca.begin(), ca.end(),
		cb.begin(),
		1L,
		bksge::multiplies<>{},
		bksge::plus<int>{});
	static_assert(bksge::is_same<decltype(res2), long>::value, "");
	VERIFY(res2 == res);

	return true;
}

struct square
{
	template <typename T>
	constexpr T operator()(T x) const { return x * x; }
};

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	double b[] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

	auto res = bksge::transform_reduce(
		bksge::begin(a), bksge::end(a),
		10.0,
		bksge::plus<>{},
		square{});
	static_assert(bksge::is_same<decltype(res), double>::value, "");
	VERIFY(res == (10.0 + 1 + 4 + 9 + 16 + 25 + 36 + 49 + 64 + 81 + 100));

	test_container<int, input_iterator_wrapper> ca(a);
	test_container<double, input_iterator_wrapper> cb(b);

	auto res2 = bksge::transform_reduce(
		ca.begin(), ca.end(),
		10.0,
		bksge::plus<>{},
		square{});
	static_assert(bksge::is_same<decltype(res2), double>::value, "");
	VERIFY(res2 == (10.0 + 1 + 4 + 9 + 16 + 25 + 36 + 49 + 64 + 81 + 100));

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, TransformReduceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace transform_reduce_test

}	// namespace bksge_numeric_test
